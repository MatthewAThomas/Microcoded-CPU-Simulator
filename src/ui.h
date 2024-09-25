void print_bus(void);
void print_micro_op(void);
void print_registers(void);
void print_memory(void);

/* Called by ui.c. Will call all the above functions. */
void print_state(char *micro_op_label);


