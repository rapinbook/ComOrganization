#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char s0[100],text[100][100][100],data[100][100][100],maindata[100][100][100][100];
struct DataItem{
	char key[50];
	int index;
};
struct DataItem* hashArrayData[100];
struct DataItem* hashArrayText[100];

char* strappend(char* a,char* b){
    size_t len = strlen(a) + strlen(b);
    char *str = (char*)malloc(len * sizeof(char) +1);
    *str = '\0';
    return strcat(strcat(str,a),b);
}
char* append(char *str, const char c)
{
	int length = strlen(str);
	str[length+1] = str[length];
	str[length] = c;
	return str;
}

void insertData(char k[],int index) {

   struct DataItem *item = (struct DataItem*) malloc(sizeof(struct DataItem));
   item->index = index;
   strcpy(item->key,k);

   //get the hash
   int hashIndex = 0;//???

   //move in array until an empty or deleted cell
   while(hashArrayData[hashIndex] != NULL) {
      //go to next cell
      ++hashIndex;


   }

   hashArrayData[hashIndex] = item;
}
void insertText(char k[],int index) {

   struct DataItem *item = (struct DataItem*) malloc(sizeof(struct DataItem));
   item->index = index;
   strcpy(item->key, k);

   //get the hash
   int hashIndex = 0;//???

   //move in array until an empty or deleted cell
   while(hashArrayText[hashIndex] != NULL) {
      //go to next cell
      ++hashIndex;

   }

   hashArrayText[hashIndex] = item;
}
char * reverseString(char * c){
	int start, end ,len;
	char temp, *ptr = NULL;

	len = strlen(c);

	ptr = malloc(sizeof(char)*(len+1));
	ptr = strcpy(ptr,c);
	for(start = 0,end = len-1;start<=end;start++,end--){
        temp = ptr[start];
        ptr[start] = ptr[end];
        ptr[end] = temp;
	}
    return ptr;
}
int hashkey(char* str,int chk){
	int i =0,j=0;
	int hashIndex = 0;
	//chk is 0 means data
   if(chk==0){
   while(hashArrayData[hashIndex] != NULL) {
      //go to next cell
      if(strcmp(hashArrayData[hashIndex]->key,str)==0){
		return hashArrayData[hashIndex]->index;
      }
      ++hashIndex;


   }
   }
   //chk is 1 means text
   else{
	while(hashArrayText[hashIndex] != NULL) {
      //go to next cell
      //printf("%s wut\n",hashArrayText[hashIndex]->key);
      if(strstr(hashArrayText[hashIndex]->key,str)!=NULL){
		return hashArrayText[hashIndex]->index;
      }
      ++hashIndex;


   }

   }
   return -1;
}
char *toBinary(int n,int sz){
    char c, *ptr = NULL;
	char *new;
	new = "";
	int x=n,i=0;
	if(n == 0){
        while(i<sz){
		//printf("Not pass make test\n");
		new = strappend(new,"0");
		i++;

	}
	return new;


	}

	while(x!=1){
		if(x%2==0){

            new = strappend(new,"0");
			i++;
		}
		else{


			new = strappend(new,"1");
			i++;
		}
		x=x/2;

	}

	new = strappend(new,"1");
	i++;
	while(i<sz){
		new = strappend(new,"0");
		i++;
	}

	new = reverseString(new);
	return new;
}
char *toBinaryNeg(int n,int sz){
    char c, *ptr = NULL;
	char *new;
	new = "";
	int x=~(n),i=0;
	if(n == 0){
        while(i<sz){
		new = strappend(new,"1");
		i++;

	}
	return new;


	}

	while(x!=1){
		if(x%2==0){

            new = strappend(new,"1");
			i++;
		}
		else{


			new = strappend(new,"0");
			i++;
		}
		x=x/2;

	}

	new = strappend(new,"0");
	i++;
	while(i<sz){
		new = strappend(new,"1");
		i++;
	}

	new = reverseString(new);
	return new;
}

char * SixTeenToBinary(char * st,int index){

	int start, temp,end ,len;

	char *new;
	new = "";

	len = strlen(st);
	for(start = 0;start<len;start++){
            if(st[start] == '0'){
                temp = 0;
                new = strappend(new,toBinary(temp,4));

            }
            if(st[start] == '1'){
                temp = 1;
                new = strappend(new,toBinary(temp,4));

            }
            if(st[start] == '2'){
                temp = 2;
                new = strappend(new,toBinary(temp,4));

            }
            if(st[start] == '3'){
                temp = 3;
                new = strappend(new,toBinary(temp,4));

            }
            if(st[start] == '4'){
                temp = 4;
                new = strappend(new,toBinary(temp,4));

            }
            if(st[start] == '5'){
                temp = 5;
                new = strappend(new,toBinary(temp,4));
            }
            if(st[start] == '6'){
                temp = 6;
                new = strappend(new,toBinary(temp,4));
            }
            if(st[start] == '7'){
                temp = 7;
                new = strappend(new,toBinary(temp,4));
            }if(st[start] == '8'){
                temp = 8;
                new = strappend(new,toBinary(temp,4));
            }
            if(st[start] == '9'){
                temp = 9;
                new = strappend(new,toBinary(temp,4));
            }
            if(st[start] == 'a'){
                temp = 10;
                new = strappend(new,toBinary(temp,4));
            }
            if(st[start] == 'b'){
                temp = 11;
                new = strappend(new,toBinary(temp,4));
            }
            if(st[start] == 'c'){
                temp = 12;
                new = strappend(new,toBinary(temp,4));
            }
            if(st[start] == 'd'){
                temp = 13;
                new = strappend(new,toBinary(temp,4));
            }
            if(st[start] == 'e'){
                temp = 14;
                new = strappend(new,toBinary(temp,4));
            }
            if(st[start] == 'f'){
                temp = 15;
                new = strappend(new,toBinary(temp,4));
            }
	}
	for(end = strlen(new)+1; end<=index;end++){
        //printf("end value : %d\n",end);
        new = strappend("0",new);
	}
    return new;

}
int main(int argc, char* argv[]){
	if(argc != 2){
        fprintf("error\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    char * instructionBinary = "";
    char * resultBack = "";
    char * resultMiddle = "";
    int CaseText = 0;
    int CaseData = 0;
    FILE *fp;
    int laDetector = 0;
    int i=0,j=0,l,r,numToken = 0;
    int labelIndex = -1, numOfElement = 0;
    char * dataValuePart = "";

	fp = freopen(argv[1],"r",stdin);

	while(fgets(s0,80,fp) != NULL){


            if(strstr(s0,".data") != NULL) {
                    CaseData = 1;
                    continue;


            }
            if(strstr(s0,".text") != NULL) {
                    CaseData = 0;
                    CaseText = 1;
                    continue;
            }
            if(CaseData == 1){

             char ** splitdata = NULL;


            char * p = strtok(s0, "\t");

            int spaces = 0,k;
            while(p){
                splitdata = realloc(splitdata, sizeof(char*) * ++spaces);
                //split = strtok(NULL," ");
                if(splitdata == NULL)
                    exit(-1);
                splitdata[spaces-1] = p;
                p = strtok(NULL, "\t");
                numToken++;
            }

            splitdata = realloc(splitdata, sizeof (char*) * (spaces+1));
            splitdata[spaces] = 0;
            char * a = splitdata[numToken-1];
            //fflush(stdout);
            if(*(a+1) == 'x'){
               fflush(stdout);
               a = a+2;
               fflush(stdout);
             a = SixTeenToBinary(a,32);
             resultBack = strappend(resultBack,a);
             fflush(stdout);
             //printf("aaaaaaaaaaaaaaa %s aaaaaaaaaaaaaaaa\n",a);
             fflush(stdout);

            }else{
                fflush(stdout);

            a = toBinary(atoi(a),32);

            resultBack = strappend(resultBack,a);

            //printf("b %s b\n",a);

            }




            //for( k = 0; k<(spaces+1);++k)
                //printf("split[%d] = %s\n", k , splitdata[k]);
            for( l = 0; l <(spaces);++l){
                strcpy(data[j][l], splitdata[l]);

            }
            if(strstr(s0,":") != NULL){
                labelIndex++;
                numOfElement = 0;


                //printf("%%%%%%%%%% %s label index %d %%%%%%%%%%%%%%%%%\n",data[j][2],labelIndex);
                fflush(stdout);
				insertData(data[j][0],j);
				int temp = 0;
				for( l = 0; l <(spaces);++l){
                strcpy(maindata[labelIndex][numOfElement][l], data[j][l+1]);

                }
                numOfElement++;
                }else{
                for( l = 0; l <(spaces);++l){
                strcpy(maindata[labelIndex][numOfElement][l], data[j][l]);

                }
                numOfElement++;

                }

            j++;
            ;
            free(splitdata);
            numToken = 0;



            }




            if(CaseText == 1){


            if(strstr(s0,":") != NULL){
                //printf("value of label : %s\n",s0);
                //printf("index of label : %d\n",i);
				insertText(s0,i);
				continue;
            }







                 char ** splittext = NULL;
            char * p = strtok(s0, "\t$,");
            int spaces = 0,k;
            while(p){
                splittext = realloc(splittext, sizeof(char*) * ++spaces);
                //split = strtok(NULL," ");
                if(splittext == NULL)
                    exit(-1);
                splittext[spaces-1] = p;
                p = strtok(NULL, "\t$, ");
            }

            splittext = realloc(splittext, sizeof (char*) * (spaces+1));
            splittext[spaces] = 0;



            //for( k = 0; k<(spaces+1);++k)
                //printf("split[%d] = %s\n", k , splittext[k]);

            for( r = 0; r <(spaces);++r){
                strcpy(text[i][r], splittext[r]);

            }
            if(strstr(s0,"la") != NULL){
                char * laKey = splittext[2];
                laKey[strlen(laKey)-1] = ':';
                int laCheck = hashkey(laKey,0);
                free(splittext);
                if(laCheck == 0){
                    i++;
                    continue;
                }else{
                    i = i+2;
                    continue;
                }
            }
            i++;
            //for( k = 0; k<(spaces+1);++k)
                //printf("split[%d] = %s\n", k , splittext[k]);

            free(splittext);


            }




	}


//printf(" %d\n",j);
//
//printf("value of hashKey : %d\n",hashkey("data1:",0));
//printf("55 %s\n",data[0][0]);
//printf("55 %s\n",maindata[1][0][1]);


//printf("55 %s\n",text[i-1][3]);
//
//printf("%d %s\n",hashArrayText[5]->index,hashArrayText[5]->key);

//char c[50]="abc";
//printf("%s",reverseString("abc"));
int m;
for (m=0;m<i;m++){
	if(strstr(text[m][0],":")==NULL){
		if(strcmp(text[m][0],"addiu")==0){
           char * answer = "";
			//printf("addiu\n");

			char ** splittext1 = NULL;
			char * p1 = strtok(text[m][1], "$,");
			int spaces = 0,k;
            while(p1){
                splittext1 = realloc(splittext1, sizeof(char*) * ++spaces);

                if(splittext1 == NULL)
                    exit(-1);
                splittext1[spaces-1] = p1;
                p1 = strtok(NULL, "$,");
            }
            splittext1 = realloc(splittext1,sizeof(char*)*(spaces+1));

            //split $ and number for text[m][2]
            char ** splittext2 = NULL;
			char * p2 = strtok(text[m][2], "$,");
			int spaces2 = 0,k2;
            while(p2){
                splittext2 = realloc(splittext2, sizeof(char*) * ++spaces2);

                if(splittext2 == NULL)
                    exit(-1);
                splittext2[spaces2-1] = p2;
                p2 = strtok(NULL, "$,");
            }
            splittext2 = realloc(splittext2,sizeof(char*)*(spaces2+1));

			//split 0x and number for text[m][3]

            char ** splittext3 = NULL;
			char * p3 = strtok(text[m][3], "x");
			int spaces3 = 0;

            while(p3){
                splittext3 = realloc(splittext3, sizeof(char*) * ++spaces3);

                if(splittext3 == NULL)
                    exit(-1);
                splittext3[spaces3-1] = p3;
                p3 = strtok(NULL, "x");
            }
            splittext3 = realloc(splittext3,sizeof(char*)*(spaces3+1));
			//printf("\nthis is splittext1 :%s\n",splittext3[1]);
			//printf("addiu");

			if(strcmp(splittext3[0],"0") != 0){
				fflush(stdout);
//              printf("value of index 2:%s\n",toBinary(atoi(text[m][3]),16));
//				fflush(stdout);
				strcpy(splittext3[0],toBinary(atoi(text[m][3]),16));
                fflush(stdout);

			}
			else{
			    fflush(stdout);
                //printf("value of index 2:%s\n",splittext3[1]);

				strcpy(splittext3[0],SixTeenToBinary(splittext3[1],16));
				fflush(stdout);

			}

			//printf("%s split2\n",toBinary(atoi(splittext2[0]),5));
//			fflush(stdout);
//			printf("%s",(splittext3[0]));
//			//fflush(stdout);
			answer = strappend(answer,"001001");
			answer = strappend(answer,toBinary(atoi(splittext2[0]),5));
			answer = strappend(answer,toBinary(atoi(splittext1[0]),5));
			answer = strappend(answer,splittext3[0]);
			resultMiddle = strappend(resultMiddle,answer);
			//printf("%s\n",answer);
			free(splittext1);
			free(splittext2);
			free(splittext3);
		}
		else if(strcmp(text[m][0],"addu")==0){
                char * answer = "";
			char ** splittext1 = NULL;
			char * p1 = strtok(text[m][1], "$,");
			int spaces = 0,k;
            while(p1){
                splittext1 = realloc(splittext1, sizeof(char*) * ++spaces);

                if(splittext1 == NULL)
                    exit(-1);
                splittext1[spaces-1] = p1;
                p1 = strtok(NULL, "$,");
            }
            splittext1 = realloc(splittext1,sizeof(char*)*(spaces+1));

            //split $ and number for text[m][2]
            char ** splittext2 = NULL;
			char * p2 = strtok(text[m][2], "$,");
			int spaces2 = 0,k2;
            while(p2){
                splittext2 = realloc(splittext2, sizeof(char*) * ++spaces2);

                if(splittext2 == NULL)
                    exit(-1);
                splittext2[spaces2-1] = p2;
                p2 = strtok(NULL, "$,");
            }
            splittext2 = realloc(splittext2,sizeof(char*)*(spaces2+1));

			//split $and number for text[m][3]

            char ** splittext3 = NULL;
			char * p3 = strtok(text[m][3], "$");
			int spaces3 = 0,k3;
            while(p3){
                splittext3 = realloc(splittext3, sizeof(char*) * ++spaces3);

                if(splittext3 == NULL)
                    exit(-1);
                splittext3[spaces3-1] = p3;
                p3 = strtok(NULL, "$");
            }
            splittext3 = realloc(splittext3,sizeof(char*)*(spaces3+1));
//            printf("%syay%syay \n",splittext2[0],splittext2[0]);
//
//			printf("value first %s\n",toBinary(atoi(splittext1[0]),5));
//			printf("value  second %s \n",toBinary(atoi(splittext2[0]),5));
//			printf("value of second value %s\n",toBinary(atoi(splittext2[0]),5));
			answer = strappend(answer,"000000");
			answer = strappend(answer,toBinary(atoi(splittext2[0]),5));
            answer = strappend(answer,toBinary(atoi(splittext3[0]),5));
            answer = strappend(answer,toBinary(atoi(splittext1[0]),5));
			answer = strappend(answer,"00000");
			answer = strappend(answer,"100001");
			resultMiddle = strappend(resultMiddle,answer);
			//printf("addu : %s\n",answer);
			//printf("%s\n",answer);
			free(splittext1);
			free(splittext2);
			free(splittext3);

		}
		else if(strcmp(text[m][0],"and")==0){
//printf("and");
			char * answer = "";
			char ** splittext1 = NULL;
			char * p1 = strtok(text[m][1], "$,");
			int spaces = 0,k;
            while(p1){
                splittext1 = realloc(splittext1, sizeof(char*) * ++spaces);

                if(splittext1 == NULL)
                    exit(-1);
                splittext1[spaces-1] = p1;
                p1 = strtok(NULL, "$,");
            }
            splittext1 = realloc(splittext1,sizeof(char*)*(spaces+1));



            char ** splittext2 = NULL;
			char * p2 = strtok(text[m][2], "$,");
			int spaces2 = 0,k2;
            while(p2){
                splittext2 = realloc(splittext2, sizeof(char*) * ++spaces2);

                if(splittext2 == NULL)
                    exit(-1);
                splittext2[spaces2-1] = p2;
                p2 = strtok(NULL, "$,");
            }
            splittext2 = realloc(splittext2,sizeof(char*)*(spaces2+1));

            char ** splittext3 = NULL;
			char * p3 = strtok(text[m][3], "$");
			int spaces3 = 0,k3;
            while(p3){
                splittext3 = realloc(splittext3, sizeof(char*) * ++spaces3);

                if(splittext3 == NULL)
                    exit(-1);
                splittext3[spaces3-1] = p3;
                p3 = strtok(NULL, "$");
            }
            splittext3 = realloc(splittext3,sizeof(char*)*(spaces3+1));
			answer = strappend(answer,"000000");
			answer = strappend(answer,toBinary(atoi(splittext2[0]),5));
            answer = strappend(answer,toBinary(atoi(splittext3[0]),5));
            answer = strappend(answer,toBinary(atoi(splittext1[0]),5));
			answer = strappend(answer,"00000");
			answer = strappend(answer,"100100");
			//printf("%s\n",answer);
			resultMiddle = strappend(resultMiddle,answer);
			//printf("%s\n",answer);
            free(splittext1);
            free(splittext2);
            free(splittext3);
		}
		else if(strcmp(text[m][0],"andi")==0){
                char * answer = "";
			char ** splittext1 = NULL;
			char * p1 = strtok(text[m][1], "$,");
			int spaces = 0,k;
            while(p1){
                splittext1 = realloc(splittext1, sizeof(char*) * ++spaces);

                if(splittext1 == NULL)
                    exit(-1);
                splittext1[spaces-1] = p1;
                p1 = strtok(NULL, "$,");
            }
            splittext1 = realloc(splittext1,sizeof(char*)*(spaces+1));

            //split $ and number for text[m][2]
            char ** splittext2 = NULL;
			char * p2 = strtok(text[m][2], "$,");
			int spaces2 = 0,k2;
            while(p2){
                splittext2 = realloc(splittext2, sizeof(char*) * ++spaces2);

                if(splittext2 == NULL)
                    exit(-1);
                splittext2[spaces2-1] = p2;
                p2 = strtok(NULL, "$,");
            }
            splittext2 = realloc(splittext2,sizeof(char*)*(spaces2+1));

			//split 0x and number for text[m][3]

            char ** splittext3 = NULL;
			char * p3 = strtok(text[m][3], "x");
			int spaces3 = 0;

            while(p3){
                splittext3 = realloc(splittext3, sizeof(char*) * ++spaces3);

                if(splittext3 == NULL)
                    exit(-1);
                splittext3[spaces3-1] = p3;
                p3 = strtok(NULL, "x");
            }
            splittext3 = realloc(splittext3,sizeof(char*)*(spaces3+1));
			//printf("\nthis is splittext1 :%s\n",splittext3[1]);
			if(strcmp(splittext3[0],"0") != 0){
				fflush(stdout);
//              printf("value of index 2:%s\n",toBinary(atoi(text[m][3]),16));
//				fflush(stdout);
				strcpy(splittext3[0],toBinary(atoi(text[m][3]),16));
                fflush(stdout);

			}
			else{
			    fflush(stdout);
                //printf("value of index 2:%s\n",splittext3[1]);

				strcpy(splittext3[0],SixTeenToBinary(splittext3[1],16));
				fflush(stdout);

			}

			answer = strappend(answer,"001100");
			answer = strappend(answer,toBinary(atoi(splittext2[0]),5));
			answer = strappend(answer,toBinary(atoi(splittext1[0]),5));
			answer = strappend(answer,splittext3[0]);
			//printf("%s\n",answer);
			//printf("andi : %s\n",answer);
			resultMiddle = strappend(resultMiddle,answer);
			free(splittext1);
			free(splittext2);
			free(splittext3);

		}
		else if(strcmp(text[m][0],"bne")==0){

                int arg1 = atoi(text[m][1]);
                int arg2 = atoi(text[m][2]);
                //printf("nnnnnnnnnnnnnnnn %d second %d nnnnnnnnnnnnnnnnnnnnnn\n",arg1,arg2);
                char * bneInstruct = "";
                char * front = "000101";
                char * middle1 = toBinary(arg1,5);
                char * middle2 = toBinary(arg2,5);

                char * offSet = "";
                char * key = malloc(strlen(text[m][2])+strlen(":")+1);;
                char * subKey;
                subKey = text[m][3];
                int keyLen = strlen(subKey) - 1;
                subKey[keyLen] = NULL;
                strcpy(key, subKey);
                int index_jump = hashkey(key,2);
                int PcPlusFour = 4194304 + m*4 + 4;
                int branchTarget = (4194304 + (4*index_jump));
                int diff = branchTarget - PcPlusFour;
                int toEncode = (diff/4);
                char * back;
                if(toEncode < 0){
                        back = toBinaryNeg(toEncode,16);

                }else{
                        back = toBinary(toEncode,16);

                }

                bneInstruct = strappend(bneInstruct,front);
                bneInstruct = strappend(bneInstruct,middle1);
                bneInstruct = strappend(bneInstruct,middle2);
                bneInstruct = strappend(bneInstruct,back);
                resultMiddle = strappend(resultMiddle,bneInstruct);
                //printf("Value of bneInstruction : %s\n",bneInstruct);


		}
		else if(strcmp(text[m][0],"beq")==0){
                int arg1 = atoi(text[m][1]);
                int arg2 = atoi(text[m][2]);
                char * beqInstruct = "";
                char * front = "000100";
                char * middle1 = toBinary(arg1,5);
                char * middle2 = toBinary(arg2,5);

                char * offSet = "";
                char * key = malloc(strlen(text[m][2])+strlen(":")+1);;
                char * subKey;
                subKey = text[m][3];
                int keyLen = strlen(subKey) - 1;
                subKey[keyLen] = NULL;
                strcpy(key, subKey);
                int index_jump = hashkey(key,2);
                int PcPlusFour = 4194304 + m*4 + 4;
                int branchTarget = (4194304 + (4*index_jump));
                int diff = branchTarget - PcPlusFour;
                int toEncode = (diff/4);
                char * back;
                if(toEncode < 0){
                        back = toBinaryNeg(toEncode,16);

                }else{
                        back = toBinary(toEncode,16);

                }

                beqInstruct = strappend(beqInstruct,front);
                beqInstruct = strappend(beqInstruct,middle1);
                beqInstruct = strappend(beqInstruct,middle2);
                beqInstruct = strappend(beqInstruct,back);
                resultMiddle = strappend(resultMiddle,beqInstruct);

                //printf("Value of beqInstruction : %s\n",beqInstruct);

		}
		else if(strcmp(text[m][0],"j")==0){
                int start, jumpIndex,backTemp ,len;
                char* front;
                char* back;
                char* result;
                result = "";
                front = toBinary(2,6);
                char * key = malloc(strlen(text[m][2])+strlen(":")+1);;
                char * subKey;
                subKey = text[m][1];
                int keyLen = strlen(subKey) - 1;
                subKey[keyLen] = NULL;
                strcpy(key, subKey);
                int index_jump = hashkey(key,2);
                backTemp = (4194304 + (4*index_jump));
                back = toBinary(backTemp/4,26);
                result = strappend(result,front);
                result = strappend(result,back);
                resultMiddle = strappend(resultMiddle,result);
                //printf("rrrrrrrrrrrrrrrrrrrrrr %s rrrrrrrrrrrrrrrr\n",result);


		}
		else if(strcmp(text[m][0],"jal")==0){
                int start, jumpIndex,backTemp ,len;
                char* front;
                char* back;
                char* result;
                result = "";
                front = toBinary(3,6);
                char * key = malloc(strlen(text[m][2])+strlen(":")+1);;
                char * subKey;
                subKey = text[m][1];
                int keyLen = strlen(subKey) - 1;
                subKey[keyLen] = NULL;
                strcpy(key, subKey);
                int index_jump = hashkey(key,2);
                backTemp = (4194304 + (4*index_jump));
                back = toBinary(backTemp/4,26);
                result = strappend(result,front);
                result = strappend(result,back);
                resultMiddle = strappend(resultMiddle,result);
                //printf("llllllllllllllll %s lllllllllllll\n",result);

		}
		else if(strcmp(text[m][0],"jr")==0){
                char * answer = "";
			char ** splittext1 = NULL;
			char * p1 = strtok(text[m][1], "$,");
			int spaces = 0,k;
            while(p1){
                splittext1 = realloc(splittext1, sizeof(char*) * ++spaces);

                if(splittext1 == NULL)
                    exit(-1);
                splittext1[spaces-1] = p1;
                p1 = strtok(NULL, "$,");
            }
            splittext1 = realloc(splittext1,sizeof(char*)*(spaces+1));

			answer = strappend(answer,"000000");
			answer = strappend(answer,toBinary(atoi(splittext1[0]),5));
			answer = strappend(answer,"000000000000000");
			answer = strappend(answer,"001000");
			//printf("%s\n",answer);
			resultMiddle = strappend(resultMiddle,answer);
			free(splittext1);

		}
		else if(strcmp(text[m][0],"lui")==0){
              char * answer = "";
			char ** splittext1 = NULL;
			char * p1 = strtok(text[m][1], "$,");
			int spaces = 0,k;
            while(p1){
                splittext1 = realloc(splittext1, sizeof(char*) * ++spaces);

                if(splittext1 == NULL)
                    exit(-1);
                splittext1[spaces-1] = p1;
                p1 = strtok(NULL, "$,");
            }
            splittext1 = realloc(splittext1,sizeof(char*)*(spaces+1));
			//printf("%s\n",splittext1[0]);
            //split $ and number for text[m][2]



			//split 0x and number for text[m][3]

            char ** splittext3 = NULL;
			char * p3 = strtok(text[m][2], "x");
			int spaces3 = 0;

            while(p3){
                splittext3 = realloc(splittext3, sizeof(char*) * ++spaces3);

                if(splittext3 == NULL)
                    exit(-1);
                splittext3[spaces3-1] = p3;
                p3 = strtok(NULL, "x");
            }
            //printf("%s\n",splittext1[0]);
            splittext3 = realloc(splittext3,sizeof(char*)*(spaces3+1));
			//printf("\nthis is splittext1 :%s\n",splittext3[1]);
			char keep[1000];
			strcpy(keep,splittext1);
			if(strcmp(splittext3[0],"0") != 0){
				fflush(stdout);
//              printf("value of index 2:%s\n",toBinary(atoi(text[m][3]),16));
//				fflush(stdout);
				//printf("%s\n",splittext1[0]);
				strcpy(splittext3[0],toBinary(atoi(text[m][2]),16));
                //fflush(stdout);
				//printf("%s\n",splittext1[0]);
			}
			else{
			    //fflush(stdout);
                //printf("value of index 2:%s\n",splittext3[1]);

				strcpy(splittext3[0],SixTeenToBinary(splittext3[1],16));
				//fflush(stdout);

			}
			//printf("%s\n",splittext1[0]);
			//printf("%s\n",keep);
			//printf("lui\n");
			answer = strappend(answer,"001111");
			answer = strappend(answer,toBinary(atoi(splittext1[0]),10));
			answer = strappend(answer,splittext3[0]);

			//printf("%s\n",answer);
			resultMiddle = strappend(resultMiddle,answer);
			free(splittext1);
			//free(splittext2);
			free(splittext3);



		}
		else if(strcmp(text[m][0],"lw")==0){
char * answer = "";
			char ** splittext1 = NULL;
			char * p1 = strtok(text[m][1], "$,");
			int spaces = 0,k;
            while(p1){
                splittext1 = realloc(splittext1, sizeof(char*) * ++spaces);

                if(splittext1 == NULL)
                    exit(-1);
                splittext1[spaces-1] = p1;
                p1 = strtok(NULL, "$,");
            }
            splittext1 = realloc(splittext1,sizeof(char*)*(spaces+1));
			//split 16($3) to 16 and 3
			char keep[2][1000];
			int a=0;
			strcpy(keep[0],"");
			while(text[m][2][a]!='('){
				append(keep[0],text[m][2][a]);
				a++;
			}
			strcpy(keep[1],"");
			a++;//text[m][2][i] is '$'
			a++;//now it is a number
			while(text[m][2][a]!=')'){
				append(keep[1],text[m][2][a]);
				a++;
			}


            //printf("\nYOLO %shey %shey\n",keep[1],keep[0]);
			answer = strappend(answer,"100011");//11 zeros op and rs unused
			answer = strappend(answer,toBinary(atoi(keep[1]),5));//it is 3 from 16($3)
			answer = strappend(answer,toBinary(atoi(splittext1[0]),5));
			//printf("%s\n",toBinaryNeg(atoi(keep[0]),16));
			if(atoi(keep[0]) >= 0){
                answer = strappend(answer,toBinary(atoi(keep[0]),16));
      }else{
                answer = strappend(answer,toBinaryNeg(atoi(keep[0]),16));
                //printf("lw two complement value : %s\n",toBinaryNeg(atoi(keep[0]),16));
      }
      resultMiddle = strappend(resultMiddle,answer);

			//answer = strappend(answer,toBinaryNeg(atoi(keep[0]),16));//address of 16+2^28 ??? cant plus 2^28 we have just 16 bits
			//printf("lw value :%s\n",answer);

			free(splittext1);
		}
		else if(strcmp(text[m][0],"la")==0){
		    //printf("value in instruction la : %s\n",text[m][2]);
		    //char * key = NULL;
		    char *key = malloc(strlen(text[m][2])+strlen(":")+1);
		    char * subKey = NULL;
		    subKey = text[m][2];
		    int len = strlen(subKey) - 1;
		    subKey[len] = NULL;
		    strcpy(key, subKey);
            strcat(key, ":");
            //printf(" value of key : %s\n",key);

		    int jumpIndex = hashkey(key,0);
		    //printf("index of la2 : %d\n",jumpIndex);
		    //printf("index of loaded data: %d\n",jumpIndex);

            if(jumpIndex == 0){
                //printf("############### do lui alone ###############\n");
                char * front = "001111";
                char * back = "0001000000000000";
                char * middle1 = "00000";
                char * middle2 = toBinary(atoi(text[m][1]),5);
                char * result = "";
                result = strappend(result,front);
                result = strappend(result,middle1);
                result = strappend(result,middle2);
                result = strappend(result,back);
                resultMiddle = strappend(resultMiddle,result);
                //printf("al : %s\n",result);
                //printf("############### bit instruction of case 1 : %s ###############\n",result);




            }else{
                //printf("############### do lui and ori ###############\n");
                char * front = "001111";
                char * back = "0001000000000000";
                char * middle1 = "00000";
                char * middle2 = toBinary(atoi(text[m][1]),5);
                char * result = "";
                result = strappend(result,front);
                result = strappend(result,middle1);
                result = strappend(result,middle2);
                result = strappend(result,back);
                resultMiddle = strappend(resultMiddle,result);
                //printf("############### bit instruction of case 2 lui : %s ###############\n",result);
                char * front2 = "001101";
                char * back2 = toBinary((jumpIndex)*4 ,16);
                char * middle_2 = toBinary(atoi(text[m][1]),5);
                char * result2 = "";
                result2 = strappend(result2,front2);
                result2 = strappend(result2,middle_2);
                result2 = strappend(result2,middle_2);
                result2 = strappend(result2,back2);
                resultMiddle = strappend(resultMiddle,result2);
                //printf("al1 : %s\n",result);
                //printf("al2 : %s\n",result2);
                //printf("############### bit instruction of case 2 ori : %s ###############\n",result2);
            }


		}
		else if(strcmp(text[m][0],"nor")==0){
                char * answer = "";
			char ** splittext1 = NULL;
			char * p1 = strtok(text[m][1], "$,");
			int spaces = 0,k;
            while(p1){
                splittext1 = realloc(splittext1, sizeof(char*) * ++spaces);

                if(splittext1 == NULL)
                    exit(-1);
                splittext1[spaces-1] = p1;
                p1 = strtok(NULL, "$,");
            }
            splittext1 = realloc(splittext1,sizeof(char*)*(spaces+1));

            char ** splittext2 = NULL;
			char * p2 = strtok(text[m][2], "$,");
			int spaces2 = 0,k2;
            while(p2){
                splittext2 = realloc(splittext2, sizeof(char*) * ++spaces2);

                if(splittext2 == NULL)
                    exit(-1);
                splittext2[spaces2-1] = p2;
                p2 = strtok(NULL, "$,");
            }
            splittext2 = realloc(splittext2,sizeof(char*)*(spaces2+1));

            char ** splittext3 = NULL;
			char * p3 = strtok(text[m][3], "$");
			int spaces3 = 0,k3;
            while(p3){
                splittext3 = realloc(splittext3, sizeof(char*) * ++spaces3);

                if(splittext3 == NULL)
                    exit(-1);
                splittext3[spaces3-1] = p3;
                p3 = strtok(NULL, "$");
            }
            splittext3 = realloc(splittext3,sizeof(char*)*(spaces3+1));
			answer = strappend(answer,"000000");
			answer = strappend(answer,toBinary(atoi(splittext2[0]),5));
            answer = strappend(answer,toBinary(atoi(splittext3[0]),5));
            answer = strappend(answer,toBinary(atoi(splittext1[0]),5));
			answer = strappend(answer,"00000");
			answer = strappend(answer,"100111");
			//printf("subu : %s\n",answer);
			resultMiddle = strappend(resultMiddle,answer);
			//printf("%s\n",answer);


            free(splittext1);
            free(splittext2);
            free(splittext3);

		}
		else if(strcmp(text[m][0],"or")==0){
                char * answer = "";
			char ** splittext1 = NULL;
			char * p1 = strtok(text[m][1], "$,");
			int spaces = 0,k;
            while(p1){
                splittext1 = realloc(splittext1, sizeof(char*) * ++spaces);

                if(splittext1 == NULL)
                    exit(-1);
                splittext1[spaces-1] = p1;
                p1 = strtok(NULL, "$,");
            }
            splittext1 = realloc(splittext1,sizeof(char*)*(spaces+1));



            char ** splittext2 = NULL;
			char * p2 = strtok(text[m][2], "$,");
			int spaces2 = 0,k2;
            while(p2){
                splittext2 = realloc(splittext2, sizeof(char*) * ++spaces2);

                if(splittext2 == NULL)
                    exit(-1);
                splittext2[spaces2-1] = p2;
                p2 = strtok(NULL, "$,");
            }
            splittext2 = realloc(splittext2,sizeof(char*)*(spaces2+1));

            char ** splittext3 = NULL;
			char * p3 = strtok(text[m][3], "$");
			int spaces3 = 0,k3;
            while(p3){
                splittext3 = realloc(splittext3, sizeof(char*) * ++spaces3);

                if(splittext3 == NULL)
                    exit(-1);
                splittext3[spaces3-1] = p3;
                p3 = strtok(NULL, "$");
            }
            splittext3 = realloc(splittext3,sizeof(char*)*(spaces3+1));

			answer = strappend(answer,"000000");
			answer = strappend(answer,toBinary(atoi(splittext2[0]),5));
            answer = strappend(answer,toBinary(atoi(splittext3[0]),5));
            answer = strappend(answer,toBinary(atoi(splittext1[0]),5));
			answer = strappend(answer,"00000");
			answer = strappend(answer,"100101");
			resultMiddle = strappend(resultMiddle,answer);
			//printf("or : %s\n",answer);
			//printf("%s\n",answer);

            free(splittext1);
            free(splittext2);
            free(splittext3);

		}
		else if(strcmp(text[m][0],"ori")==0){
                //printf("ori\n");
			char * answer = "";
			char ** splittext1 = NULL;
			char * p1 = strtok(text[m][1], "$,");
			int spaces = 0,k;
            while(p1){
                splittext1 = realloc(splittext1, sizeof(char*) * ++spaces);

                if(splittext1 == NULL)
                    exit(-1);
                splittext1[spaces-1] = p1;
                p1 = strtok(NULL, "$,");
            }
            splittext1 = realloc(splittext1,sizeof(char*)*(spaces+1));

            //split $ and number for text[m][2]
            char ** splittext2 = NULL;
			char * p2 = strtok(text[m][2], "$,");
			int spaces2 = 0,k2;
            while(p2){
                splittext2 = realloc(splittext2, sizeof(char*) * ++spaces2);

                if(splittext2 == NULL)
                    exit(-1);
                splittext2[spaces2-1] = p2;
                p2 = strtok(NULL, "$,");
            }
            splittext2 = realloc(splittext2,sizeof(char*)*(spaces2+1));

			//split 0x and number for text[m][3]

            char ** splittext3 = NULL;
			char * p3 = strtok(text[m][3], "x");
			int spaces3 = 0;

            while(p3){
                splittext3 = realloc(splittext3, sizeof(char*) * ++spaces3);

                if(splittext3 == NULL)
                    exit(-1);
                splittext3[spaces3-1] = p3;
                p3 = strtok(NULL, "x");
            }
            splittext3 = realloc(splittext3,sizeof(char*)*(spaces3+1));
			//printf("\nthis is splittext1 :%s\n",splittext3[1]);
			if(strcmp(splittext3[0],"0") != 0){
				fflush(stdout);
//              printf("value of index 2:%s\n",toBinary(atoi(text[m][3]),16));
//				fflush(stdout);
				strcpy(splittext3[0],toBinary(atoi(text[m][3]),16));
                fflush(stdout);

			}
			else{
			    fflush(stdout);
                //printf("value of index 2:%s\n",splittext3[1]);

				strcpy(splittext3[0],SixTeenToBinary(splittext3[1],16));
				fflush(stdout);

			}

			answer = strappend(answer,"001101");
			answer = strappend(answer,toBinary(atoi(splittext2[0]),5));
			answer = strappend(answer,toBinary(atoi(splittext1[0]),5));
			answer = strappend(answer,splittext3[0]);
			//printf("ori : %s\n",answer);
			resultMiddle = strappend(resultMiddle,answer);
			//printf("%s\n",answer);

			free(splittext1);
			free(splittext2);
			free(splittext3);

		}
		else if(strcmp(text[m][0],"sltiu")==0){
                char * answer = "";
			char ** splittext1 = NULL;
			char * p1 = strtok(text[m][1], "$,");
			int spaces = 0,k;
            while(p1){
                splittext1 = realloc(splittext1, sizeof(char*) * ++spaces);

                if(splittext1 == NULL)
                    exit(-1);
                splittext1[spaces-1] = p1;
                p1 = strtok(NULL, "$,");
            }
            splittext1 = realloc(splittext1,sizeof(char*)*(spaces+1));

            //split $ and number for text[m][2]
            char ** splittext2 = NULL;
			char * p2 = strtok(text[m][2], "$,");
			int spaces2 = 0,k2;
            while(p2){
                splittext2 = realloc(splittext2, sizeof(char*) * ++spaces2);

                if(splittext2 == NULL)
                    exit(-1);
                splittext2[spaces2-1] = p2;
                p2 = strtok(NULL, "$,");
            }
            splittext2 = realloc(splittext2,sizeof(char*)*(spaces2+1));

			//split 0x and number for text[m][3]

            char ** splittext3 = NULL;
			char * p3 = strtok(text[m][3], "x");
			int spaces3 = 0;

            while(p3){
                splittext3 = realloc(splittext3, sizeof(char*) * ++spaces3);

                if(splittext3 == NULL)
                    exit(-1);
                splittext3[spaces3-1] = p3;
                p3 = strtok(NULL, "x");
            }
            splittext3 = realloc(splittext3,sizeof(char*)*(spaces3+1));
			//printf("\nthis is splittext1 :%s\n",splittext3[1]);
			if(strcmp(splittext3[0],"0") != 0){
				fflush(stdout);
//              printf("value of index 2:%s\n",toBinary(atoi(text[m][3]),16));
//				fflush(stdout);
				strcpy(splittext3[0],toBinary(atoi(text[m][3]),16));
                fflush(stdout);

			}
			else{
			    fflush(stdout);
                //printf("value of index 2:%s\n",splittext3[1]);

				strcpy(splittext3[0],SixTeenToBinary(splittext3[1],16));
				fflush(stdout);

			}

			answer = strappend(answer,"001011");
			answer = strappend(answer,toBinary(atoi(splittext2[0]),5));
			answer = strappend(answer,toBinary(atoi(splittext1[0]),5));
			answer = strappend(answer,splittext3[0]);
			//printf("%s\n",answer);
			resultMiddle = strappend(resultMiddle,answer);
			free(splittext1);
			free(splittext2);
			free(splittext3);

		}
		else if(strcmp(text[m][0],"sltu")==0){
                char * answer = "";
			char ** splittext1 = NULL;
			char * p1 = strtok(text[m][1], "$,");
			int spaces = 0,k;
            while(p1){
                splittext1 = realloc(splittext1, sizeof(char*) * ++spaces);

                if(splittext1 == NULL)
                    exit(-1);
                splittext1[spaces-1] = p1;
                p1 = strtok(NULL, "$,");
            }
            splittext1 = realloc(splittext1,sizeof(char*)*(spaces+1));



            char ** splittext2 = NULL;
			char * p2 = strtok(text[m][2], "$,");
			int spaces2 = 0,k2;
            while(p2){
                splittext2 = realloc(splittext2, sizeof(char*) * ++spaces2);

                if(splittext2 == NULL)
                    exit(-1);
                splittext2[spaces2-1] = p2;
                p2 = strtok(NULL, "$,");
            }
            splittext2 = realloc(splittext2,sizeof(char*)*(spaces2+1));

            char ** splittext3 = NULL;
			char * p3 = strtok(text[m][3], "$");
			int spaces3 = 0,k3;
            while(p3){
                splittext3 = realloc(splittext3, sizeof(char*) * ++spaces3);

                if(splittext3 == NULL)
                    exit(-1);
                splittext3[spaces3-1] = p3;
                p3 = strtok(NULL, "$");
            }
            splittext3 = realloc(splittext3,sizeof(char*)*(spaces3+1));

			answer = strappend(answer,"000000");
			answer = strappend(answer,toBinary(atoi(splittext2[0]),5));
            answer = strappend(answer,toBinary(atoi(splittext3[0]),5));
            answer = strappend(answer,toBinary(atoi(splittext1[0]),5));
			answer = strappend(answer,"00000");
			answer = strappend(answer,"101011");
			//printf("%s\n",answer);
			resultMiddle = strappend(resultMiddle,answer);

            free(splittext1);
            free(splittext2);
            free(splittext3);

		}
		else if(strcmp(text[m][0],"sll")==0){
                char * answer = "";
			char ** splittext1 = NULL;
			char * p1 = strtok(text[m][1], "$,");
			int spaces = 0,k;
            while(p1){
                splittext1 = realloc(splittext1, sizeof(char*) * ++spaces);

                if(splittext1 == NULL)
                    exit(-1);
                splittext1[spaces-1] = p1;
                p1 = strtok(NULL, "$,");
            }
            splittext1 = realloc(splittext1,sizeof(char*)*(spaces+1));

            //split $ and number for text[m][2]
            char ** splittext2 = NULL;
			char * p2 = strtok(text[m][2], "$,");
			int spaces2 = 0,k2;
            while(p2){
                splittext2 = realloc(splittext2, sizeof(char*) * ++spaces2);

                if(splittext2 == NULL)
                    exit(-1);
                splittext2[spaces2-1] = p2;
                p2 = strtok(NULL, "$,");
            }
            splittext2 = realloc(splittext2,sizeof(char*)*(spaces2+1));

			//split 0x and number for text[m][3]

            char ** splittext3 = NULL;
			char * p3 = strtok(text[m][3], "x");
			int spaces3 = 0;

            while(p3){
                splittext3 = realloc(splittext3, sizeof(char*) * ++spaces3);

                if(splittext3 == NULL)
                    exit(-1);
                splittext3[spaces3-1] = p3;
                p3 = strtok(NULL, "x");
            }
            splittext3 = realloc(splittext3,sizeof(char*)*(spaces3+1));
			//printf("\nthis is splittext1 :%s\n",splittext3[1]);
			if(strcmp(splittext3[0],"0") != 0){
				fflush(stdout);
//              printf("value of index 2:%s\n",toBinary(atoi(text[m][3]),16));
//				fflush(stdout);
				strcpy(splittext3[0],toBinary(atoi(text[m][3]),5));
                fflush(stdout);

			}
			else{
			    fflush(stdout);
                //printf("value of index 2:%s\n",splittext3[1]);

				strcpy(splittext3[0],SixTeenToBinary(splittext3[1],16));
				fflush(stdout);

			}

			answer = strappend(answer,"00000000000");
			answer = strappend(answer,toBinary(atoi(splittext2[0]),5));
			answer = strappend(answer,toBinary(atoi(splittext1[0]),5));
			answer = strappend(answer,splittext3[0]);
			answer = strappend(answer,"000000");
			//printf("sll : %s\n",answer);
			resultMiddle = strappend(resultMiddle,answer);
			//printf("%s\n",answer);

			free(splittext1);
			free(splittext2);
			free(splittext3);

		}
		else if(strcmp(text[m][0],"srl")==0){
                char * answer = "";
			char ** splittext1 = NULL;
			char * p1 = strtok(text[m][1], "$,");
			int spaces = 0,k;
            while(p1){
                splittext1 = realloc(splittext1, sizeof(char*) * ++spaces);

                if(splittext1 == NULL)
                    exit(-1);
                splittext1[spaces-1] = p1;
                p1 = strtok(NULL, "$,");
            }
            splittext1 = realloc(splittext1,sizeof(char*)*(spaces+1));

            //split $ and number for text[m][2]
            char ** splittext2 = NULL;
			char * p2 = strtok(text[m][2], "$,");
			int spaces2 = 0,k2;
            while(p2){
                splittext2 = realloc(splittext2, sizeof(char*) * ++spaces2);

                if(splittext2 == NULL)
                    exit(-1);
                splittext2[spaces2-1] = p2;
                p2 = strtok(NULL, "$,");
            }
            splittext2 = realloc(splittext2,sizeof(char*)*(spaces2+1));

			//split 0x and number for text[m][3]

            char ** splittext3 = NULL;
			char * p3 = strtok(text[m][3], "x");
			int spaces3 = 0;

            while(p3){
                splittext3 = realloc(splittext3, sizeof(char*) * ++spaces3);

                if(splittext3 == NULL)
                    exit(-1);
                splittext3[spaces3-1] = p3;
                p3 = strtok(NULL, "x");
            }
            splittext3 = realloc(splittext3,sizeof(char*)*(spaces3+1));
			//printf("\nthis is splittext1 :%s\n",splittext3[1]);
			if(strcmp(splittext3[0],"0") != 0){
				fflush(stdout);
//              printf("value of index 2:%s\n",toBinary(atoi(text[m][3]),16));
//				fflush(stdout);
				strcpy(splittext3[0],toBinary(atoi(text[m][3]),5));
                fflush(stdout);

			}
			else{
			    fflush(stdout);
                //printf("value of index 2:%s\n",splittext3[1]);

				strcpy(splittext3[0],SixTeenToBinary(splittext3[1],16));
				fflush(stdout);

			}

			answer = strappend(answer,"00000000000");
			answer = strappend(answer,toBinary(atoi(splittext2[0]),5));
			answer = strappend(answer,toBinary(atoi(splittext1[0]),5));
			answer = strappend(answer,splittext3[0]);
			answer = strappend(answer,"000010");
			resultMiddle = strappend(resultMiddle,answer);
			//printf("%s\n",answer);
			//printf("srl : %s\n",answer);

			free(splittext1);
			free(splittext2);
			free(splittext3);

		}
		else if(strcmp(text[m][0],"sw")==0){
                char * answer = "";
			char ** splittext1 = NULL;
			char * p1 = strtok(text[m][1], "$,");
			int spaces = 0,k;
            while(p1){
                splittext1 = realloc(splittext1, sizeof(char*) * ++spaces);

                if(splittext1 == NULL)
                    exit(-1);
                splittext1[spaces-1] = p1;
                p1 = strtok(NULL, "$,");
            }
            splittext1 = realloc(splittext1,sizeof(char*)*(spaces+1));
			//split 16($3) to 16 and 3
			char keep[2][1000];
			int a=0;
			strcpy(keep[0],"");
			while(text[m][2][a]!='('){
				append(keep[0],text[m][2][a]);
				a++;
			}
			strcpy(keep[1],"");
			a++;//text[m][2][i] is '$'
			a++;//now it is a number
			while(text[m][2][a]!=')'){
				append(keep[1],text[m][2][a]);
				a++;
			}


            //printf("\nYOLO %shey %shey\n",keep[1],keep[0]);
			answer = strappend(answer,"101011");//11 zeros op and rs unused
			answer = strappend(answer,toBinary(atoi(keep[1]),5));//it is 3 from 16($3)
			answer = strappend(answer,toBinary(atoi(splittext1[0]),5));
			answer = strappend(answer,toBinary(atoi(keep[0]),16));//address of 16+2^28 ??? cant plus 2^28 we have just 16 bits
			//printf("%s\n",answer);
			//printf("sw : %s\n",answer);
			resultMiddle = strappend(resultMiddle,answer);

			free(splittext1);

		}
		else if(strcmp(text[m][0],"subu")==0){
                char * answer = "";
			char ** splittext1 = NULL;
			char * p1 = strtok(text[m][1], "$,");
			int spaces = 0,k;
            while(p1){
                splittext1 = realloc(splittext1, sizeof(char*) * ++spaces);

                if(splittext1 == NULL)
                    exit(-1);
                splittext1[spaces-1] = p1;
                p1 = strtok(NULL, "$,");
            }
            splittext1 = realloc(splittext1,sizeof(char*)*(spaces+1));

            char ** splittext2 = NULL;
			char * p2 = strtok(text[m][2], "$,");
			int spaces2 = 0,k2;
            while(p2){
                splittext2 = realloc(splittext2, sizeof(char*) * ++spaces2);

                if(splittext2 == NULL)
                    exit(-1);
                splittext2[spaces2-1] = p2;
                p2 = strtok(NULL, "$,");
            }
            splittext2 = realloc(splittext2,sizeof(char*)*(spaces2+1));

            char ** splittext3 = NULL;
			char * p3 = strtok(text[m][3], "$");
			int spaces3 = 0,k3;
            while(p3){
                splittext3 = realloc(splittext3, sizeof(char*) * ++spaces3);

                if(splittext3 == NULL)
                    exit(-1);
                splittext3[spaces3-1] = p3;
                p3 = strtok(NULL, "$");
            }
            splittext3 = realloc(splittext3,sizeof(char*)*(spaces3+1));

			answer = strappend(answer,"000000");
			answer = strappend(answer,toBinary(atoi(splittext2[0]),5));
            answer = strappend(answer,toBinary(atoi(splittext3[0]),5));
            answer = strappend(answer,toBinary(atoi(splittext1[0]),5));
			answer = strappend(answer,"00000");
			answer = strappend(answer,"100011");
			//printf("subu : %s\n",answer);
			//printf("%s\n",answer);
			resultMiddle = strappend(resultMiddle,answer);
            free(splittext1);
            free(splittext2);
            free(splittext3);

		}





	}

}
//printf("%d %d\n",i,j);
//
char * textSize =  toBinary(i*4,32);
char * dataSize =  toBinary(j*4,32);
//printf("%d\n",hashkey("array2",0));
//printf("%s%s\n",textSize,dataSize);
//printf("%s%s%s%s\n",textSize,dataSize,resultMiddle,resultBack);
    instructionBinary = strappend(instructionBinary,textSize);
    instructionBinary = strappend(instructionBinary,dataSize);
    instructionBinary = strappend(instructionBinary,resultMiddle);
    instructionBinary = strappend(instructionBinary,resultBack);
    printf("%s\n",instructionBinary);

//printf("%s",resultBack);
//printf("%s%s\n",resultMiddle,resultBack);
//printf("%s",resultMiddle);

    fclose(stdin);


return instructionBinary;
}


