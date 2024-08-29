#include "templates.h"

#include <stdio.h>
#include <stdlib.h>

TetBlock tet_template1[TET_TEMPLATE_SIZE][TET_TEMPLATE_SIZE] = {
    {{0}, {0}, {0}, {0}, {0}},
    {{0}, {1}, {1}, {0}, {0}},
    {{0}, {0}, {1}, {1}, {0}},
    {{0}, {0}, {0}, {0}, {0}},
    {{0}, {0}, {0}, {0}, {0}}};

TetBlock tet_template2[TET_TEMPLATE_SIZE][TET_TEMPLATE_SIZE] = {
    {{0}, {0}, {0}, {0}, {0}},
    {{0}, {0}, {1}, {0}, {0}},
    {{0}, {1}, {1}, {1}, {0}},
    {{0}, {0}, {0}, {0}, {0}},
    {{0}, {0}, {0}, {0}, {0}}};

TetBlock tet_template3[TET_TEMPLATE_SIZE][TET_TEMPLATE_SIZE] = {
    {{0}, {0}, {0}, {0}, {0}},
    {{0}, {0}, {0}, {0}, {0}},
    {{1}, {1}, {1}, {1}, {0}},
    {{0}, {0}, {0}, {0}, {0}},
    {{0}, {0}, {0}, {0}, {0}}};

TetBlock tet_template4[TET_TEMPLATE_SIZE][TET_TEMPLATE_SIZE] = {
    {{0}, {0}, {0}, {0}, {0}},
    {{0}, {1}, {0}, {0}, {0}},
    {{0}, {1}, {1}, {1}, {0}},
    {{0}, {0}, {0}, {0}, {0}},
    {{0}, {0}, {0}, {0}, {0}}};

TetBlock tet_template5[TET_TEMPLATE_SIZE][TET_TEMPLATE_SIZE] = {
    {{0}, {0}, {0}, {0}, {0}},
    {{0}, {0}, {0}, {1}, {0}},
    {{0}, {1}, {1}, {1}, {0}},
    {{0}, {0}, {0}, {0}, {0}},
    {{0}, {0}, {0}, {0}, {0}}};

TetBlock tet_template6[TET_TEMPLATE_SIZE][TET_TEMPLATE_SIZE] = {
    {{0}, {0}, {0}, {0}, {0}},
    {{0}, {1}, {1}, {0}, {0}},
    {{0}, {1}, {1}, {0}, {0}},
    {{0}, {0}, {0}, {0}, {0}},
    {{0}, {0}, {0}, {0}, {0}}};

TetBlock tet_template7[TET_TEMPLATE_SIZE][TET_TEMPLATE_SIZE] = {
    {{0}, {0}, {0}, {0}, {0}},
    {{0}, {0}, {1}, {1}, {0}},
    {{0}, {1}, {1}, {0}, {0}},
    {{0}, {0}, {0}, {0}, {0}},
    {{0}, {0}, {0}, {0}, {0}}};

TetBlock *tet_templates[] = {
    (TetBlock *)tet_template1, (TetBlock *)tet_template2,
    (TetBlock *)tet_template3, (TetBlock *)tet_template4,
    (TetBlock *)tet_template5, (TetBlock *)tet_template6,
    (TetBlock *)tet_template7};
