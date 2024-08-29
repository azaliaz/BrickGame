#include "tetris.h"

#include "../../gui/cli/tetris_cli.h"
#include "templates.h"

void userInput(UserAction_t action, bool hold) {
  if (!hold) {
    switch (action) {
      case Left:
        game->player->action = Left;
        break;
      case Right:
        game->player->action = Right;
        break;
      case Up:
        game->player->action = Up;
        break;
      case Down:
        game->player->action = Down;
        break;
      case Start:
        game->player->action = Start;
        break;
      case Pause:
        game->player->action = Pause;
        break;
      case Terminate:
        game->player->action = Terminate;
        break;
      default:
        game->player->action = Action;
        break;
    }
  }
}

void moveFigureDown(GameInfo_t *game) { game->figure->y++; }

void moveFigureUp(GameInfo_t *game) { game->figure->y--; }

void moveFigureRight(GameInfo_t *game) { game->figure->x++; }

void moveFigureLeft(GameInfo_t *game) { game->figure->x--; }

int collisionTet(GameInfo_t *game) {
  TetFigure *tet = game->figure;  // падающая фигура
  TetField *field = game->field;  // игровое поле
  for (int i = 0; i < tet->size; i++) {
    for (int j = 0; j < tet->size; j++) {
      if (tet->blocks[i][j].b != 0) {
        int fx = tet->x + j;
        int fy = tet->y + i;
        if (fx < 0 || fx >= field->width || fy < 0 || fy >= field->height) {
          game->playing = COLLISION;
          return 1;
        }
        if (field->blocks[fy][fx].b != 0) {
          game->playing = COLLISION;
          return 1;
        }
      }
    }
  }
  return 0;
}

// размещение фигуры после падения
void locationFigure(GameInfo_t *game) {
  TetFigure *t = game->figure;
  TetField *field = game->field;
  for (int i = 0; i < t->size; i++)
    for (int j = 0; j < t->size; j++) {
      if (t->blocks[i][j].b !=
          0) {  // если блок не нулевой определим координаты поля соотв блоку и
                // перенесем его данные на поле
        int fieldX = t->x + j;  // x на игровом поле
        int fieldY = t->y + i;  // y на игровом поле
        // yбедимся, что координаты в пределах игрового поля
        if (fieldX >= 0 && fieldX < field->width && fieldY >= 0 &&
            fieldY < field->height) {
          game->field->blocks[fieldY][fieldX].b = t->blocks[i][j].b;
        }
      }
    }
}

// проверка заполенения строки
int lineFilledTet(int i, TetField *tfl) {
  for (int j = 0; j < tfl->width; j++)
    if (tfl->blocks[i][j].b == 0) return 0;
  return 1;
}

// процедура сдвга на одну строку
void dropLineTet(int i, TetField *tfl) {
  if (i == 0) {
    for (int j = 0; j < tfl->width; j++) tfl->blocks[i][j].b = 0;
  } else {
    // переносим блоки верхней строки на строку текущую
    for (int k = i; k > 0; k--)
      for (int j = 0; j < tfl->width; j++)
        tfl->blocks[k][j].b = tfl->blocks[k - 1][j].b;
  }
}

// функция удаляющая строки и подсчиатвающая очки
int fullLineGame(GameInfo_t *game) {
  TetField *tfl = game->field;
  int count = 0;
  for (int i = tfl->height - 1; i >= 0; i--) {
    while (lineFilledTet(i, tfl)) {  // пока текущая строка заполнена
      dropLineTet(i, tfl);  // удаляем ее со сдвигом вниз
      count++;  // увеличиваем количество удаленных строк на 1
    }
  }
  return count;
}

void dropNewFigure(GameInfo_t *game) {
  int fnum = game->next_figure;

  TetFigure *t = createTetFigure(game);

  int template_size = game->figure_t->size;
  TetBlock *template_blocks = game->figure_t->blocks[fnum];

  for (int i = 0; i < t->size; i++) {
    for (int j = 0; j < t->size; j++) {
      if (i * template_size + j < template_size * template_size) {
        t->blocks[i][j].b = template_blocks[i * template_size + j].b;
      } else {
        t->blocks[i][j].b = 0;
      }
    }
  }
  if (game->figure != NULL) freeTetFigure(game->figure);
  game->figure = t;
  game->next_figure = rand() % game->figure_t->count;
}

TetFigure *rotateFigure(GameInfo_t *game) {
  TetFigure *tet = createTetFigure(game);  // создам пустую фигуру
  TetFigure *tet_old = game->figure;
  tet->x = tet_old->x;
  tet->y = tet_old->y;
  for (int i = 0; i < tet->size; i++)
    for (int j = 0; j < tet->size; j++)
      tet->blocks[i][j].b = tet_old->blocks[j][tet->size - 1 - i].b;
  return tet;
}

void calcOne(GameInfo_t *game) {
  game->ticks_next = game->ticks;
  moveFigureDown(game);
  game->playing = MOVING;

  if (collisionTet(game)) {
    moveFigureUp(game);
    locationFigure(game);
    linesToScore(game);
    dropNewFigure(game);
    game->playing = DROP;

    if (collisionTet(game)) {
      game->playing = GAMEOVER;
    }
  }
}

void calcTet(GameInfo_t *game) {
  if (game->ticks_next <= 0 && game->playing != PAUSE &&
      game->playing != INIT) {
    calcOne(game);
  }

  if (game->playing == GAMEOVER) return;
  switch (game->player->action) {
    case Right:
      if (game->pause) break;
      moveFigureRight(game);
      if (collisionTet(game)) moveFigureLeft(game);
      break;
    case Left:
      if (game->pause) break;
      moveFigureLeft(game);
      if (collisionTet(game)) moveFigureRight(game);
      break;
    case Down:
      if (game->pause) break;
      moveFigureDown(game);
      if (collisionTet(game)) moveFigureUp(game);
      break;
    case Up:
      if (game->pause) break;
      TetFigure *t = rotateFigure(game);
      TetFigure *told = game->figure;
      game->figure = t;
      if (collisionTet(game)) {
        game->figure = told;
        freeTetFigure(t);
      } else {
        freeTetFigure(told);
      }
      break;
    case Pause:
      if (game->pause) {
        game->pause = 0;
        game->playing = MOVING;
      } else {
        game->pause = 1;
        game->playing = PAUSE;
      }
      break;
    case Terminate:
      game->playing = GAMEOVER;
      break;
    case Start:
      game->pause = 0;
      game->playing = MOVING;
      break;
    default:
      break;
  }
  game->ticks_next--;
}

void linesToScore(GameInfo_t *game) {
  int lines = fullLineGame(game);
  if (lines == 1) {
    game->score += 100;
  }
  if (lines == 2) {
    game->score += 300;
  }
  if (lines == 3) {
    game->score += 700;
  }
  if (lines >= 4) {
    game->score += 1500;
  }
  if (game->score > game->high_score) {
    game->high_score = game->score;
    FILE *tetHighScore;
    tetHighScore = fopen("./highscore_tetris.txt", "w");
    if (tetHighScore) {
      fprintf(tetHighScore, "%d", game->high_score);
      fclose(tetHighScore);
    }
  }
  int new_level = game->score / 600 + 1;
  if (new_level > 10) {
    new_level = 10;
  }

  if (new_level > game->level) {
    game->level = new_level;
    game->speed += new_level;
  }
}

int highscoreRead() {
  int high_score = 0;
  FILE *tetHighScore;
  tetHighScore = fopen("./highscore_tetris.txt", "r");
  if (tetHighScore != NULL) {
    fscanf(tetHighScore, "%d", &high_score);
    fclose(tetHighScore);
  }
  return high_score;
}

GameInfo_t updateCurrentState() {
  GameInfo_t updatedGame = {0};

  calcTet(game);
  if (game->playing != GAMEOVER) {
    if (updatedGame.board != NULL) {
      freePrintField(updatedGame.board, game->field->height);
    }
    updatedGame.board =
        createPrintField(game->field->width, game->field->height);

    if (updatedGame.next != NULL) {
      freeNext(updatedGame.next, game->figure_t->size);
    }
    updatedGame.next = createNextfigure(game->figure_t->size);

    updatedGame.score = game->score;
    updatedGame.high_score = game->high_score;
    updatedGame.level = game->level;
    updatedGame.speed = game->speed;
    updatedGame.pause = game->pause;
  }

  return updatedGame;
}
