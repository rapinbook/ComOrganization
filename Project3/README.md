# Project 3. MIPS Pipelined Simulator
Skeleton developed by CMU,
modified for KAIST CS311 purpose by THKIM, BKKIM and SHJEON.

## Instructions
There are three files you may modify: `util.h`, `run.h`, and `run.c`.

### 1. util.h

We have setup the basic CPU\_State that is sufficient to implement the project.
However, you may decide to add more variables, and modify/remove any misleading variables.

### 2. run.h

You may add any additional functions that will be called by your implementation of `process_instruction()`.
In fact, we encourage you to split your implementation of `process_instruction()` into many other helping functions.
You may decide to have functions for each stages of the pipeline.
Function(s) to handle flushes (adding bubbles into the pipeline), etc.

### 3. run.c

**Implement** the following function:

    void process_instruction()

The `process_instruction()` function is used by the `cycle()` function to simulate a `cycle` of the pipelined simulator.
Each `cycle()` the pipeline will advance to the next instruction (if there are no stalls/hazards, etc.).
Your internal register, memory, and pipeline register state should be updated according to the instruction
that is being executed at each stage.


In util.h
	For PIPE_SWITCH, we use this to see whether we will process that stage or not. ID_EX_DEST_JR for jr target. FLAG_LW for load word instruction. BRANCH_PC BRANCH_COUND BRANCH_PRINT for branch print and branch flush and loop. EACH_STALL and TOTAL_STALL for adding the number of stall to the CURRENT_STATE.PC FLAG_JUMP for jump instruction and NOP for add 0 0 0 instruction