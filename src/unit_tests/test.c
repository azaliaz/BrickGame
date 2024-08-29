#include <check.h>

#include "../brick_game/tetris/templates.h"
#include "../brick_game/tetris/tetris.h"

GameInfo_t *game;
void cleanup(GameInfo_t game_info) {
  freeResources(game_info, game->figure_t->size, game->field->height);
  freeGame(game);
}

START_TEST(test_input_Terminate_action) {
  initGame();
  userInput(Terminate, 0);
  GameInfo_t game_info = updateCurrentState();
  ck_assert_int_eq(game->player->action, Terminate);
  cleanup(game_info);
}
END_TEST

START_TEST(test_input_Start_action) {
  initGame();
  userInput(Start, 0);
  GameInfo_t game_info = updateCurrentState();
  ck_assert_int_eq(game->player->action, Start);
  cleanup(game_info);
}
END_TEST

START_TEST(test_collision) {
  initGame();
  game->pause = 0;
  game->ticks_next = 0;
  game->player->action = Down;

  int res = collisionTet(game);
  ck_assert_int_eq(res, 0);
  cleanup(updateCurrentState());
}
END_TEST

START_TEST(test_eraseLines) {
  initGame();
  int line_erase = 18;
  for (int i = 0; i < game->field->width; i++) {
    game->field->blocks[line_erase][i].b = 1;
  }
  int erased = fullLineGame(game);
  ck_assert_int_eq(erased, 1);
  cleanup(updateCurrentState());
}
END_TEST

START_TEST(test_createGame) {
  initGame();
  ck_assert_ptr_nonnull(game);
  ck_assert_ptr_nonnull(game->player);
  ck_assert_int_eq(game->player->action, Start);
  ck_assert_ptr_nonnull(game->figure);
  cleanup(updateCurrentState());
}
END_TEST

START_TEST(test_input_Left_action) {
  initGame();
  game->pause = 1;
  userInput(Left, 0);
  GameInfo_t game_info = updateCurrentState();
  ck_assert_int_eq(game->player->action, Left);
  cleanup(game_info);
}
END_TEST

START_TEST(test_input_Left_action_with_collision) {
  initGame();
  game->pause = 0;
  userInput(Left, 0);
  for (int i = 0; i < game->field->width; i++) {
    game->field->blocks[1][i].b = 1;
  }
  GameInfo_t game_info = updateCurrentState();
  ck_assert_int_eq(game->player->action, Left);
  cleanup(game_info);
}
END_TEST

START_TEST(test_input_Right_action) {
  initGame();
  game->pause = 0;
  userInput(Right, 0);
  GameInfo_t game_info = updateCurrentState();
  ck_assert_int_eq(game->player->action, Right);
  cleanup(game_info);
}
END_TEST

START_TEST(test_input_Down_action) {
  initGame();
  game->pause = 0;
  userInput(Down, 0);
  GameInfo_t game_info = updateCurrentState();
  ck_assert_int_eq(game->player->action, Down);
  cleanup(game_info);
}
END_TEST

START_TEST(test_input_Down_action_with_collision) {
  initGame();
  game->pause = 0;
  userInput(Down, 0);
  for (int i = 0; i < game->field->width; i++) {
    game->field->blocks[1][i].b = 1;
  }
  GameInfo_t game_info = updateCurrentState();
  ck_assert_int_eq(game->player->action, Down);
  cleanup(game_info);
}
END_TEST

START_TEST(test_input_Pause_action) {
  initGame();
  userInput(Pause, 0);
  GameInfo_t game_info = updateCurrentState();
  ck_assert_int_eq(game->player->action, Pause);
  cleanup(game_info);
}
END_TEST

START_TEST(test_plant_figure) {
  initGame();
  game->pause = 0;
  locationFigure(game);
  ck_assert_ptr_nonnull(game->figure);
  cleanup(updateCurrentState());
}
END_TEST

START_TEST(test_rotate_figure) {
  initGame();
  game->pause = 0;
  userInput(Up, 0);
  GameInfo_t game_info = updateCurrentState();
  ck_assert_int_eq(game->player->action, Up);
  ck_assert_ptr_nonnull(game->figure);
  cleanup(game_info);
}
END_TEST

START_TEST(test_rotate_figure_collision) {
  initGame();
  game->pause = 0;
  for (int i = 0; i < game->field->width; i++) {
    game->field->blocks[2][i].b = 1;
  }
  userInput(Up, 0);
  GameInfo_t game_info = updateCurrentState();
  ck_assert_int_eq(game->player->action, Up);
  ck_assert_ptr_nonnull(game->figure);
  cleanup(game_info);
}
END_TEST

START_TEST(test_count_score) {
  initGame();
  game->pause = 0;
  game->high_score = 0;
  game->score = 700;

  int line_fill = 18;
  for (int i = 0; i < game->field->width; i++) {
    game->field->blocks[line_fill][i].b = 1;
  }
  linesToScore(game);

  ck_assert_int_eq(game->score, 800);
  cleanup(updateCurrentState());
}
END_TEST

int main(void) {
  Suite *s = suite_create("Tetris Game Tests");
  TCase *tc_input_actions = tcase_create("Input Actions");
  tcase_add_test(tc_input_actions, test_input_Terminate_action);
  tcase_add_test(tc_input_actions, test_input_Start_action);
  suite_add_tcase(s, tc_input_actions);

  TCase *tc_collision = tcase_create("collisionTet Tests");
  tcase_add_test(tc_collision, test_collision);
  suite_add_tcase(s, tc_collision);

  TCase *tc_eraseLines = tcase_create("Erase Lines");
  tcase_add_test(tc_eraseLines, test_eraseLines);
  suite_add_tcase(s, tc_eraseLines);

  TCase *tc_createGame = tcase_create("Create Game");
  tcase_add_test(tc_createGame, test_createGame);
  suite_add_tcase(s, tc_createGame);

  TCase *tc_input = tcase_create("Input Tests");
  tcase_add_test(tc_input, test_input_Left_action);
  tcase_add_test(tc_input, test_input_Left_action_with_collision);
  tcase_add_test(tc_input, test_input_Right_action);
  tcase_add_test(tc_input, test_input_Down_action);
  tcase_add_test(tc_input, test_input_Down_action_with_collision);
  tcase_add_test(tc_input, test_input_Pause_action);
  suite_add_tcase(s, tc_input);

  TCase *tc_plant_figure = tcase_create("Plant Figure");
  tcase_add_test(tc_plant_figure, test_plant_figure);
  suite_add_tcase(s, tc_plant_figure);

  TCase *tc_rotate_figure = tcase_create("Rotate Figure");
  tcase_add_test(tc_rotate_figure, test_rotate_figure);
  tcase_add_test(tc_rotate_figure, test_rotate_figure_collision);
  suite_add_tcase(s, tc_rotate_figure);

  TCase *tc_count_score = tcase_create("Count Score");
  tcase_add_test(tc_count_score, test_count_score);
  suite_add_tcase(s, tc_count_score);

  // Запуск тестов
  SRunner *sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
