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
instruction* get_inst_info(uint32_t pc)
{
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
	/** Implement this function */
	int k,k1;
	uint32_t PC = CURRENT_STATE.PC;
	instruction* inst = get_inst_info(PC);
	if(PC>=0x400000+(NUM_INST*4)||PC<0x400000||RUN_BIT==FALSE){
		RUN_BIT=FALSE;
		return;
	}
	switch(inst->opcode)
	{
	    //Type I
	    case 0x9:		//(0x001001)ADDIU
	        CURRENT_STATE.REGS[RT(inst)] = (unsigned int)CURRENT_STATE.REGS[RS(inst)] + (unsigned int)SIGN_EX(IMM(inst));
	        CURRENT_STATE.PC += 4;
	        //printf("ADDIU\n");
	        break;
	    case 0xc:		//(0x001100)ANDI
	        CURRENT_STATE.REGS[RT(inst)] = CURRENT_STATE.REGS[RS(inst)] & SIGN_EX(IMM(inst));
	        CURRENT_STATE.PC += 4;
	         //printf("ADDI\n");
	        break;
	    case 0xf:		//(0x001111)LUI
	        CURRENT_STATE.REGS[RT(inst)] = SIGN_EX(IMM(inst))<<16;
	        CURRENT_STATE.PC += 4;
	        //printf("LUI\n");
	        break;

	    case 0xd:		//(0x001101)ORI
	        CURRENT_STATE.REGS[RT(inst)] = (CURRENT_STATE.REGS[RS(inst)])|(SIGN_EX(IMM(inst)));
	        CURRENT_STATE.PC += 4;
	        //printf("ORI\n");
	        break;

	    case 0xb:		//(0x001011)SLTIU
	        //printf("SLTIU\n");
	        if((unsigned int)CURRENT_STATE.REGS[RS(inst)] < (unsigned int)(IMM(inst))){
                CURRENT_STATE.REGS[RT(inst)] = 1;
            }else{
                CURRENT_STATE.REGS[RT(inst)] = 0;

            }
            CURRENT_STATE.PC += 4;
	        break;
	    case 0x23:		//(0x100011)LW
	        //printf("LW\n");
	        CURRENT_STATE.REGS[RT(inst)] = mem_read_32(CURRENT_STATE.REGS[RS(inst)] +SIGN_EX(IMM(inst)));
	        CURRENT_STATE.PC += 4;
	        break;


	    case 0x2b:		//(0x101011)SW
	        //printf("SW\n");
	        mem_write_32(CURRENT_STATE.REGS[RS(inst)] +SIGN_EX(IMM(inst)),CURRENT_STATE.REGS[RT(inst)]);
	        CURRENT_STATE.PC += 4;
	        break;
	    case 0x4:		//(0x000100)BEQ
	        //printf("BEQ\n");
	        if (CURRENT_STATE.REGS[RS(inst)] == CURRENT_STATE.REGS[RT(inst)]){
                CURRENT_STATE.PC = CURRENT_STATE.PC+ 4  +(IMM(inst)<<2);
                }
                else{ CURRENT_STATE.PC += 4;

            }
            break;



	    case 0x5:		//(0x000101)BNE
	        //printf("BNE\n");
	         if (CURRENT_STATE.REGS[RS(inst)] != CURRENT_STATE.REGS[RT(inst)]){
                CURRENT_STATE.PC = CURRENT_STATE.PC+ 4 +(IMM(inst)<<2);
                }
                else{ CURRENT_STATE.PC += 4;

            }
            break;

    	    //TYPE R
	    case 0x0:		//(0x000000)ADDU, AND, NOR, OR, SLTU, SLL, SRL, SUBU  if JR
	        switch(FUNC(inst))
	        {
                case 0x21://ADDU
                    CURRENT_STATE.REGS[RD(inst)] = (unsigned int)CURRENT_STATE.REGS[RS(inst)] + (unsigned int)CURRENT_STATE.REGS[RT(inst)];
                    CURRENT_STATE.PC += 4;
                    //printf("ADDU\n");
                    break;
                case 0x24://AND
                    CURRENT_STATE.REGS[RD(inst)] = CURRENT_STATE.REGS[RS(inst)] & CURRENT_STATE.REGS[RT(inst)];
                    CURRENT_STATE.PC += 4;
                    //printf("AND\n");
                    break;
                case 0x27://NOR
                    CURRENT_STATE.REGS[RD(inst)] = ~(CURRENT_STATE.REGS[RS(inst)] | CURRENT_STATE.REGS[RT(inst)]);
                    CURRENT_STATE.PC += 4;
                    //printf("NOR\n");
                    break;
                case 0x25://OR
                    CURRENT_STATE.REGS[RD(inst)] = (CURRENT_STATE.REGS[RS(inst)]) | (CURRENT_STATE.REGS[RT(inst)]);
                    CURRENT_STATE.PC += 4;
                    //printf("OR\n");
                    break;
                case 0x2b://SLTU
                    //printf("SLTU\n");
                    if((unsigned int)CURRENT_STATE.REGS[RS(inst)] < (unsigned int)CURRENT_STATE.REGS[RT(inst)]){
                        CURRENT_STATE.REGS[RD(inst)] = 1;
                        CURRENT_STATE.PC += 4;



                    }else{
                        CURRENT_STATE.REGS[RD(inst)] = 0;
                        CURRENT_STATE.PC += 4;




                    }
                    break;
                case 0x0://SLL

                    CURRENT_STATE.REGS[RD(inst)] =  CURRENT_STATE.REGS[RT(inst)]<<SHAMT(inst);
                    CURRENT_STATE.PC += 4;
                    //printf("Sll\n");
                    break;

                case 0x2://SRL

                	if(CURRENT_STATE.REGS[RT(inst)]<0){
						k = 0x80000000;
						k1 = k>>SHAMT(inst);
						k = ~k;
						CURRENT_STATE.REGS[RD(inst)] = (CURRENT_STATE.REGS[RT(inst)]&k)>>SHAMT(inst);
						CURRENT_STATE.REGS[RD(inst)] = CURRENT_STATE.REGS[RD(inst)]&k1;
						break;
                	}
                	else{
                    CURRENT_STATE.REGS[RD(inst)] =  CURRENT_STATE.REGS[RT(inst)]>>SHAMT(inst);

                    CURRENT_STATE.PC += 4;
                    //printf("Srl\n");
                    break;
                	}
                    break;
                case 0x23://SUBU
                    CURRENT_STATE.REGS[RD(inst)] = (unsigned int)CURRENT_STATE.REGS[RS(inst)] - (unsigned int)CURRENT_STATE.REGS[RT(inst)];
                    CURRENT_STATE.REGS[RD(inst)] = (unsigned int)CURRENT_STATE.REGS[RD(inst)];
                    CURRENT_STATE.PC += 4;
                    //printf("SUBU\n");
                    break;

                case 0x08://JR
                    CURRENT_STATE.PC = CURRENT_STATE.REGS[RS(inst)];
                    //printf("JR\n");
                    break;

	        }
	        break;


    	    //TYPE J
	    case 0x2:		//(0x000010)J
	        //printf("J\n");
            CURRENT_STATE.PC = ( CURRENT_STATE.PC & 0xf0000000)|(TARGET(inst)*4);

            break;

	    case 0x3:		//(0x000011)JAL
	        //printf("JAL\n");
	        CURRENT_STATE.REGS[31] = CURRENT_STATE.PC + 8;
	        CURRENT_STATE.PC = ( CURRENT_STATE.PC & 0xf0000000)|(TARGET(inst)<<2);
            break;


	    default:
			assert(0);
	}


}
