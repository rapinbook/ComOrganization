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
//INSTRUCTION FETCH STAGE
void IF_Stage(){

    if(CURRENT_STATE.STAGE[0] != 1){
        //printf("WTH\n");
        CURRENT_STATE.PIPE[0] = 0;
        //CURRENT_STATE.STAGE[0] = 0;
        //CURRENT_STATE.STAGE[1]  = 1;
        return;

    }
    //printf("CURRENT STAGE PC FETCH : %x\n",CURRENT_STATE.PC);

    //printf("first stage\n");
    CURRENT_STATE.STAGE[1]  = 1;
    CURRENT_STATE.STAGE[0] = 0;
    instruction * inst = get_inst_info(CURRENT_STATE.PC);
    uint32_t PC = CURRENT_STATE.PC;
    CURRENT_STATE.IF_ID_INST = inst->value;
	CURRENT_STATE.IF_ID_NPC = PC;
	CURRENT_STATE.PIPE[0] = PC;

	if(CURRENT_STATE.PIPE_FLUSH[IF_STAGE] == 1){
            //printf("HERE FOR IF STAGE\n");
            CURRENT_STATE.PC = CURRENT_STATE.BRANCH_PC - 4;
            //printf("PCCCCCCCCCCCCCCCCCCCCC %x\n",CURRENT_STATE.PC);
            CURRENT_STATE.PIPE[0] = 0;
            CURRENT_STATE.PIPE_FLUSH[IF_STAGE] = 0;
            CURRENT_STATE.BRANCH_RESET_IF = 1;
            //CURRENT_STATE.PIPE_FLUSH[IF_STAGE] = 0;

    }
    if(CURRENT_STATE.BRANCH_CON_SIG == 1){
        CURRENT_STATE.PC -= 4;
        CURRENT_STATE.PIPE_FLUSH[IF_STAGE] = 1;
        CURRENT_STATE.BRANCH_CON_SIG = 0;
    }
	//Have to jump here cause of stop function
	if(CURRENT_STATE.JUMP_ACTIVE == 1){

            //CURRENT_STATE.PC -= 4;
            CURRENT_STATE.PC = CURRENT_STATE.JUMP_PC - 4;
            CURRENT_STATE.JUMP_ACTIVE = 0;
	}

    if(CURRENT_STATE.PIPE_STALL[0] != 0){
            //printf("STALL VERSION OF IF STAGE\n");
            CURRENT_STATE.PC -= 4;
            CURRENT_STATE.PIPE_STALL[0] = 0;




	}

}
void ID_Stage(){

	/*if(CURRENT_STATE.PIPE_FLUSH[ID_STAGE]==TRUE){

	}*/
    if(CURRENT_STATE.STAGE[1] != 1){
        CURRENT_STATE.PIPE[1] = 0;
        return;
    }


    int PC = CURRENT_STATE.PIPE[IF_STAGE] ;
     //printf("second stage\n");
    CURRENT_STATE.STAGE[1]  = 0;
    CURRENT_STATE.STAGE[2]  = 1;
	instruction *inst = get_inst_info(CURRENT_STATE.IF_ID_NPC);
	CURRENT_STATE.ID_EX_NPC  = CURRENT_STATE.IF_ID_NPC;
	int FLAG_PIPE_CHANGE = 0;
	if(CURRENT_STATE.PIPE_STALL[1] != 0){
            //printf("STALL VERSION OF ID STAGE\n");
            CURRENT_STATE.ID_EX_NPC = CURRENT_STATE.PIPE_STALL[1];
            inst = get_inst_info(CURRENT_STATE.PIPE_STALL[1]);
            FLAG_PIPE_CHANGE = CURRENT_STATE.PIPE_STALL[1];
            CURRENT_STATE.PIPE_STALL[1] = 0;




	}

	//Flushing for Jumop

    if(CURRENT_STATE.PIPE_FLUSH[ID_STAGE] == 1 || CURRENT_STATE.BRANCH_RESET_IF == 1){
        //printf("HEREEEEEEEEEEEEEEEEEEEEE\n");

        CURRENT_STATE.ID_EX_REG2 = 0;
        CURRENT_STATE.ID_EX_REG1 = 0;
        CURRENT_STATE.ID_EX_DEST = 0;
        CURRENT_STATE.ID_EX_WB = 0;
        CURRENT_STATE.ID_EX_FLUSH_OPCLEAN = 1;



        CURRENT_STATE.PIPE[0] = 0;


        /*if(CURRENT_STATE.JUMP_ACTIVE == 1){
            CURRENT_STATE.PIPE_FLUSH[ID_STAGE] = 0;

            CURRENT_STATE.PC = CURRENT_STATE.JUMP_PC;
            CURRENT_STATE.JUMP_ACTIVE = 0;
        }*/
        CURRENT_STATE.BRANCH_RESET_IF = 0;
        if(CURRENT_STATE.PIPE_FLUSH[ID_STAGE] == 1){

        //printf("INNNNNNNNNNNNNNNNNNN\n");

        CURRENT_STATE.PIPE_FLUSH[ID_STAGE] = 0;
        }
        //return;
    }else{

	switch(inst->opcode)
	    {
	    	//R type
	        case 0x0:
				//keep the number of reg, not the value in reg
				if(FUNC(inst)==0x08){

					//printf("LAST: %x\n",CURRENT_STATE.REGS[RS(inst)]);
					//CURRENT_STATE.ID_EX_REG1 = CURRENT_STATE.REGS[RS(inst)];
					CURRENT_STATE.JUMP_PC = CURRENT_STATE.REGS[RS(inst)];
                    CURRENT_STATE.PIPE_FLUSH[ID_STAGE] = 1;
                    //printf("JUMP_PC JR: %x\n", CURRENT_STATE.JUMP_PC);


                    CURRENT_STATE.ID_EX_WB = 0;
                    CURRENT_STATE.JUMP_ACTIVE = 1;

                    break;
				}
				else{

                CURRENT_STATE.ID_EX_REG2 = CURRENT_STATE.REGS[RT(inst)];
	            CURRENT_STATE.ID_EX_REG1 = CURRENT_STATE.REGS[RS(inst)];
	            CURRENT_STATE.ID_EX_DEST = RD(inst);
				CURRENT_STATE.ID_EX_WB = 1;
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
				CURRENT_STATE.ID_EX_WB = 1;
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

            CURRENT_STATE.JUMP_PC = ( PC & 0xf0000000)|(TARGET(inst)*4);
            //printf("JUMP_PC J: %x\n", CURRENT_STATE.JUMP_PC);
            CURRENT_STATE.PIPE_FLUSH[ID_STAGE] = 1;
            //CURRENT_STATE.FLAG_JUMP = 1;
            CURRENT_STATE.ID_EX_DEST = 0;
            CURRENT_STATE.JUMP_ACTIVE = 1;
            //
            CURRENT_STATE.ID_EX_WB = 0;



            break;

	    case 0x3:		//(0x000011)JAL
	        //printf("JAL\n");
	        CURRENT_STATE.ID_EX_REG1 = PC + 8;
	        CURRENT_STATE.JUMP_PC = ( PC & 0xf0000000)|(TARGET(inst) <<2);
	        //printf("JUMP_PC JAL: %x\n", CURRENT_STATE.JUMP_PC);
	        //CURRENT_STATE.FLAG_JUMP = 1;
	        CURRENT_STATE.ID_EX_DEST = 31;
			CURRENT_STATE.PIPE_FLUSH[ID_STAGE] = 1;
			CURRENT_STATE.JUMP_ACTIVE = 1;
			CURRENT_STATE.ID_EX_WB = 1;
			//CURRENT_STATE.ID_EX_JAL = 1;
			//printf("WOW\n");

            CURRENT_STATE.JAL_ACTIVE += 1;
            //printf("JAL ACTIVE COUNT : %x\n",CURRENT_STATE.JAL_ACTIVE);


            break;

	    } }
		//stall
		if(CURRENT_STATE.ID_EX_MEMREAD == 1){
            //printf("What is up bro!\n");
			if(CURRENT_STATE.EX_MEM_DEST==RS(inst)||CURRENT_STATE.EX_MEM_DEST==RT(inst)){
                //printf("What is up bro!\n");
                CURRENT_STATE.PIPE_STALL[1] = CURRENT_STATE.IF_ID_NPC;
                CURRENT_STATE.PIPE_STALL[0] = CURRENT_STATE.PC;
                //printf("stall_IF:%x stall_ID:%x \n",CURRENT_STATE.PIPE_STALL[0],CURRENT_STATE.PIPE_STALL[1]);
                CURRENT_STATE.ID_EX_FLUSH_OPCLEAN = 1;
                CURRENT_STATE.STALL_CONTROL_SIG = 1;

				CURRENT_STATE.ID_EX_REG1 = 0;
				CURRENT_STATE.ID_EX_REG2 = 0;
				CURRENT_STATE.ID_EX_WB = 0;
			}

		}
		/*if(inst->opcode==0x2b){

				if(CURRENT_STATE.EX_MEM_DEST==RS(inst)||CURRENT_STATE.EX_MEM_DEST==RT(inst)){

					CURRENT_STATE.ID_EX_REG1 = 0;
					CURRENT_STATE.ID_EX_REG2 = 0;
					CURRENT_STATE.ID_EX_WB = 0;
				}

		}
    }*/
    if(CURRENT_STATE.BRANCH_CON_SIG == 1){
        CURRENT_STATE.PIPE_FLUSH[ID_STAGE] = 1;

    }

    //printf("END ID PCCCCCCCCCCCCCCCCCCCCC %x\n",CURRENT_STATE.PC);
    //printf("END ID\n");
	CURRENT_STATE.PIPE[ID_STAGE] = CURRENT_STATE.PIPE[IF_STAGE];
	if(FLAG_PIPE_CHANGE != 0){
        CURRENT_STATE.PIPE[ID_STAGE] = FLAG_PIPE_CHANGE;
        FLAG_PIPE_CHANGE = 0;
	}
	if(CURRENT_STATE.JUMP_ACTIVE == 1){
        CURRENT_STATE.ID_EX_J = 1;
	}else{
        CURRENT_STATE.ID_EX_J = 0;
	}
	if(CURRENT_STATE.JAL_ACTIVE == 1){

        CURRENT_STATE.ID_EX_JAL = 1;
        //CURRENT_STATE.JAL_ACTIVE = 0;

	}else{

        CURRENT_STATE.ID_EX_JAL = 0;
	}
}
void EX_Stage(){

    if(CURRENT_STATE.STAGE[2] != 1){
        CURRENT_STATE.PIPE[2] = 0;
        return;
    }
    //printf("third stage\n");
    CURRENT_STATE.STAGE[2]  = 0;
    CURRENT_STATE.STAGE[3]  = 1;

	int k,chk=0,k1;
	short opcode=0,func=0;
	CURRENT_STATE.PIPE[EX_STAGE] = CURRENT_STATE.PIPE[ID_STAGE];
	instruction* inst = get_inst_info(CURRENT_STATE.ID_EX_NPC);
	opcode = inst->opcode;
	//if(CURRENT_STATE.ID_EX_WB==1){
            //printf("WB_ACTIVATE Forward condi? :%x\n",CURRENT_STATE.ID_EX_WB);
			if(CURRENT_STATE.MEM_WB_DEST_FINAL!=0&&CURRENT_STATE.MEM_WB_DEST_FINAL==RS(inst)&&CURRENT_STATE.EX_MEM_DEST!=RS(inst)){
                //printf("11111111111111111111111111111111111111111111\n");
                CURRENT_STATE.ID_EX_REG1 =CURRENT_STATE.EX_MEM_FORWARD_VALUE ;
				//CURRENT_STATE.MEM_WB_FORWARD_REG = CURRENT_STATE.MEM_WB_DEST;
				//CURRENT_STATE.MEM_WB_FORWARD_VALUE = CURRENT_STATE.MEM_WB_ALU_OUT; // value of the register we want to forward
			}
			if(CURRENT_STATE.MEM_WB_DEST_FINAL!=0&&CURRENT_STATE.MEM_WB_DEST_FINAL==RT(inst)&&CURRENT_STATE.EX_MEM_DEST!=RT(inst)){
                //printf("222222222222222222222222222222222222 %x\n",CURRENT_STATE.MEM_WB_DEST_FINAL);
			    //printf("22222222222222222222222222222222222222222222\n");
			    CURRENT_STATE.ID_EX_REG2 =CURRENT_STATE.EX_MEM_FORWARD_VALUE ;
                //CURRENT_STATE.MEM_WB_FORWARD_REG = CURRENT_STATE.MEM_WB_DEST;
				//CURRENT_STATE.MEM_WB_FORWARD_VALUE = CURRENT_STATE.MEM_WB_ALU_OUT; // value of the register we want to forward
			}

			if(CURRENT_STATE.EX_MEM_DEST!=0&&CURRENT_STATE.EX_MEM_DEST==RS(inst)){
				//printf("33333333333333333333333333333333333333333333\n");
                CURRENT_STATE.ID_EX_REG1 = CURRENT_STATE.EX_MEM_ALU_OUT;
				//CURRENT_STATE.EX_MEM_FORWARD_REG = CURRENT_STATE.EX_MEM_DEST;
				//CURRENT_STATE.EX_MEM_FORWARD_VALUE = CURRENT_STATE.EX_MEM_ALU_OUT; // value of the register we want to forward
			}
			if(CURRENT_STATE.EX_MEM_DEST!=0&&CURRENT_STATE.EX_MEM_DEST==RT(inst)){
				//printf("444444444444444444444444444444444444444444444\n");
				CURRENT_STATE.ID_EX_REG2 = CURRENT_STATE.EX_MEM_ALU_OUT;
				if(opcode == 0x5 || opcode == 0x6){
                    //CURRENT_STATE.ID_EX_REG1 = CURRENT_STATE.EX_MEM_ALU_OUT;
                    CURRENT_STATE.REGS[CURRENT_STATE.ID_EX_DEST] = CURRENT_STATE.EX_MEM_ALU_OUT;
				}
				//printf("CURRENT_STATE.EX_MEM_ALU_OUT : %d %x\n",CURRENT_STATE.EX_MEM_ALU_OUT,RT(inst));
				//CURRENT_STATE.EX_MEM_FORWARD_REG = CURRENT_STATE.EX_MEM_DEST;
				//CURRENT_STATE.EX_MEM_FORWARD_VALUE = CURRENT_STATE.EX_MEM_ALU_OUT; // value of the register we want to forward
			}


	//}

	func = inst->func_code;

	//Flush for jump

	if(CURRENT_STATE.ID_EX_FLUSH_OPCLEAN == 1){
        opcode = 0;
        func = 0x21;
        CURRENT_STATE.ID_EX_REG1 = 0;
        CURRENT_STATE.ID_EX_REG2 = 0;
         CURRENT_STATE.EX_MEM_DEST = 0;
        //printf("CLEAN SHIT\n");
        CURRENT_STATE.ID_EX_FLUSH_OPCLEAN = 0;
        if(CURRENT_STATE.STALL_CONTROL_SIG == 1){
            CURRENT_STATE.PIPE[EX_STAGE] = 0;
            CURRENT_STATE.STALL_CONTROL_SIG = 0;
        }


    }
    if(CURRENT_STATE.PIPE_FLUSH[EX_STAGE] == 1){
            //printf("HELLOOOOOOOOOO\n");
            opcode = 0;
            func = 0x21;
            CURRENT_STATE.ID_EX_REG1 = 0;
            CURRENT_STATE.ID_EX_REG2 = 0;
            CURRENT_STATE.PIPE[2] = 0;
            CURRENT_STATE.PIPE_FLUSH[EX_STAGE] = 0;
            CURRENT_STATE.ID_EX_DEST = 0;


    }
	switch(opcode)
	{

	    //Type I
	    case 0x9:		//(0x001001)ADDIU
	        CURRENT_STATE.EX_MEM_ALU_OUT = ((unsigned int)CURRENT_STATE.ID_EX_REG1 + (unsigned int)CURRENT_STATE.ID_EX_IMM);
	        //printf("ADDIUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU REG1:%x Imm:%x DEST:%x PC:%x\n",(unsigned int)CURRENT_STATE.ID_EX_REG1,CURRENT_STATE.ID_EX_IMM,CURRENT_STATE.ID_EX_DEST,CURRENT_STATE.ID_EX_NPC);

	        break;
	    case 0xc:		//(0x001100)ANDI
	        CURRENT_STATE.EX_MEM_ALU_OUT = (CURRENT_STATE.ID_EX_REG1 & CURRENT_STATE.ID_EX_IMM);

	         //printf("ADDI\n");
	        break;
	    case 0xf:		//(0x001111)LUI

	        CURRENT_STATE.EX_MEM_ALU_OUT = SIGN_EX(CURRENT_STATE.ID_EX_IMM)<<16;
	        CURRENT_STATE.LA_CONTROL_SIG += 1;
	        //printf("Is it the right thing here\n");



	        break;

	    case 0xd:		//(0x001101)ORI
	        CURRENT_STATE.EX_MEM_ALU_OUT = (CURRENT_STATE.ID_EX_REG1)|(CURRENT_STATE.ID_EX_IMM);
	        //printf("somehow work\n");
	        if(CURRENT_STATE.LA_CONTROL_SIG == 2){
                CURRENT_STATE.LA_CONTROL_SIG = 3;
	        }




	        break;

	    case 0xb:		//(0x001011)SLTIU
	        //printf("SLTIU\n");
	        if((unsigned int)CURRENT_STATE.ID_EX_REG1 < (unsigned int)(CURRENT_STATE.ID_EX_IMM)){
                //printf("SLTIU : %x\n",CURRENT_STATE.ID_EX_REG1);
                CURRENT_STATE.EX_MEM_ALU_OUT = 1;
            }else{
                //printf("SLTIU : %x\n",CURRENT_STATE.ID_EX_REG1);
                CURRENT_STATE.EX_MEM_ALU_OUT = 0;

            }

	        break;
	    case 0x23:		//(0x100011)LW
	        //keep address

	        CURRENT_STATE.EX_MEM_W_VALUE = CURRENT_STATE.ID_EX_REG1 + SIGN_EX(CURRENT_STATE.ID_EX_IMM);
	        CURRENT_STATE.ID_EX_MEMREAD_FLAG= 1;
	        //printf("DEST %x\n LW\n value:%x PC:%x\n",CURRENT_STATE.ID_EX_DEST,CURRENT_STATE.EX_MEM_W_VALUE,CURRENT_STATE.PIPE[2]);
	        //CURRENT_STATE.PC += 4;
	        break;
	    case 0x2b:		//(0x101011)SW
	        //keep address
	        CURRENT_STATE.EX_MEM_W_VALUE = CURRENT_STATE.ID_EX_REG1 + SIGN_EX(CURRENT_STATE.ID_EX_IMM);
	        //printf("DEST %x\n SW\n value:%x PC:%x\n",CURRENT_STATE.ID_EX_DEST,CURRENT_STATE.EX_MEM_W_VALUE,CURRENT_STATE.PIPE[2]);
	        //mem_write_32(CURRENT_STATE.REGS[RS(inst)] +SIGN_EX(IMM(inst)),CURRENT_STATE.REGS[RT(inst)]);
	        //CURRENT_STATE.PC += 4;
	        break;
	    case 0x4:		//(0x000100)BEQ
	        //printf("BEQ\n");
	        if (CURRENT_STATE.ID_EX_REG1 == CURRENT_STATE.REGS[CURRENT_STATE.ID_EX_DEST]){
                CURRENT_STATE.EX_MEM_BR_TAKE = 1;
                CURRENT_STATE.EX_MEM_BR_TARGET = CURRENT_STATE.ID_EX_NPC + 4 + (CURRENT_STATE.ID_EX_IMM<<2);
                CURRENT_STATE.BRANCH_PC = CURRENT_STATE.EX_MEM_BR_TARGET;

                CURRENT_STATE.BRANCH_CON_SIG = 1;
                CURRENT_STATE.PIPE_FLUSH[EX_STAGE] = 1;
                }
            else{
                CURRENT_STATE.EX_MEM_BR_TAKE = 2;//for stall
                        //CURRENT_STATE.PC += 4
            }
            break;
	    case 0x5:		//(0x000101)BNE
	        //printf("BNEEEEEEEEEEEEEEEEEE\n");
	         if (CURRENT_STATE.ID_EX_REG1 != CURRENT_STATE.REGS[CURRENT_STATE.ID_EX_DEST]){

                CURRENT_STATE.EX_MEM_BR_TAKE = 1;
                //printf("%x %x \n",CURRENT_STATE.ID_EX_REG1,CURRENT_STATE.REGS[CURRENT_STATE.ID_EX_DEST]);
                CURRENT_STATE.EX_MEM_BR_TARGET = CURRENT_STATE.ID_EX_NPC + 4 + (CURRENT_STATE.ID_EX_IMM<<2);
                CURRENT_STATE.BRANCH_PC = CURRENT_STATE.EX_MEM_BR_TARGET;
                //CURRENT_STATE.EX_MEM_DEST = 0;
                CURRENT_STATE.BRANCH_CON_SIG = 1;
                CURRENT_STATE.PIPE_FLUSH[EX_STAGE] = 1;
                }
            else{
                //printf("BR NOT taken\n");
                //printf("%x %x \n",CURRENT_STATE.ID_EX_REG1,CURRENT_STATE.REGS[CURRENT_STATE.ID_EX_DEST]);
                CURRENT_STATE.EX_MEM_BR_TAKE = 2;//CURRENT_STATE.PC += 4;
            }
            //printf("BNEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE : %x %x %x\n",CURRENT_STATE.EX_MEM_BR_TAKE,CURRENT_STATE.ID_EX_REG1,CURRENT_STATE.REGS[CURRENT_STATE.ID_EX_DEST]);
            break;
    	    //TYPE R
	    case 0x0:		//(0x000000)ADDU, AND, NOR, OR, SLTU, SLL, SRL, SUBU  if JR
	        switch(func)
	        {
                case 0x21://ADDU
                    CURRENT_STATE.EX_MEM_ALU_OUT = (unsigned int)CURRENT_STATE.ID_EX_REG1 + (unsigned int)CURRENT_STATE.ID_EX_REG2;
					//printf("ADDUOHHHHHHHHHHHHHHHHHH : %x\n",CURRENT_STATE.ID_EX_REG1);
					//printf("ADDU value : %x \n",CURRENT_STATE.ID_EX_REG1);
                    //printf("ADDU dest : %x \n",CURRENT_STATE.ID_EX_DEST);
                    //printf("ADDU_ALU value : %x PC:%x \n",CURRENT_STATE.EX_MEM_ALU_OUT,CURRENT_STATE.ID_EX_NPC);
                    //CURRENT_STATE.PC += 4;
                    break;
                case 0x24://AND
                    CURRENT_STATE.EX_MEM_ALU_OUT = CURRENT_STATE.ID_EX_REG1 & CURRENT_STATE.ID_EX_REG2;
                    //CURRENT_STATE.PC += 4;
                    //printf("AND\n");
                    break;
                case 0x27://NOR
                    CURRENT_STATE.EX_MEM_ALU_OUT = ~(CURRENT_STATE.ID_EX_REG1| CURRENT_STATE.ID_EX_REG2);
                    //printf("NOR value : %x \n",CURRENT_STATE.ID_EX_REG1);
                    //printf("NOR value : %x \n",CURRENT_STATE.ID_EX_REG2);
                    //printf("NOR value : %x \n",CURRENT_STATE.EX_MEM_ALU_OUT);
                    //CURRENT_STATE.PC += 4;
                    //printf("NOR\n");
                    break;
                case 0x25://OR
                    CURRENT_STATE.EX_MEM_ALU_OUT = (CURRENT_STATE.ID_EX_REG1) | (CURRENT_STATE.ID_EX_REG2);
                    //printf("OR value : %x \n",CURRENT_STATE.ID_EX_REG1);
                    //printf("OR value : %x \n",CURRENT_STATE.ID_EX_REG2);
                    //printf("OR value : %x \n",CURRENT_STATE.EX_MEM_ALU_OUT);
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
                        //CURRENT_STATE.PC += 4
                    }
                    break;
                case 0x0://SLL
                    //printf("SLLLLLLLLLLLLLLLLLLLLLLL\n");
                    CURRENT_STATE.EX_MEM_ALU_OUT =  CURRENT_STATE.ID_EX_REG2<<SHAMT(inst);
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
                    break;
                	}
                    break;
                case 0x23://SUBU
                    CURRENT_STATE.EX_MEM_ALU_OUT = (unsigned int)CURRENT_STATE.ID_EX_REG1 - (unsigned int)CURRENT_STATE.ID_EX_REG2;
                    CURRENT_STATE.EX_MEM_ALU_OUT = (unsigned int)CURRENT_STATE.EX_MEM_ALU_OUT;
                    //printf("subuuuuuuuuuuuuu\n");

                    break;

                case 0x08://JR

                    break;

	        }
	        break;


    	    //TYPE J
	    case 0x2:		//(0x000010)J
	    case 0x3:		//(0x000011)JAL
	        CURRENT_STATE.EX_MEM_ALU_OUT = CURRENT_STATE.ID_EX_REG1;

            break;


	    default:
			break;
	}
	if(CURRENT_STATE.LA_CONTROL_SIG == 3){
        CURRENT_STATE.EX_MEM_LA = 1;
        CURRENT_STATE.LA_CONTROL_SIG = 0;
	}else{
	    CURRENT_STATE.EX_MEM_LA = 0;

	}
	if(CURRENT_STATE.ID_EX_MEMREAD_FLAG ==  1){
            //printf("FLAGGGGGGGGGGGGG NOTICED\n");
            CURRENT_STATE.ID_EX_MEMREAD = 1;
            CURRENT_STATE.EX_MEM_MEMREAD  = CURRENT_STATE.ID_EX_MEMREAD;
            CURRENT_STATE.ID_EX_MEMREAD_FLAG = 0;

	}else{
            CURRENT_STATE.ID_EX_MEMREAD = 0;
            CURRENT_STATE.EX_MEM_MEMREAD  = CURRENT_STATE.ID_EX_MEMREAD;
	}


	CURRENT_STATE.EX_MEM_WB = CURRENT_STATE.ID_EX_WB;
	CURRENT_STATE.EX_MEM_DEST = CURRENT_STATE.ID_EX_DEST;
	CURRENT_STATE.EX_MEM_FORWARD_REG = 0;
	CURRENT_STATE.EX_MEM_NPC  = CURRENT_STATE.ID_EX_NPC;
	CURRENT_STATE.EX_MEM_J = CURRENT_STATE.ID_EX_J;
	CURRENT_STATE.EX_MEM_JAL = CURRENT_STATE.ID_EX_JAL;
}
// MEM STAGE
void MEM_Stage(){
	int keep=0;
    if(CURRENT_STATE.STAGE[3] != 1){
        CURRENT_STATE.PIPE[3] = 0;
        return;
    }
    //printf("fourth stage\n");
    CURRENT_STATE.STAGE[3]  = 0;
    CURRENT_STATE.STAGE[4]  = 1;
	CURRENT_STATE.PIPE[MEM_STAGE] = CURRENT_STATE.PIPE[EX_STAGE];
    instruction * inst_MEM = get_inst_info(CURRENT_STATE.EX_MEM_NPC);
    CURRENT_STATE.MEM_WB_NPC = CURRENT_STATE.MEM_WB_NPC;
	CURRENT_STATE.MEM_WB_ALU_OUT = CURRENT_STATE.EX_MEM_ALU_OUT;
	switch(inst_MEM->opcode)
	    {
		case 0x23:		//(0x100011)LW

            keep = cache_read(CURRENT_STATE.EX_MEM_W_VALUE);
            //printf("CURRENT_STATE.EX_MEM_W_VALUE : %x\n",CURRENT_STATE.EX_MEM_W_VALUE);


            //if miss, so stall 30 cycles
            if(keep==-1){
				//this time it will hit
				CURRENT_STATE.MEM_WB_MEM_OUT = (uint32_t)cache_read(CURRENT_STATE.EX_MEM_W_VALUE);
				//printf("HITTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT %x %x %x %x\n",CURRENT_STATE.EX_MEM_W_VALUE,CURRENT_STATE.EX_MEM_DEST,CURRENT_STATE.MEM_WB_MEM_OUT,mem_read_32(CURRENT_STATE.EX_MEM_W_VALUE));
				//do 30 cycles stall

				CURRENT_STATE.STALL_FOR_DCACHE = 1;
				CURRENT_STATE.STALL_COUNT = 1;

            }
            else{
				CURRENT_STATE.MEM_WB_MEM_OUT = (uint32_t)keep;
            }
             CURRENT_STATE.MEM_WB_DEST = CURRENT_STATE.EX_MEM_DEST;
            //printf("CURRENT_STATE.MEM_WB_MEM_OUT : %x WB: %x PC: %x \n",CURRENT_STATE.MEM_WB_MEM_OUT,CURRENT_STATE.ID_EX_WB,CURRENT_STATE.PIPE[MEM_STAGE] );
            CURRENT_STATE.READ_TAKEN = 1;
            CURRENT_STATE.EX_MEM_WB = 0;
	        //CURRENT_STATE.PC += 4;
	        break;
        case 0x2b:		//(0x101011)SW
            //printf("SW\n");
             //printf("CURRENT_STATE.MEM_WB_MEM_OUT : %x \n",CURRENT_STATE.MEM_WB_MEM_OUT );
	        keep = cache_write(CURRENT_STATE.EX_MEM_W_VALUE,CURRENT_STATE.REGS[CURRENT_STATE.EX_MEM_DEST]);
	        if(keep==-1){
                //printf("WRITEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE %x %x %x %x\n",CURRENT_STATE.EX_MEM_W_VALUE,CURRENT_STATE.EX_MEM_DEST,CURRENT_STATE.MEM_WB_MEM_OUT,mem_read_32(CURRENT_STATE.EX_MEM_W_VALUE));
				CURRENT_STATE.STALL_FOR_DCACHE = 1;
				CURRENT_STATE.STALL_COUNT = 1;
	        }
            //printf("CURRENT_STATE.MEM_WB_MEM_OUT : %x \n",CURRENT_STATE.MEM_WB_MEM_OUT );
	        CURRENT_STATE.EX_MEM_WB = 0;
	        //CURRENT_STATE.PC += 4;
	        break;
        case 0x4:		//(0x000100)BEQ
	    case 0x5:		//(0x000101)BNE
	        CURRENT_STATE.MEM_WB_BR_TAKE = CURRENT_STATE.EX_MEM_BR_TAKE;
            break;
        default :
            CURRENT_STATE.MEM_WB_ALU_OUT = CURRENT_STATE.EX_MEM_ALU_OUT;
            CURRENT_STATE.MEM_WB_DEST = CURRENT_STATE.EX_MEM_DEST;
            break;
	    }
	    //CURRENT_STATE.PIPE[3] = CURRENT_STATE.PIPE[2];
	    //CURRENT_STATE.EX_MEM_WB = CURRENT_STATE.ID_EX_WB;
	    //printf("WB_ACTIVATE? :%x\n",CURRENT_STATE.EX_MEM_WB);
	    CURRENT_STATE.MEM_WB_WB  = CURRENT_STATE.EX_MEM_WB;
	    CURRENT_STATE.MEM_WB_NPC = CURRENT_STATE.EX_MEM_NPC;
        CURRENT_STATE.MEM_WB_MEMREAD  = CURRENT_STATE.EX_MEM_MEMREAD;
        CURRENT_STATE.MEM_WB_J = CURRENT_STATE.EX_MEM_J;
        CURRENT_STATE.MEM_WB_JAL = CURRENT_STATE.EX_MEM_JAL;
        CURRENT_STATE.MEM_WB_LA = CURRENT_STATE.EX_MEM_LA;





}
//WRITE BACK STAGE
void WB_Stage(){

    if(CURRENT_STATE.STAGE[4] != 1){
        CURRENT_STATE.PIPE[4] = 0;
        return;
    }


    //printf("fifth stage\n");
     CURRENT_STATE.MEM_WB_DEST_FINAL = CURRENT_STATE.MEM_WB_DEST;
    CURRENT_STATE.STAGE[4]  = 0;
	CURRENT_STATE.PIPE[WB_STAGE] = CURRENT_STATE.PIPE[MEM_STAGE];
    instruction * inst_WB = get_inst_info(CURRENT_STATE.MEM_WB_NPC);
    if(CURRENT_STATE.MEM_WB_WB == 1 ){
            //printf("WB VALUE: %x\n",CURRENT_STATE.MEM_WB_ALU_OUT);
            CURRENT_STATE.EX_MEM_FORWARD_VALUE =CURRENT_STATE.MEM_WB_ALU_OUT;

            CURRENT_STATE.REGS[CURRENT_STATE.MEM_WB_DEST] = CURRENT_STATE.MEM_WB_ALU_OUT;
            //printf("CURRENT_STATE.MEM_WB_DEST : %x %x\n",CURRENT_STATE.MEM_WB_DEST,CURRENT_STATE.MEM_WB_ALU_OUT);

    }
    else if(CURRENT_STATE.READ_TAKEN == 1){
            //printf("HARDENNNNNNNNNNNNNNNN %x PC:%x \n",CURRENT_STATE.MEM_WB_MEM_OUT,CURRENT_STATE.MEM_WB_NPC);
            CURRENT_STATE.EX_MEM_FORWARD_VALUE = CURRENT_STATE.MEM_WB_MEM_OUT;
            //printf("LOADDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD\n");

            CURRENT_STATE.REGS[CURRENT_STATE.MEM_WB_DEST]  = CURRENT_STATE.MEM_WB_MEM_OUT;
            CURRENT_STATE.READ_TAKEN = 0;
            CURRENT_STATE.MEM_WB_MEMREAD  = 0;

    }
    if(CURRENT_STATE.PIPE[WB_STAGE] != 0){
        INSTRUCTION_COUNT++;
    }

}
/***************************************************************/
/*                                                             */
/* Procedure: process_instruction                              */
/*                                                             */
/* Purpose: Process one instrction                             */
/*                                                             */
/***************************************************************/
void process_instruction(){
    /*if (CYCLE_COUNT >= 118) {
        RUN_BIT = FALSE;
	}*/
	/** Your implementation here */
	if(CURRENT_STATE.PC==0x400000){
	CURRENT_STATE.IF_ID_INST = 0;
	CURRENT_STATE.IF_ID_NPC = 0;
	CURRENT_STATE.IF_ID_REG1 = 0;
	CURRENT_STATE.IF_ID_REG2 = 0;
	CURRENT_STATE.ID_EX_NPC = 0;
	CURRENT_STATE.ID_EX_IMM = 0;
	CURRENT_STATE.ID_EX_DEST=0;
	CURRENT_STATE.ID_EX_MEMREAD = 0;
	CURRENT_STATE.ID_EX_MEMREAD_FLAG = 0;
	CURRENT_STATE.ID_EX_J = 0;
	CURRENT_STATE.ID_EX_JAL = 0;
	CURRENT_STATE.REGS[0] = 0;
	//EX_MEM_latch
	CURRENT_STATE.EX_MEM_NPC=0;
	CURRENT_STATE.EX_MEM_ALU_OUT = 0;
	CURRENT_STATE.EX_MEM_W_VALUE = 0;
	CURRENT_STATE.EX_MEM_BR_TARGET = 0;
	CURRENT_STATE.EX_MEM_BR_TAKE = 0;
	CURRENT_STATE.EX_MEM_DEST=0;
	CURRENT_STATE.EX_MEM_MEMREAD = 0;
	CURRENT_STATE.JUMP_ACTIVE = 0;
	CURRENT_STATE.JAL_ACTIVE = 0;
	CURRENT_STATE.ID_EX_FLUSH_OPCLEAN = 0;
	CURRENT_STATE.EX_MEM_MEMREAD = 0;
	CURRENT_STATE.EX_MEM_J = 0;
	CURRENT_STATE.EX_MEM_JAL = 0;
	CURRENT_STATE.EX_MEM_LA = 0;
	CURRENT_STATE.LA_CONTROL_SIG = 0;

	//MEM_WB_latch
	CURRENT_STATE.MEM_WB_NPC = 0;
	CURRENT_STATE.MEM_WB_ALU_OUT = 0;
	CURRENT_STATE.MEM_WB_MEM_OUT = 0;
	CURRENT_STATE.MEM_WB_BR_TAKE = 0;
	CURRENT_STATE.MEM_WB_DEST = 0;
	CURRENT_STATE.MEM_WB_MEMREAD = 0;
	CURRENT_STATE.MEM_WB_MEMREAD = 0;
	CURRENT_STATE.MEM_WB_J = 0;
	CURRENT_STATE.MEM_WB_JAL = 0;
	CURRENT_STATE.MEM_WB_LA = 0;

	//Forwarding
	CURRENT_STATE.EX_MEM_FORWARD_REG = 0;
	CURRENT_STATE.MEM_WB_FORWARD_REG = 0;
	CURRENT_STATE.EX_MEM_FORWARD_VALUE = 0;
	CURRENT_STATE.MEM_WB_FORWARD_VALUE = 0;

	//To choose right PC

	CURRENT_STATE.IF_PC = 0;
	CURRENT_STATE.JUMP_PC = 0;
	CURRENT_STATE.BRANCH_PC = 0;
	CURRENT_STATE.BRANCH_CON_SIG = 0;
	CURRENT_STATE.BRANCH_RESET_IF = 0;
	CURRENT_STATE.STALL_CONTROL_SIG = 0;

	}

    uint32_t PC = CURRENT_STATE.PC;
    int chk=0,i=0;
	instruction* inst = get_inst_info(PC);
	if(PC>=0x400000+(NUM_INST*4)||PC<0x400000){
        //printf("WTFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF %x\n",0x400000+(NUM_INST*4));
        //printf("WTFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF %x\n",PC);
		FETCH_BIT = FALSE;

	}
	if(FETCH_BIT==TRUE){
		//printf("HEY\n");
		CURRENT_STATE.STAGE[0] = 1;
	}else{
        //printf("OUT\n");
        CURRENT_STATE.STAGE[0] = 0;
	}
	if(CURRENT_STATE.STALL_FOR_DCACHE==0){
	WB_Stage();
    MEM_Stage();
    EX_Stage();
    ID_Stage();
    IF_Stage();
    CURRENT_STATE.PC += 4;
	}
	else{

		CURRENT_STATE.PIPE[WB_STAGE] = 0;

		if(CURRENT_STATE.STALL_COUNT<30){
			CURRENT_STATE.STALL_COUNT++;
		}
		else{
			CURRENT_STATE.STALL_FOR_DCACHE = 0;
			CURRENT_STATE.STALL_COUNT = 0;
		}
	}
    //printf("%x\n",CURRENT_STATE.PC);
    for(i=0;i<5;i++){
		if(CURRENT_STATE.STAGE[i]==1){
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

    if((int)(CURRENT_STATE.PIPE[WB_STAGE] - MEM_TEXT_START)/4 > NUM_INST) {
        //printf("OUT\n");
        RUN_BIT = FALSE;
	}
}
