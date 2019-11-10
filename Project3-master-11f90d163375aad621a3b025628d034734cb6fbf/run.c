/***************************************************************/
/*                                                             */
/*   MIPS-32 Instruction Level Simulator                       */
/*                                                             */
/*   CS311 KAIST                                               */
/*   run.c                                                     */
/*                                                             */
/***************************************************************/

#include <stdio.h>

#include "util.h"
#include "run.h"

/***************************************************************/
/*                                                             */
/* Procedure: get_inst_info                                    */
/*                                                             */
/* Purpose: Read insturction information                       */
/*                                                             */
/***************************************************************/
instruction* get_inst_info(uint32_t pc) {
    return &INST_INFO[(pc - MEM_TEXT_START) >> 2];
}


/***************************************************************/
/*                                                             */
/* Procedure: process_instruction                              */
/*                                                             */
/* Purpose: Process one instrction                             */
/*                                                             */
/***************************************************************/
void process_instruction(){
	/** Your implementation here */

	// For testing
	/*
	if (CYCLE_COUNT >= 172) {
        RUN_BIT = FALSE;
	}
	*/


	//printf("INSTRUCTION COUNT %d\n", (int)NUM_INST);

	//int if_flag, id_flag, exe_flag, mem_flag, wb_flag = 0;

	int k,chk=0,k1,i,b=0;
	uint32_t tmp;
	//FETCH_BIT = 1;
	uint32_t PC = CURRENT_STATE.PC;

	instruction* inst = get_inst_info(PC);
	//initialize all value
	//some value has been initialized already in cs311.c

	if(PC==0x400000){
	CURRENT_STATE.ID_EX_IMM = 0;
	CURRENT_STATE.ID_EX_DEST=0;
	CURRENT_STATE.REGS[0] = 0;
	//EX_MEM_latch
	CURRENT_STATE.EX_MEM_NPC=0;
	CURRENT_STATE.EX_MEM_ALU_OUT = 0;
	CURRENT_STATE.EX_MEM_W_VALUE = 0;
	CURRENT_STATE.EX_MEM_BR_TARGET = 0;
	CURRENT_STATE.EX_MEM_BR_TAKE = 0;
	CURRENT_STATE.EX_MEM_DEST=0;

	//MEM_WB_latch
	CURRENT_STATE.MEM_WB_NPC = 0;
	CURRENT_STATE.MEM_WB_ALU_OUT = 0;
	CURRENT_STATE.MEM_WB_MEM_OUT = 0;
	CURRENT_STATE.MEM_WB_BR_TAKE = 0;
	CURRENT_STATE.MEM_WB_DEST = 0;

	//Forwarding
	CURRENT_STATE.EX_MEM_FORWARD_REG = 0;
	CURRENT_STATE.MEM_WB_FORWARD_REG = 0;
	CURRENT_STATE.EX_MEM_FORWARD_VALUE = 0;
	CURRENT_STATE.MEM_WB_FORWARD_VALUE = 0;

	//To choose right PC
	CURRENT_STATE.FLAG_LW = 0;
	CURRENT_STATE.IF_PC = 0;
	CURRENT_STATE.JUMP_PC = 0;
	CURRENT_STATE.BRANCH_PC = 0;
	CURRENT_STATE.BRANCH_COUNT = 0;
	CURRENT_STATE.BRANCH_PRINT = 0;
	CURRENT_STATE.EACH_STALL = 0;
	CURRENT_STATE.TOTAL_STALL = 0;
	CURRENT_STATE.FLAG_JUMP = 0;
	CURRENT_STATE.NOP_FLAG = 0;

	}
	if(PC>=0x400000+(NUM_INST*4)||PC<0x400000){

		FETCH_BIT = FALSE;
		CURRENT_STATE.PIPE_SWITCH[0] = 0;

	}
	//printf("OMG\n");
	//if there is new instruction to fetch
	if(FETCH_BIT==TRUE){
		//printf("HEY\n");
		CURRENT_STATE.PIPE_SWITCH[0] = 1;
	}
	//printf("IF get PIPE : %x\n",CURRENT_STATE.PIPE[IF_STAGE]);
	//WriteBack STAGE
	if(CURRENT_STATE.PIPE_SWITCH[WB_STAGE] == 1){
//printf("HEY1\n");
        //printf(" MEM_WB_PC  %x\n ",CURRENT_STATE.MEM_WB_NPC);
        //printf(" CURRENT_PC  %x\n ",CURRENT_STATE.PC);

		instruction* inst = get_inst_info(CURRENT_STATE.MEM_WB_NPC);
		if(CURRENT_STATE.MEM_WB_JUMPTAKEN == 1){
            INSTRUCTION_COUNT--;
            CURRENT_STATE.MEM_WB_JUMPTAKEN = 0;
            CURRENT_STATE.EX_MEM_JUMPTAKEN = 0;
            CURRENT_STATE.ID_EX_JUMPTAKEN = 0;

        }

		CURRENT_STATE.PIPE[4] = CURRENT_STATE.PIPE[MEM_STAGE];
		//printf("IF HERE1 get PIPE : %x\n",CURRENT_STATE.MEM_WB_NPC);


        switch(inst->opcode)
	    {

	    	//R type
	        case 0x0:
				//keep the number of reg, not the value in reg
				//printf("IF be4 inside get PIPE : %x\n",CURRENT_STATE.PIPE[IF_STAGE]);
				//tmp = CURRENT_STATE.PIPE[IF_STAGE];
				//printf("FUNC: %x MEM :%x\n",FUNC(inst),CURRENT_STATE.MEM_WB_ALU_OUT);
				if(FUNC(inst)==0x21){
                    if(CURRENT_STATE.NOP_FLAG == 1){

                            INSTRUCTION_COUNT++;
                        //printf("HEREEEEEEEEEEEEEEEEEEEEEE\n");
                        break;
                    }else{
                    INSTRUCTION_COUNT++;


                    CURRENT_STATE.REGS[RD(inst)] = CURRENT_STATE.MEM_WB_ALU_OUT;
                    }

				}else{

                INSTRUCTION_COUNT++;
				CURRENT_STATE.REGS[RD(inst)] = CURRENT_STATE.MEM_WB_ALU_OUT;
				}


				//CURRENT_STATE.PIPE[IF_STAGE] = tmp;
	            //printf("IF inside get PIPE : %x\n",CURRENT_STATE.PIPE[IF_STAGE]);
				break;
			//I type
			case 0x9:		//(0x001001)ADDIU
                INSTRUCTION_COUNT++;
			    CURRENT_STATE.REGS[RT(inst)] = CURRENT_STATE.MEM_WB_ALU_OUT;
			    break;
			case 0xc:		//(0x001100)ANDI
			    INSTRUCTION_COUNT++;
			    CURRENT_STATE.REGS[RT(inst)] = CURRENT_STATE.MEM_WB_ALU_OUT;
			    break;
			case 0xf:		//(0x001111)LUI
			    INSTRUCTION_COUNT++;
			    CURRENT_STATE.REGS[RT(inst)] = CURRENT_STATE.MEM_WB_ALU_OUT;
			    break;
			case 0xd:		//(0x001101)ORI
			    INSTRUCTION_COUNT++;
			    CURRENT_STATE.REGS[RT(inst)] = CURRENT_STATE.MEM_WB_ALU_OUT;

			    break;
	        case 0xb:		//(0x001011)SLTIU
	            INSTRUCTION_COUNT++;
	            CURRENT_STATE.REGS[RT(inst)] = CURRENT_STATE.MEM_WB_ALU_OUT;
			    break;
			case 0x23:		//(0x100011)LW
			    INSTRUCTION_COUNT++;
			    CURRENT_STATE.REGS[RT(inst)] = CURRENT_STATE.MEM_WB_MEM_OUT;
			    break;
			case 0x2b:		//(0x101011)SW nothing
                INSTRUCTION_COUNT++;
			    break;
	        case 0x4:		//(0x000100)BEQ

                if(CURRENT_STATE.MEM_WB_BR_TAKE == 1){
                    INSTRUCTION_COUNT -= 2;
                }else{
                    INSTRUCTION_COUNT++;
                }
	            break;
	        case 0x5:		//(0x000101)BNE
                 if(CURRENT_STATE.MEM_WB_BR_TAKE == 1){
                    INSTRUCTION_COUNT -= 2;
                }else{
                    INSTRUCTION_COUNT++;
                }
	            break;
			//TYPE J
			case 0x2:		//(0x000010)J
			    INSTRUCTION_COUNT++;
			    break;
			case 0x3:		//(0x000011)JAL
				//idk
				INSTRUCTION_COUNT++;
				break;
	    }


		//printf("IF HERE2 get PIPE : %x\n",CURRENT_STATE.PIPE[IF_STAGE]);
		CURRENT_STATE.PIPE_SWITCH[WB_STAGE] = 0;
		/*if(CURRENT_STATE.PIPE_STALL[4] == 1){
                CURRENT_STATE.PIPE[4] = 0;
                CURRENT_STATE.PIPE_STALL[4] = 0;
                //CURRENT_STATE.PIPE_STALL[4] = 1;

		}*/
	}
//printf("IF 2 get PIPE : %x\n",CURRENT_STATE.PIPE[IF_STAGE]);
	//MEMORY ALLOCATION STAGE
	if(CURRENT_STATE.PIPE_SWITCH[MEM_STAGE] == 1){
		CURRENT_STATE.MEM_WB_NPC = CURRENT_STATE.EX_MEM_NPC;
		CURRENT_STATE.PIPE[MEM_STAGE] = CURRENT_STATE.PIPE[EX_STAGE];
		CURRENT_STATE.MEM_WB_JUMPTAKEN = CURRENT_STATE.EX_MEM_JUMPTAKEN;
		instruction *inst = get_inst_info(CURRENT_STATE.EX_MEM_NPC);
//printf("HEY2\n");
	    switch(inst->opcode)
	    {
		case 0x23:		//(0x100011)LW
	        //printf("LW\n");


	        CURRENT_STATE.MEM_WB_MEM_OUT = mem_read_32(CURRENT_STATE.EX_MEM_W_VALUE);
	        //CURRENT_STATE.PC += 4;
	        break;


	    case 0x2b:		//(0x101011)SW
	        //printf("SW\n");
	        mem_write_32(CURRENT_STATE.EX_MEM_W_VALUE,CURRENT_STATE.MEM_WB_MEM_OUT);
	        //CURRENT_STATE.PC += 4;
	        break;
        case 0x4:		//(0x000100)BEQ
            CURRENT_STATE.BRANCH_PC = CURRENT_STATE.EX_MEM_BR_TARGET;
	        CURRENT_STATE.MEM_WB_BR_TAKE = CURRENT_STATE.EX_MEM_BR_TAKE;
            break;
	    case 0x5:		//(0x000101)BNE
            CURRENT_STATE.BRANCH_PC = CURRENT_STATE.EX_MEM_BR_TARGET;
	        CURRENT_STATE.MEM_WB_BR_TAKE = CURRENT_STATE.EX_MEM_BR_TAKE;
            break;
		case 0xf:		//(0x001111)LUI

	        CURRENT_STATE.MEM_WB_ALU_OUT = CURRENT_STATE.EX_MEM_ALU_OUT;
	        //CURRENT_STATE.PC += 4;
	        //printf("LUI %x\n",CURRENT_STATE.EX_MEM_ALU_OUT);
	        break;

	    case 0xd:		//(0x001101)ORI
	        CURRENT_STATE.MEM_WB_ALU_OUT = CURRENT_STATE.EX_MEM_ALU_OUT;
	        //CURRENT_STATE.PC += 4;
	        //printf("ORI %x\n",CURRENT_STATE.EX_MEM_ALU_OUT);
	        break;
        default :
            CURRENT_STATE.MEM_WB_ALU_OUT = CURRENT_STATE.EX_MEM_ALU_OUT;
            break;
	    }
	    //for forwarding
	    CURRENT_STATE.MEM_WB_DEST = CURRENT_STATE.EX_MEM_DEST;

		CURRENT_STATE.PIPE_SWITCH[MEM_STAGE] = 0;
		CURRENT_STATE.PIPE_SWITCH[WB_STAGE] = 1;
		/*if(CURRENT_STATE.PIPE_STALL[3] == 1){
                CURRENT_STATE.PIPE[3] = 0;
                CURRENT_STATE.PIPE_STALL[3] = 0;
                CURRENT_STATE.PIPE_STALL[4] = 1;

		}*/
	}else{
	    CURRENT_STATE.PIPE[3] = 0;

	}

	//EXECUTE INSTRUCTION
	if(CURRENT_STATE.PIPE_SWITCH[EX_STAGE] == 1){
//printf("HEY3\n");
	    CURRENT_STATE.EX_MEM_NPC = CURRENT_STATE.ID_EX_NPC;
	    instruction *inst = get_inst_info(CURRENT_STATE.ID_EX_NPC);
	    CURRENT_STATE.PIPE[EX_STAGE] = CURRENT_STATE.PIPE[ID_STAGE];
	    CURRENT_STATE.EX_MEM_JUMPTAKEN = CURRENT_STATE.ID_EX_JUMPTAKEN;


	    //CURRENT_STATE.EX_MEM_3rd_INST = inst;
	    //stall
	    if(CURRENT_STATE.PIPE_STALL[EX_STAGE]==TRUE){
			CURRENT_STATE.PIPE_STALL[EX_STAGE] = FALSE;
			//what if there is forward??? solve that later
			//addu $0,$0,$0

			inst->opcode = 0;
			inst->func_code = 0x21;
			CURRENT_STATE.NOP_FLAG = 1;

	    }

	    if(CURRENT_STATE.EX_MEM_BR_TAKE == 1){
            inst->opcode = 0;
			inst->func_code = 0x21;
			CURRENT_STATE.NOP_FLAG = 1;

        }




		if(CURRENT_STATE.EX_MEM_FORWARD_REG != 0){
				//compared register is the same as register that used in this instruction or not
				//change the value of it (forward value)
				//printf("HEY3 after\n");
			if(CURRENT_STATE.EX_MEM_FORWARD_REG==RS(inst)){

				CURRENT_STATE.ID_EX_REG1 = CURRENT_STATE.EX_MEM_FORWARD_VALUE;
			}
		//here it is RT
			if(CURRENT_STATE.EX_MEM_FORWARD_REG==RT(inst)){

				CURRENT_STATE.ID_EX_REG2 = CURRENT_STATE.EX_MEM_FORWARD_VALUE;
			}
		}
		//if there is a forward from MEM/WB
		if(CURRENT_STATE.MEM_WB_FORWARD_REG != 0){
				//compared register is the same as register that used in this instruction or not
				//change the value of it (forward value)
				//compared unsigned char
//printf("HEY4 after\n");
			if(CURRENT_STATE.MEM_WB_FORWARD_REG==RS(inst)){

                //CURRENT_STATE.MEM_WB_FORWARD_VALUE = 268435468;

				CURRENT_STATE.ID_EX_REG1 = CURRENT_STATE.MEM_WB_FORWARD_VALUE;
			}
		//here it is RT
			if(CURRENT_STATE.MEM_WB_FORWARD_REG==RT(inst)){


				CURRENT_STATE.ID_EX_REG2 = CURRENT_STATE.MEM_WB_FORWARD_VALUE;
			}
		}





	    switch(inst->opcode)
	{
	    //Type I
	    case 0x9:		//(0x001001)ADDIU
	        CURRENT_STATE.EX_MEM_ALU_OUT = ((unsigned int)CURRENT_STATE.ID_EX_REG1 + (unsigned int)CURRENT_STATE.ID_EX_IMM);
	        //printf("$8 valueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee %d\n",CURRENT_STATE.EX_MEM_ALU_OUT);
	        //CURRENT_STATE.PC += 4;
			//printf("ADDIUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU %x ",CURRENT_STATE.ID_EX_IMM);

	        break;
	    case 0xc:		//(0x001100)ANDI
	        CURRENT_STATE.EX_MEM_ALU_OUT = (CURRENT_STATE.ID_EX_REG1 & CURRENT_STATE.ID_EX_IMM);

	        //CURRENT_STATE.PC += 4;
	         //printf("ADDI\n");
	        break;
	    case 0xf:		//(0x001111)LUI

	        CURRENT_STATE.EX_MEM_ALU_OUT = SIGN_EX(CURRENT_STATE.ID_EX_IMM)<<16;
	        //CURRENT_STATE.PC += 4;
	        //printf("LUI %x\n",CURRENT_STATE.EX_MEM_ALU_OUT);
	        break;

	    case 0xd:		//(0x001101)ORI
	        CURRENT_STATE.EX_MEM_ALU_OUT = (CURRENT_STATE.ID_EX_REG1)|(CURRENT_STATE.ID_EX_IMM);
	        //CURRENT_STATE.PC += 4;
	        //printf("ORI %x\n",CURRENT_STATE.EX_MEM_ALU_OUT);
	        break;

	    case 0xb:		//(0x001011)SLTIU
	        //printf("SLTIU\n");
	        if((unsigned int)CURRENT_STATE.ID_EX_REG1 < (unsigned int)(CURRENT_STATE.ID_EX_IMM)){
                CURRENT_STATE.EX_MEM_ALU_OUT = 1;
            }else{
                CURRENT_STATE.EX_MEM_ALU_OUT = 0;

            }
            //CURRENT_STATE.PC += 4;
	        break;
	    case 0x23:		//(0x100011)LW
	        //keep address

	        CURRENT_STATE.EX_MEM_W_VALUE = CURRENT_STATE.ID_EX_REG1 + SIGN_EX(CURRENT_STATE.ID_EX_IMM);
	        //CURRENT_STATE.PC += 4;
	        break;


	    case 0x2b:		//(0x101011)SW
	        //keep address
	        CURRENT_STATE.EX_MEM_W_VALUE = CURRENT_STATE.ID_EX_REG1 + SIGN_EX(CURRENT_STATE.ID_EX_IMM);
	        //mem_write_32(CURRENT_STATE.REGS[RS(inst)] +SIGN_EX(IMM(inst)),CURRENT_STATE.REGS[RT(inst)]);
	        //CURRENT_STATE.PC += 4;
	        break;
	    case 0x4:		//(0x000100)BEQ
	        //printf("BEQ\n");
	        if (CURRENT_STATE.ID_EX_REG1 == CURRENT_STATE.REGS[CURRENT_STATE.ID_EX_DEST]){
                CURRENT_STATE.EX_MEM_BR_TAKE = 1;
                CURRENT_STATE.EX_MEM_BR_TARGET = CURRENT_STATE.EX_MEM_NPC+ 4  +(CURRENT_STATE.ID_EX_IMM<<2);
                }
            else{
                CURRENT_STATE.EX_MEM_BR_TAKE = 2;//for stall

                        //CURRENT_STATE.PC += 4;

            }
            break;
	    case 0x5:		//(0x000101)BNE
	        //printf("BNE\n");
	         if (CURRENT_STATE.ID_EX_REG1 != CURRENT_STATE.REGS[CURRENT_STATE.ID_EX_DEST]){
                //printf("BR takennnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn\n");
                //printf("BR %x\n",CURRENT_STATE.ID_EX_NPC);
                //printf("BR %x\n",CURRENT_STATE.REGS[CURRENT_STATE.ID_EX_DEST]);
                CURRENT_STATE.EX_MEM_BR_TAKE = 1;
                CURRENT_STATE.EX_MEM_BR_TARGET = CURRENT_STATE.EX_MEM_NPC + 4 + (CURRENT_STATE.ID_EX_IMM<<2);
                }
            else{
                //printf("BR NOT taken\n");
                CURRENT_STATE.EX_MEM_BR_TAKE = 2;//CURRENT_STATE.PC += 4;

            }
            break;

    	    //TYPE R
	    case 0x0:		//(0x000000)ADDU, AND, NOR, OR, SLTU, SLL, SRL, SUBU  if JR
	        switch(FUNC(inst))
	        {
                case 0x21://ADDU
                    CURRENT_STATE.EX_MEM_ALU_OUT = (unsigned int)CURRENT_STATE.ID_EX_REG1 + (unsigned int)CURRENT_STATE.ID_EX_REG2;
					//printf("ADDUOHHHHHHHHHHHHHHHHHH : %x\n",CURRENT_STATE.ID_EX_REG1);


                    //CURRENT_STATE.PC += 4;

                    break;
                case 0x24://AND
                    CURRENT_STATE.EX_MEM_ALU_OUT = CURRENT_STATE.ID_EX_REG1 & CURRENT_STATE.ID_EX_REG2;
                    //CURRENT_STATE.PC += 4;
                    //printf("AND\n");
                    break;
                case 0x27://NOR
                    CURRENT_STATE.EX_MEM_ALU_OUT = ~(CURRENT_STATE.ID_EX_REG1| CURRENT_STATE.ID_EX_REG2);
                    //CURRENT_STATE.PC += 4;
                    //printf("NOR\n");
                    break;
                case 0x25://OR
                    CURRENT_STATE.EX_MEM_ALU_OUT = (CURRENT_STATE.ID_EX_REG1) | (CURRENT_STATE.ID_EX_REG2);
                    //CURRENT_STATE.PC += 4;
                    //printf("OR\n");
                    break;
                case 0x2b://SLTU
                    //printf("SLTU\n");
                    if((unsigned int)CURRENT_STATE.ID_EX_REG1 < (unsigned int)CURRENT_STATE.ID_EX_REG2){
                        CURRENT_STATE.EX_MEM_ALU_OUT = 1;
                        //CURRENT_STATE.PC += 4;



                    }else{
                        CURRENT_STATE.EX_MEM_ALU_OUT = 0;
                        //CURRENT_STATE.PC += 4;




                    }
                    break;
                case 0x0://SLL

                    CURRENT_STATE.EX_MEM_ALU_OUT =  CURRENT_STATE.ID_EX_REG2<<SHAMT(inst);
                    //CURRENT_STATE.PC += 4;
                    //printf("Sll\n");
                    break;

                case 0x2://SRL

                	if(CURRENT_STATE.ID_EX_REG2<0){
						k = 0x80000000;
						k1 = k>>SHAMT(inst);
						k = ~k;
						CURRENT_STATE.EX_MEM_ALU_OUT = (CURRENT_STATE.ID_EX_REG2&k)>>SHAMT(inst);
						CURRENT_STATE.EX_MEM_ALU_OUT = CURRENT_STATE.EX_MEM_ALU_OUT&k1;
						break;
                	}
                	else{
                    CURRENT_STATE.EX_MEM_ALU_OUT =  CURRENT_STATE.ID_EX_REG2>>SHAMT(inst);

                    //CURRENT_STATE.PC += 4;
                    //printf("Srl\n");
                    break;
                	}
                    break;
                case 0x23://SUBU
                    CURRENT_STATE.EX_MEM_ALU_OUT = (unsigned int)CURRENT_STATE.ID_EX_REG1 - (unsigned int)CURRENT_STATE.ID_EX_REG2;
                    CURRENT_STATE.EX_MEM_ALU_OUT = (unsigned int)CURRENT_STATE.EX_MEM_ALU_OUT;
                    //CURRENT_STATE.PC += 4;
                    //printf("SUBU\n");
                    break;

                case 0x08://JR
                    /*CURRENT_STATE.PC = CURRENT_STATE.ID_EX_REG1;
                    CURRENT_STATE.EACH_STALL = 1;
                    flag_Jump = 1;*/
                    //printf("JR\n");
                    break;

	        }
	        break;


    	    //TYPE J
	    case 0x2:		//(0x000010)J
	    case 0x3:		//(0x000011)JAL
            break;


	    default:
			break;
	}

	if(CURRENT_STATE.FLAG_JR == 1){
            inst->opcode = 0;
			inst->func_code = 0x08;
			CURRENT_STATE.FLAG_JR = 0;
			CURRENT_STATE.NOP_FLAG = 1;
        }
    /*if(CURRENT_STATE.FLAG_J == 1){
            inst->opcode = 0x2;
			CURRENT_STATE.FLAG_J = 0;
			//CURRENT_STATE.NOP_FLAG = 1;
        }
    if(CURRENT_STATE.FLAG_JAL == 1){
            inst->opcode = 0x3;

			CURRENT_STATE.FLAG_JAL = 0;
			//CURRENT_STATE.NOP_FLAG = 1;
        }*/


		//for forwarding
		CURRENT_STATE.EX_MEM_DEST = CURRENT_STATE.ID_EX_DEST;
		//for cycle
		CURRENT_STATE.PIPE_SWITCH[EX_STAGE] = 0;
		CURRENT_STATE.PIPE_SWITCH[MEM_STAGE] = 1;

	}else{
	    CURRENT_STATE.PIPE[2] = 0;

	}
	//Decoder Instruction
	if(CURRENT_STATE.PIPE_SWITCH[ID_STAGE] == 1 ){
        CURRENT_STATE.ID_EX_NPC  = CURRENT_STATE.IF_ID_NPC;//?????????? still confused this thing
        instruction *inst = get_inst_info(CURRENT_STATE.IF_ID_NPC);
		//printf("ID get PIPE : %x\n",CURRENT_STATE.PIPE[IF_STAGE]);
		CURRENT_STATE.PIPE[ID_STAGE] = CURRENT_STATE.PIPE[IF_STAGE];



	    switch(inst->opcode)
	    {


	    	//R type
	        case 0x0:
				//keep the number of reg, not the value in reg
				if(FUNC(inst)==0x08){

					//printf("LAST: %x\n",CURRENT_STATE.REGS[RS(inst)]);
					//CURRENT_STATE.ID_EX_REG1 = CURRENT_STATE.REGS[RS(inst)];
					CURRENT_STATE.JUMP_PC = CURRENT_STATE.REGS[RS(inst)];
                    CURRENT_STATE.EACH_STALL = 1;
                    CURRENT_STATE.FLAG_JUMP = 1;
                    CURRENT_STATE.FLAG_JR = 1;
                    CURRENT_STATE.EX_MEM_DEST = 0;
                    CURRENT_STATE.ID_EX_JUMPTAKEN = 1;
                    break;
				}
				else if(RT(inst) == RS(inst)){

                        CURRENT_STATE.ID_EX_REG2 = CURRENT_STATE.REGS[RT(inst)];
                        CURRENT_STATE.ID_EX_REG1 = CURRENT_STATE.ID_EX_REG2;


				}else{

                CURRENT_STATE.ID_EX_REG2 = CURRENT_STATE.REGS[RT(inst)];
	            CURRENT_STATE.ID_EX_REG1 = CURRENT_STATE.REGS[RS(inst)];

	            CURRENT_STATE.ID_EX_DEST = RD(inst);

				break;

				}

			//I type
			case 0x9:		//(0x001001)ADDIU

			case 0xc:		//(0x001100)ANDI

			case 0xf:		//(0x001111)LUI

			case 0xd:		//(0x001101)ORI

	        case 0xb:		//(0x001011)SLTIU

			case 0x23:		//(0x100011)LW

			case 0x2b:		//(0x101011)SW

	        case 0x4:		//(0x000100)BEQ


	        case 0x5:		//(0x000101)BNE
	            //printf("BNE\n");
                CURRENT_STATE.ID_EX_REG1 = CURRENT_STATE.REGS[RS(inst)];
                CURRENT_STATE.ID_EX_DEST = RT(inst);

                CURRENT_STATE.ID_EX_IMM  = IMM(inst);




				break;

			//TYPE J we consider branch taken here.
	    case 0x2:		//(0x000010)J
	        //printf("J\n");
            CURRENT_STATE.JUMP_PC = ( CURRENT_STATE.EX_MEM_NPC & 0xf0000000)|(TARGET(inst)*4);

            CURRENT_STATE.EACH_STALL = 1;
            CURRENT_STATE.FLAG_JUMP = 1;
            CURRENT_STATE.EX_MEM_DEST = 0;
            CURRENT_STATE.FLAG_J = 1;
            CURRENT_STATE.ID_EX_JUMPTAKEN = 1;


            break;

	    case 0x3:		//(0x000011)JAL
	        //printf("JAL\n");
	        //printf("EX_MEM_NPC %x\n",CURRENT_STATE.EX_MEM_NPC);

	        CURRENT_STATE.REGS[31] = CURRENT_STATE.EX_MEM_NPC + 12;
	        CURRENT_STATE.JUMP_PC = ( CURRENT_STATE.EX_MEM_NPC & 0xf0000000)|(TARGET(inst) <<2);
	        CURRENT_STATE.FLAG_JUMP = 1;
	        CURRENT_STATE.EACH_STALL = 1;
	        CURRENT_STATE.EX_MEM_DEST = 0;
	        CURRENT_STATE.FLAG_JAL = 1;
	        CURRENT_STATE.ID_EX_JUMPTAKEN = 1;

            break;

	    }
		//stall by misprediction of branch

	    /*CURRENT_STATE.PIPE[2] = CURRENT_STATE.PIPE[1] ;
	    CURRENT_STATE.PIPE[1] = CURRENT_STATE.PIPE[0] ;
	    CURRENT_STATE.PIPE[0] += 4;*/
	    //forward data hazard ( add $1
		//		add $2, $1,$5
//printf("AFTER\n");
	    CURRENT_STATE.EX_MEM_FORWARD_REG = 0; //??? or 0
	    CURRENT_STATE.MEM_WB_FORWARD_REG = 0;
	    //not cover lw sw yet
	    //compare the number of register
	    //ALU data hazard
		//printf("PC::::%x\n",CURRENT_STATE.ID_EX_NPC);
        if(CURRENT_STATE.EX_MEM_DEST!=0&&CURRENT_STATE.EX_MEM_DEST==RS(inst)){
				//printf("11111111111111111\n");
			CURRENT_STATE.EX_MEM_FORWARD_REG = CURRENT_STATE.EX_MEM_DEST;
			CURRENT_STATE.EX_MEM_FORWARD_VALUE = CURRENT_STATE.EX_MEM_ALU_OUT; // value of the register we want to forward
        }
        if(CURRENT_STATE.EX_MEM_DEST!=0&&CURRENT_STATE.EX_MEM_DEST==RT(inst)){
        	//printf("22222222222222\n");
			CURRENT_STATE.EX_MEM_FORWARD_REG = CURRENT_STATE.EX_MEM_DEST;
			CURRENT_STATE.EX_MEM_FORWARD_VALUE = CURRENT_STATE.EX_MEM_ALU_OUT; // value of the register we want to forward
        }
        //ALU data harzard for MEM_WB
        if(CURRENT_STATE.MEM_WB_DEST!=0&&CURRENT_STATE.MEM_WB_DEST==RS(inst)){
			//printf("3333333333333\n");
			CURRENT_STATE.MEM_WB_FORWARD_REG = CURRENT_STATE.MEM_WB_DEST;
			CURRENT_STATE.MEM_WB_FORWARD_VALUE = CURRENT_STATE.MEM_WB_ALU_OUT; // value of the register we want to forward


        }
        if(CURRENT_STATE.MEM_WB_DEST!=0&&CURRENT_STATE.MEM_WB_DEST==RT(inst)){
//printf("4444444444444444\n");
			CURRENT_STATE.MEM_WB_FORWARD_REG = CURRENT_STATE.MEM_WB_DEST;
			CURRENT_STATE.MEM_WB_FORWARD_VALUE = CURRENT_STATE.MEM_WB_ALU_OUT; // value of the register we want to forward
        }




//printf("AFTER1 \n");
		//here forwarding of lw, then some instruction following lw. need one stall
        // for lw sw forwarding (MEM-WB) to MEM
		//stall
		if(CURRENT_STATE.PC > 0x400008){
		instruction *inst_1 = get_inst_info(CURRENT_STATE.EX_MEM_NPC);

		//printf("AFTER2 %d\n",CURRENT_STATE.EX_MEM_NPC);
		if(inst_1->opcode==0x23){
			//printf("WUT\n");
			//only when R type or sw after lw, will be stall. if not cycle count will not correct
			//what should we do the case sw after lw? even we dont have that in all example(check หลายทีละ ไม่มี)
			if(CURRENT_STATE.EX_MEM_DEST!=0&&CURRENT_STATE.EX_MEM_DEST==RT(inst)||CURRENT_STATE.EX_MEM_DEST==RS(inst)){
				CURRENT_STATE.EACH_STALL = 1;

			}

		}
		}

		CURRENT_STATE.PIPE_SWITCH[ID_STAGE] = 0;
		CURRENT_STATE.PIPE_SWITCH[EX_STAGE] = 1;
		if(CURRENT_STATE.EACH_STALL!=0){
				CURRENT_STATE.PIPE_SWITCH[IF_STAGE] = 1;
				//printf("EACH_STALL not WUWWWWWWWWWWWWWWWWWWWWWWWWWW %d\n",CURRENT_STATE.PIPE_STALL[1]);
			if(CURRENT_STATE.PIPE_STALL[1] < CURRENT_STATE.EACH_STALL){

				CURRENT_STATE.ID_EX_REG2 = 0;
				CURRENT_STATE.ID_EX_REG1 = 0;
				CURRENT_STATE.ID_EX_DEST = 0;
				CURRENT_STATE.PIPE_STALL[1]++;
				//stall for IF, PC must be the same
				//CURRENT_STATE.PIPE_STALL[IF_STAGE]=TRUE;
				CURRENT_STATE.PIPE_STALL[EX_STAGE]=TRUE;
				//printf("HERE : %x\n",CURRENT_STATE.PC);
				CURRENT_STATE.PC -=4;
                PC = CURRENT_STATE.PC;
			}
			else{
					//printf("TOTAL STALL: %d\n",CURRENT_STATE.FLAG_JUMP);
				CURRENT_STATE.TOTAL_STALL += CURRENT_STATE.EACH_STALL-1;
				CURRENT_STATE.PIPE_STALL[ID_STAGE]=FALSE;
				//CURRENT_STATE.PIPE_STALL[IF_STAGE]=FALSE;
				CURRENT_STATE.PIPE_STALL[EX_STAGE]=FALSE;
				CURRENT_STATE.EACH_STALL=0;
				CURRENT_STATE.PC +=4;
                PC = CURRENT_STATE.PC;
                if(PC>=0x400000+(NUM_INST*4)){
						//printf("CONFUSED\n");
					CURRENT_STATE.PIPE_SWITCH[IF_STAGE] = 0;
                }
                //if stall
				if(CURRENT_STATE.FLAG_JUMP == 1){

						CURRENT_STATE.ID_EX_REG2 = 0;
				CURRENT_STATE.ID_EX_REG1 = 0;
				CURRENT_STATE.ID_EX_DEST = 0;
					//CURRENT_STATE.TOTAL_STALL -= (CURRENT_STATE.EACH_STALL-1);
					//inst must be the one that we change to nop
					CURRENT_STATE.PIPE_SWITCH[IF_STAGE] = 1;
					//flag becomes false
					//CURRENT_STATE.PIPE_STALL[0]=FALSE;
					//pdf said we need excatly correct number of cycle (see in util.c increment variable CYCLE_COUNT in fuction cycle())
					CURRENT_STATE.PC = CURRENT_STATE.JUMP_PC;
					PC = CURRENT_STATE.PC;
					CURRENT_STATE.FLAG_JUMP = 0;
					//then it add+4 again in the end, so next cycle is the same instruction.
					//CURRENT_STATE.PIPE[IF_STAGE] = CURRENT_STATE.PC;
					//printf("FLAG JUMP : %x\n",CURRENT_STATE.PC);
					CURRENT_STATE.PIPE[ID_STAGE] = 0;
				}
			}

		}
		//printf("REGGGGGGGGGGGGG %d\n",CURRENT_STATE.ID_EX_DEST);

	}else{
	    CURRENT_STATE.PIPE[1] = 0;

	}
	//for branch print
	if(CURRENT_STATE.BRANCH_PRINT != 0){
			//printf("MAYBE\n");
		b=CURRENT_STATE.BRANCH_PRINT;
		CURRENT_STATE.BRANCH_PRINT++;
		if(b==1||b==2){
		CURRENT_STATE.PIPE[b] = 0;
		CURRENT_STATE.PIPE[b+1] = 0;
		CURRENT_STATE.PIPE[b+2] = 0;
		}
		if(b==3){
			CURRENT_STATE.PIPE[b] = 0;
			CURRENT_STATE.PIPE[b+1] = 0;
		}
		if(b==4){
			CURRENT_STATE.PIPE[b] = 0;
			CURRENT_STATE.BRANCH_PRINT = 0;
		}
	}
	//Fetch Instruction
	if(CURRENT_STATE.PIPE_SWITCH[IF_STAGE] == 1){
            //INSTRUCTION_COUNT++;

//printf("HEY5\n");

		//printf("IF STAGE : %x\n",)
        CURRENT_STATE.PIPE[IF_STAGE] = PC+(CURRENT_STATE.TOTAL_STALL*4)+((CURRENT_STATE.PIPE_STALL[1])*4);


		instruction* inst = get_inst_info(PC);
		//printf("PC : %d\n",PC);
        CURRENT_STATE.IF_ID_INST = inst->value;
        CURRENT_STATE.IF_ID_NPC = PC;





		CURRENT_STATE.PIPE_SWITCH[IF_STAGE] = 0;
		CURRENT_STATE.PIPE_SWITCH[ID_STAGE] = 1;

		if(CURRENT_STATE.EX_MEM_BR_TAKE == 1){
            //printf("HEREEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE\n");



			//inst must be the one that we change to nop
			instruction* inst = get_inst_info(PC-4);
			CURRENT_STATE.IF_ID_INST = inst->value;
			CURRENT_STATE.IF_ID_NPC = PC-4;

			//flag becomes false

			//printf("BRANCH_COUNTBRANCH_COUNTBRANCH_COUNTBRANCH_COUNTBRANCH_COUNTBRANCH_COUNTBRANCH_COUNTBRANCH_COUNT %d\n",CURRENT_STATE.BRANCH_COUNT);


			//pdf said we need excatly correct number of cycle (see in util.c increment variable CYCLE_COUNT in fuction cycle())
			CURRENT_STATE.PC -=4;

			CURRENT_STATE.BRANCH_COUNT += 1;
			//printf("Current PC %d\n",CURRENT_STATE.PC);



			if(CURRENT_STATE.BRANCH_COUNT == 2){

				CURRENT_STATE.PIPE[0] = 0;
				CURRENT_STATE.PIPE[1] = 0;
				CURRENT_STATE.PIPE[2] = 0;
				//CURRENT_STATE.PIPE_SWITCH[1] = 0;

			    CURRENT_STATE.EX_MEM_BR_TAKE = 0;

               // printf("BRANCH PCCCCCCCCCCCCCCCC %d\n",CURRENT_STATE.BRANCH_PC);
                CURRENT_STATE.PC =  CURRENT_STATE.BRANCH_PC -4;
                CURRENT_STATE.BRANCH_COUNT = 0;
				CURRENT_STATE.BRANCH_PRINT = 1;
				CURRENT_STATE.NOP_FLAG = 0;

			}
			//CURRENT_STATE.BRANCH_COUNT += 1;
			//then it add+4 again in the end, so next cycle is the same instruction.

        }


	}else{
	    CURRENT_STATE.PIPE[0] = 0;

	}
	//even it exceeds the maximum  we still need this value(PC+4), dont change.
	CURRENT_STATE.PC = CURRENT_STATE.PC + 4;

	for(i=0;i<5;i++){
		if(CURRENT_STATE.PIPE_SWITCH[i]==1){
			chk=1;
			break;
		}
	}
	if(chk==0){
		RUN_BIT=FALSE;
		//printf("OUT\n");
		CURRENT_STATE.PC = CURRENT_STATE.PIPE[4] + 4;
		return;
	}
	if((int)(CURRENT_STATE.MEM_WB_NPC - MEM_TEXT_START)/4 > NUM_INST) {
        RUN_BIT = FALSE;
	}

//printf("AFTER3 \n");

}
