#ifndef TETRIS_CLI_H
#define TETRIS_CLI_H
#include <ncurses.h>

#include "../../brick_game/tetris/tetris.h"

/**
 * @brief Получает пользовательский ввод и возвращает соответствующее действие.
 *
 * Функция использует библиотеку `ncurses` для захвата нажатой клавиши и
 * возвращает действие, соответствующее нажатой клавише.
 *
 * @return UserAction_t Возвращает действие в зависимости от нажатой клавиши.
 */
UserAction_t get_signal();

/**
 * @brief Отрисовывает игровое поле.
 *
 * @param game Структура, содержащая информацию об игре.
 */
void drawField(GameInfo_t game);

/**
 * @brief Отображает текущее состояние игры.
 *
 * Функция отвечает за отрисовку игрового поля.
 *
 * @param game Структура, содержащая информацию об игре.
 * @param sp_start Время начала текущего кадра.
 * @param sp_end Время окончания текущего кадра.
 */
void printGame(GameInfo_t game, struct timespec sp_start,
               struct timespec sp_end);

/**
 * @brief Обрабатывает задержку, чтобы обеспечить желаемую скорость игры.
 *
 * Эта функция вычисляет время, прошедшее между началом и концом итерации
 * игрового цикла. Затем она определяет, необходима ли задержка, чтобы скорость
 * игры соответствовала желаемой. Если прошедшее время меньше требуемого времени
 * для кадра, функция использует `nanosleep`, чтобы приостановить выполнение до
 * тех пор, пока не истечет требуемое время.
 *
 * @param sp_start  Время начала итерации игрового цикла, захваченное с помощью
 * `clock_gettime()`.
 * @param sp_end    Время окончания итерации игрового цикла, захваченное с
 * помощью `clock_gettime()`.
 * @param game_speed Скорость игры, которая влияет на требуемое время задержки.
 *
 * Функция вычисляет необходимое время задержки на основе фиксированной
 * продолжительности кадра (20 мс) и корректирует его в зависимости от параметра
 * `game_speed`. Если оставшееся время после итерации игрового цикла
 * положительно, функция вызывает `nanosleep()`, чтобы задержать выполнение.
 */
void timeFunction(struct timespec sp_start, struct timespec sp_end,
                  int game_speed);

/**
 * @brief Отображает следующую фигуру на экране, которая будет падать.
 * @param game Структура, содержащую информацию об игре.
 */
void printNextFigure(GameInfo_t game);

/**
 * @brief Инициализирует цветовые пары для отрисовки.
 *
 * Функция устанавливает цветовые пары, используемые для отрисовки различных
 * элементов игры.
 */
void initColors();

/**
 * @brief Отображает информацию о текущем состоянии игры.
 *
 * Функция выводит информацию о текущем уровне, скорости, очках и рекорде. Также
 * отображает состояние паузы и управляет выводом инструкций по управлению.
 *
 * @param game Указатель на структуру, содержащую информацию об игре.
 */
void printInfo(GameInfo_t game);
#endif