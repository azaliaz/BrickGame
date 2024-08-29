#include "templates.h"
#include "tetris.h"

void initGame() {
  game = createGame(10, 20, 5, 7, tet_templates);

  TetPlayer *player = (TetPlayer *)malloc(sizeof(TetPlayer));
  player->action = Start;
  game->player = player;
  dropNewFigure(game);
}

GameInfo_t *createGame(int field_width, int field_height, int figures_size,
                       int count, TetBlock **figures_template) {
  GameInfo_t *game = (GameInfo_t *)malloc(sizeof(GameInfo_t));
  game->field = createTetField(field_width, field_height);

  game->figure_t = createTetTemplates(count, figures_size, figures_template);

  game->ticks = TET_TICKS_START;
  game->ticks_next = TET_TICKS_START;
  game->score = 0;
  game->high_score = highscoreRead();
  game->speed = 1;
  game->level = 1;
  game->pause = 1;
  game->playing = INIT;
  game->next_figure = rand() % game->figure_t->count;

  return game;
}
TetTemplates *createTetTemplates(int count, int figures_size,
                                 TetBlock **figures_template) {
  TetTemplates *tetft = (TetTemplates *)malloc(sizeof(TetTemplates));

  tetft->count = count;
  tetft->size = figures_size;
  tetft->blocks = figures_template;
  return tetft;
}
int **createNextfigure(int size) {
  int **next = (int **)malloc(size * sizeof(int *));

  for (int i = 0; i < size; i++) {
    next[i] = (int *)malloc(size * sizeof(int));
  }

  TetBlock *next_template = game->figure_t->blocks[game->next_figure];
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      next[i][j] = next_template[i * size + j].b;
    }
  }
  return next;
}
// сoздание поля
TetField *createTetField(int width, int height) {
  TetField *tetf = (TetField *)malloc(sizeof(TetField));  // выделили поле

  tetf->width = width;
  tetf->height = height;
  tetf->blocks = (TetBlock **)malloc(height * sizeof(TetBlock *));

  for (int i = 0; i < height; i++) {
    tetf->blocks[i] = (TetBlock *)malloc(width * sizeof(TetBlock));

    for (int j = 0; j < width; j++) {
      tetf->blocks[i][j].b = 0;
    }
  }
  return tetf;
}

int **createPrintField(int width, int height) {
  TetField *field = game->field;
  TetFigure *figure = game->figure;

  int **tetfield = (int **)malloc(height * sizeof(int *));
  for (int i = 0; i < height; i++) {
    tetfield[i] = (int *)malloc(width * sizeof(int));
  }

  for (int i = 0; i < field->height; i++) {
    for (int j = 0; j < field->width; j++) {
      int sym = 0;

      if (field->blocks[i][j].b != 0) {
        sym = 1;
      } else {
        int x = j - figure->x;
        int y = i - figure->y;

        if (x >= 0 && x < figure->size && y >= 0 && y < figure->size) {
          if (figure->blocks[y][x].b != 0) {
            sym = 1;
          }
        }
      }
      tetfield[i][j] = sym;
    }
  }

  return tetfield;
}

TetFigure *createTetFigure(GameInfo_t *game) {
  TetFigure *figure = (TetFigure *)malloc(sizeof(TetFigure));
  figure->x = 3;
  figure->y = 0;
  figure->size = game->figure_t->size;
  figure->blocks = (TetBlock **)malloc(sizeof(TetBlock *) * figure->size);
  for (int i = 0; i < figure->size; i++) {
    figure->blocks[i] = (TetBlock *)malloc(sizeof(TetBlock) * figure->size);
    for (int j = 0; j < figure->size; j++) {
      figure->blocks[i][j].b = 0;
    }
  }
  return figure;
}
