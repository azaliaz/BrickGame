#ifndef TETRIS_H
#define TETRIS_H

#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TET_TICKS_START 30
/**
 * @brief Возможные действия для игры
 */
typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

/**
 * @brief Перечисление для состояний игры.
 *
 * это используется для отслеживания различных состояний игры.
 */
typedef enum {
  /*!
    \brief Инициализация игры
   */
  INIT = 0,
  /*!
    \brief Блок падает
  */
  DROP,
  /*!
    \brief Блок перемещается.
  */
  MOVING,
  /*!
    \brief Столкновение блока
  */
  COLLISION,
  /*!
    \brief Игра на паузе
  */
  PAUSE,
  /*!
    \brief Игра окончена
  */
  GAMEOVER
} GameState;

/**
 * @brief Структура для блока тетриса.
 */
typedef struct TetBlock {
  /*!
  \brief Переменная, обозначающая блок на поле
  */
  int b;
} TetBlock;

/**
 * @brief Структура для падающей фигуры
 */
typedef struct TetFigure {
  int x;
  int y;
  int size;
  TetBlock** blocks;
} TetFigure;

/**
 * @brief Структура с описанием шаблон фигур
 */
typedef struct TetTemplates {
  int count;
  int size;
  TetBlock** blocks;
} TetTemplates;

/**
 * @brief Структура для игрового поля тетриса.
 */
typedef struct TetField {
  int width;
  int height;
  TetBlock** blocks;
} TetField;

/**
 * @brief Структура для представления игрока в игре, о его текущем деуствии.
 */
typedef struct TetPlayer {
  int action;
} TetPlayer;

/**
 * @brief Информация о состоянии игры.
 *
 */
typedef struct GameInfo_t {
  /*!

    \brief Указатель на игровое поле.
  */
  TetField* field;

  /*!

   \brief Указатель на текущую фигуру
  */
  TetFigure* figure;
  /*!

   \brief Указатель на шаблоны фигур.
  */
  TetTemplates* figure_t;
  /*!

   \brief Игрок
  */

  TetPlayer* player;
  /*!

   \brief Матрица для представления игрового поля.
  */
  int** board;
  /*!

   \brief  Матрица для обозначения следующей фигуры
  */
  int** next;
  /*!

   \brief Количество тиков игрового цикла
  */
  int ticks;
  /*!

   \brief Количество тиков до следующего события
  */
  int ticks_next;
  /*!

   \brief переменная, указывающая активна ли игра в данный момент
  */
  int playing;
  /*!

   \brief Количество очков
  */
  int score;
  /*!

   \brief Текущий уровень
  */
  int level;
  /*!

   \brief Максимальное количество очков
  */
  int high_score;
  /*!

   \brief Следующая фигура
  */
  int next_figure;
  /*!

   \brief флаг, указывающий нажата ли пауза
  */
  int pause;
  /*!

   \brief Скорость игры
  */
  int speed;
} GameInfo_t;

/**
 * @brief Обрабатывает пользовательский ввод и устанавливает действие игрока.
 * @param action Действие, которое игрок хочет выполнить.
 * @param hold Флаг, указывающий, удерживает ли игрок кнопку.
 */

void userInput(UserAction_t action, bool hold);

/**
 * @brief Инициализирует игру.
 *
 * Создаёт новый объект игры с параметрами, выделяет память для игрока,
 * устанавливает начальное действие игрока и сбрасывает новую фигуру.
 */
void initGame();

/**
 * @brief Создаёт объект игры.
 *
 * @param field_width Ширина игрового поля.
 * @param field_height Высота игрового поля.
 * @param figures_size Размер фигуры.
 * @param count Количество шаблонов фигур.
 * @param figures_template Указатель на массив шаблонов фигур.
 * @return Указатель на инициализированный объект игры.
 */
GameInfo_t* createGame(int field_width, int field_height, int figures_size,
                       int count, TetBlock** figures_template);

/**
 * @brief Создаёт и инициализирует структуру, содержащую шаблоны фигур.
 *
 * @param count Количество шаблонов фигур.
 * @param figures_size Размер фигуры.
 * @param figures_template Указатель на массив шаблонов фигур.
 * @return Указатель на созданные шаблоны фигур.
 */

TetTemplates* createTetTemplates(int count, int figures_size,
                                 TetBlock** figures_template);

/**
 * @brief Создаёт массив для следующей фигуры.
 *
 * @param size Размер поля фигуры.
 * @return Двумерный массив для представления следующей фигуры.
 */
int** createNextfigure(int size);

/**
 * @brief Создаёт игровое поле.
 *
 * @param width Ширина игрового поля.
 * @param height Высота игрового поля.
 * @return Указатель на созданное игровое поле.
 */
TetField* createTetField(int width, int height);

/**
 * @brief Создает игровое поле для вывода на экран.
 *
 * @param width Ширина поля.
 * @param height Высота поля.
 * @return Двумерный массив для отрисовки поля.
 */
int** createPrintField(int width, int height);

/**
 * @brief Создаёт новую фигуру.
 *
 * @param game Указатель на объект игры.
 * @return Указатель на созданную фигуру, или NULL в случае ошибки.
 */
TetFigure* createTetFigure(GameInfo_t* game);

/**
 * @brief Перемещает текущую фигуру вниз на одну клетку.
 * @param game Указатель на структуру с информацией об игре.
 */
void moveFigureDown(GameInfo_t* game);

/**
 * @brief Перемещает текущую фигуру вверх на одну клетку.
 * @param game Указатель на структуру с информацией об игре.
 */
void moveFigureUp(GameInfo_t* game);

/**
 * @brief Перемещает текущую фигуру вправо на одну клетку.
 * @param game Указатель на структуру с информацией об игре.
 */
void moveFigureRight(GameInfo_t* game);

/**
 * @brief Перемещает текущую фигуру влево на одну клетку.
 * @param game Указатель на структуру с информацией об игре.
 */
void moveFigureLeft(GameInfo_t* game);

/**
 * @brief Проверяет на столкновение текущей фигуры с границами поля или другими
 * фигурами.
 * @param game Указатель на структуру с информацией об игре.
 * @return Возвращает 1, если произошло столкновение, и 0 в противном случае.
 */
int collisionTet(GameInfo_t* game);

/**
 * @brief Размещение фигуры после падения.
 * @param game Указатель на структуру с информацией об игре.
 */
void locationFigure(GameInfo_t* game);

/**
 * @brief Проверка на то, заполнена ли указанная строка на игровом поле.
 * @param i Индекс строки.
 * @param tfl Указатель на игровое поле.
 * @return Возвращает 1, если строка заполнена, и 0 в противном случае.
 */
int lineFilledTet(int i, TetField* tfl);

/**
 * @brief Сдвигает строки игрового поля вниз, начиная с указанной строки.
 * @param i Индекс строки, начиная с которой нужно выполнить сдвиг.
 * @param tfl Указатель на игровое поле.
 */
void dropLineTet(int i, TetField* tfl);

/**
 * @brief Создаёт новую фигуру и устанавливает её как текущую.
 * Также выбирает случайную фигуру для следующего падения.
 * @param game Указатель на структуру с информацией об игре.
 */
int fullLineGame(GameInfo_t* game);

/**
 * @brief Поворачивает текущую фигуру на 90 градусов.
 * @param game Указатель на структуру с информацией об игре.
 * @return Указатель на новую фигуру, представляющую повёрнутую версию.
 */
TetFigure* rotateFigure(GameInfo_t* game);

/**
 * @brief Выполняет расчёт состояния игры на основе пользовательского ввода и
 * времени.
 * @param game Указатель на структуру с информацией об игре.
 */
void calcTet(GameInfo_t* game);

/**
 * @brief Выполняет один такт игрового цикла.
 * Перемещает фигуру вниз, проверяет столкновения, обновляет поле и очищает
 * линии.
 * @param game Указатель на структуру с информацией об игре.
 */
void calcOne(GameInfo_t* game);

/**
 * @brief Создаёт новую фигуру и устанавливает её как текущую фигуру в игре.
 *
 * Эта функция выбирает случайную фигуру из набора фигур и устанавливает её как
 * текущую падающую фигуру в игре. Также выбирается новая случайная фигура для
 * следующего падения.
 *
 * @param game Указатель на структуру, содержащую информацию об игре. Не должен
 * быть NULL.
 *
 * @details
 * Функция выполняет следующие шаги:
 * - Создаёт новую фигуру и заполняет её блоки в соответствии с шаблоном
 * выбранной фигуры.
 * - Устанавливает новую фигуру как текущую.
 * - Обновляет номер следующей фигуры.
 */
void dropNewFigure(GameInfo_t* game);

/**
 * @brief Обновляет количество очков на основе удалённых линий.
 * @param game Указатель на структуру с информацией об игре.
 */
void linesToScore(GameInfo_t* game);

/**
 * @brief Читает максимальный счёт из файла.
 * @return Возвращает значение максимального счёта.
 */
int highscoreRead();

/**
 * @brief Обновляет текущее состояние игры и возвращает его.
 *
 * Эта функция обновляет состояние игры, используя текущие данные и параметры.
 * Вызывает функцию `calcTet`, чтобы обновить состояние тетромино.
 * Если игра не завершена, она обновляет внутренние данные, такие как поле для
 * отображения и следующая фигура. Обновляет информацию о счете, максимальном
 * счете, уровне, скорости и паузе.
 * @return Обновленное состояние игры в виде структуры `GameInfo_t`.
 */
GameInfo_t updateCurrentState();

/**
 * @brief Освобождает память, выделенную под двумерный массив `print_field`.
 *
 * @param print_field Двумерный массив целых чисел, представляющий собой поле
 * для печати.
 * @param height Высота массива.
 */
void freePrintField(int** print_field, int height);

/**
 * @brief Освобождает память, выделенную под двумерный массив `next`.
 *
 * @param next Двумерный массив целых чисел, представляющий собой следующую
 * фигуру.
 * @param size Размер массива.
 */
void freeNext(int** next, int size);

/**
 * @brief Освобождает память, выделенную под игровое поле.
 *
 * @param tetf Указатель на структуру поля, которую необходимо освободить.
 */
void freeTetField(TetField* tetf);

/**
 * @brief Освобождает память, выделенную под фигуру.
 *
 * @param tf Указатель на структуру фигуры, которую необходимо освободить.
 */
void freeTetFigure(TetFigure* tf);

/**
 * @brief Освобождает память, выделенную под шаблоны фигур.
 *
 * @param tetft Указатель на структуру `TetTemplates`, представляющую собой
 * шаблоны фигур.
 */
void freeTetTemplates(TetTemplates* tet_templates);

/**
 * @brief Освобождает память, занятую полем для отображения игры и следующей
 фигурой.

 *
 * @param game Текущие данные игры, включая указатели на поле и следующую
 фигуру.
 * @param size Размер следующей фигуры.
 * @param height Высота поля для отображения игры.
*/
void freeResources(GameInfo_t game, int size, int height);

/**
 * @brief Освобождает всю память, выделенную под игру.
 *
 * @param game Указатель на структуру `GameInfo_t`, представляющую собой
 * информацию.
 */
void freeGame(GameInfo_t* game);

extern GameInfo_t* game;
#endif