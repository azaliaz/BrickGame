#include "tetris_cli.h"

#include "../../brick_game/tetris/tetris.h"

UserAction_t get_signal() {
  int ch = getch();

  switch (ch) {
    case KEY_LEFT:
      return Left;
    case KEY_RIGHT:
      return Right;
    case 'z':
      return Up;
    case KEY_DOWN:
      return Down;
    case '\n':
      return Start;
    case 'p':
      return Pause;
    case 27:
      return Terminate;
    default:
      return Action;
  }
}
void printGame(GameInfo_t game, struct timespec sp_start,
               struct timespec sp_end) {
  drawField(game);
  printNextFigure(game);
  printInfo(game);
  freeResources(game, 5, 20);
  timeFunction(sp_start, sp_end, game.speed);
  refresh();
}

void printNextFigure(GameInfo_t game) {
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      int sym = game.next[i][j] != 0 ? 2 : 0;
      attron(COLOR_PAIR(sym));
      mvaddch(i + 5, j * 2 + 53, ' ');
      mvaddch(i + 5, j * 2 + 54, ' ');
      attroff(COLOR_PAIR(sym));
    }
  }
}
void initColors() {
  start_color();
  init_pair(1, COLOR_BLACK, COLOR_WHITE);
  init_pair(2, COLOR_RED, COLOR_RED);
  init_pair(3, COLOR_WHITE, COLOR_BLACK);
  init_pair(4, COLOR_RED, COLOR_BLACK);
}

void drawField(GameInfo_t game) {
  int width = 10;
  int height = 20;

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      int sym = game.board[i][j] != 0 ? 2 : 1;
      attron(COLOR_PAIR(sym));
      mvaddch(i + 3, j * 2 + 27, ' ');
      mvaddch(i + 3, j * 2 + 28, ' ');
      attroff(COLOR_PAIR(sym));
    }
  }
}

void printInfo(GameInfo_t game) {
  attron(COLOR_PAIR(3));
  mvwprintw(stdscr, 1, 35, "TETRIS");
  attroff(COLOR_PAIR(3));

  attron(COLOR_PAIR(3));
  mvwprintw(stdscr, 4, 52, "NEXT FIGURE:");
  mvwprintw(stdscr, 10, 52, "LEVEL: %d", game.level);
  mvwprintw(stdscr, 13, 52, "SPEED: %d", game.speed);
  mvwprintw(stdscr, 16, 52, "SCORE: %d", game.score);
  clrtoeol();
  mvwprintw(stdscr, 19, 52, "HIGHT SCORE: %d", game.high_score);
  attroff(COLOR_PAIR(3));
  if (game.pause) {
    for (int i = 0; i < 20; i++) {
      for (int j = 0; j < 10; j++) {
        mvaddch(i + 3, j * 2 + 27, ' ');
        mvaddch(i + 3, j * 2 + 28, ' ');
      }
    }
    mvwprintw(stdscr, 10, 35, "Press");
    mvwprintw(stdscr, 12, 35, "ENTER");
    mvwprintw(stdscr, 14, 36, "to");
    mvwprintw(stdscr, 16, 35, "START");
  }
  attron(COLOR_PAIR(3));
  mvwprintw(stdscr, 8, 6, "Pause: 'p'");
  mvwprintw(stdscr, 10, 6, "Exit: 'ESC key'");
  mvwprintw(stdscr, 12, 6, "Move: '<' '>' 'v' ");
  mvwprintw(stdscr, 14, 6, "Rotate: 'z'");
}

void timeFunction(struct timespec sp_start, struct timespec sp_end,
                  int game_speed) {
  clock_gettime(CLOCK_MONOTONIC, &sp_end);
  struct timespec ts1, ts2 = {0, 0};
  if (sp_end.tv_sec - sp_start.tv_sec <= 0 &&
      (ts2.tv_nsec = (20000000 - game_speed * 1500000) -
                     (sp_end.tv_nsec - sp_start.tv_nsec)) > 0) {
    nanosleep(&ts2, &ts1);
  }
}