#ifndef UI_H
#define UI_H

#include "microcode.h"

/* Called by ui.c. Will call all the above functions. */
int print_state(micro_op *op);

#endif // UI_H