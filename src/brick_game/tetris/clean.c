#include "tetris.h"

void freePrintField(int **print_field, int height) {
  if (print_field) {
    for (int i = 0; i < height; i++) {
      if (print_field[i]) free(print_field[i]);
    }
    free(print_field);
  }
}

void freeNext(int **next, int size) {
  if (next) {
    for (int i = 0; i < size; i++) free(next[i]);
    free(next);
  }
}

void freeTetField(TetField *field) {
  if (field) {
    for (int i = 0; i < field->height; i++) {
      free(field->blocks[i]);
    }
    free(field->blocks);
    free(field);
  }
}

void freeTetFigure(TetFigure *figure) {
  if (figure) {
    if (figure->blocks) {
      for (int i = 0; i < figure->size; i++) {
        free(figure->blocks[i]);
      }
      free(figure->blocks);
    }
    free(figure);
  }
}

void freeTetTemplates(TetTemplates *templates) {
  if (templates) {
    free(templates);
  }
}
void freeResources(GameInfo_t game, int size, int height) {
  freePrintField(game.board, height);
  freeNext(game.next, size);
}

void freeGame(GameInfo_t *tetg) {
  if (tetg) {
    if (tetg->figure != NULL) freeTetFigure(tetg->figure);
    freeTetField(tetg->field);
    freeTetTemplates(tetg->figure_t);
    free(tetg->player);
    free(tetg);
  }
}