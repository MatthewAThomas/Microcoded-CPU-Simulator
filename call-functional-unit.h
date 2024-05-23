/* Defines an interface for interacting with functional units.
   Each cycle is broken into two steps:
    - write:
        - each functional unit reads its inputs and executes, writing data to databus if necessary
    - load: all registers and the memory unit load from the databus if signaled to
*/

/* Memory Unit */
bool init_memory_unit(void);
void exec_memory_unit(void);

/* Immediate Select Unit */
void init_imm_sel_unit(void);
void exec_imm_sel_unit(void);

/* ALU Unit */
void init_alu_unit(void);
void exec_alu_unit(void);

/* Register File Unit and other special registers */
void init_regs(void);
void write_regs(void);
void load_regs(void);