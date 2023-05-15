#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct store{
    char opc[20];
    char reg1[6] ; char reg2[6] ; char reg3[6] ;
    int imm ; char addr[20] ; char label[20] ;
};

char* insertZeroes(const char* str, int i, int n) {
    int len = strlen(str);
    int newLen = len + n;
    char* newStr = (char*)malloc((newLen + 1) * sizeof(char));
    int j, k;

    if (i < 0 || i > len) {
        printf("Invalid position.\n");
        return NULL;
    }

    for (j = 0, k = 0; j < newLen; j++) {
        if (j >= i && j < i + n) {
            newStr[j] = '0';
        } else {
            newStr[j] = str[k];
            k++;
        }
    }

    newStr[newLen] = '\0';
    return newStr;
}

char* num_to_binary(int number, int bits) {         //converts given number to binary of n bits
    char* binary = (char*)malloc(bits + 1);
    for (int i=0;i<bits;i++) {
        binary[i] = '0';
    }

    binary[bits] = '\0';

    for (int i = bits - 1; i >= 0; i--) {
        if (number % 2 == 1) {
            binary[i] = '1';
        }
        number /= 2;
    }

    return binary;
}

 
int check_binary(int num){    //not sure if this function is correct or not 
    int flag=0;               //checks if number is 7 bit binary 
    while (num > 0) {         // preferred to make separate functions to check binary and length 7 
        if (num % 10 <= 1) { 
            flag=1; 
        }
        num /= 10; 
    }
    int len=0; 
    if (flag==1)
    {
        while(num>0){
            len++;
            num/=10;
        }
        if(len==7) flag=1;
        else flag=0;
    }
    return flag;
}

int search(int n,int m,char str[],char arr[n][m]){  
    int flag=0;                           //checks if given string is present in an array of string or not
    for (int i=0 ; i<n ; i++){
        if(strcmp(str,arr[i])==0) {
            flag=1;
        }
    }
    return flag;
}

int main() {

    //opening files here

    FILE* answers_file;
    char fname3[] = "answers.txt";

    answers_file = fopen(fname3, "w");


    if (answers_file == NULL) {
        printf("Failed to open the error file");
    }

    FILE* errors_file;
    char fname[] = "errors.txt";

    errors_file = fopen(fname, "w");


    if (errors_file == NULL) {
        printf("Failed to open the error file");
    }


    int p = 0;
    char filename[] = "data.txt";
    char line[100];
    struct store all[500];

    FILE *fp = fopen(filename, "r");

    if (fp == NULL) { 
        printf("Error opening file %s\n", filename);
        return 1;
    }

    //finished opening files

    int i=0;
    int instructions=0;
    int var_counter=0;
    char var_arr[200][200]; 
    int label_counter=0; int l=0;
    char label_arr[200][200];
    char valid_label[128][128];
    int label_line[128];


    char jump_inst[4][4]={"jmp","jlt","jgt","je"};
    char reg_arr[8][6]={"R0","R1","R2","R3","R4","R5","R6","FLAGS"};

    while (fgets(line, sizeof(line), fp) != NULL) {

        line[strcspn(line, "\n")] = '\0';

        if(strlen(line)>0) {
        char*string[7];
        char *token = strtok(line, " "); 
        int count=0;
        while (token != NULL) {
            string[count]=token;
            //printf("%s\n", token);
            token = strtok(NULL, " ");
            count++;
        }
        
        strcpy(all[i].opc,string[0]);
        
        //initialising all to be null
        strcpy(all[i].reg1,"NULL\0");
        strcpy(all[i].reg2,"NULL\0");
        strcpy(all[i].reg3,"NULL\0");
        strcpy(all[i].addr,"NULL\0");
        strcpy(all[i].label,"NULL\0"); 
        all[i].imm=-1; //since imm is an integer value

        if (strcmp(all[i].opc,"var")==0)    //array of all the variables 
        { 
            strcpy(var_arr[var_counter],string[1]); 
            strcpy(all[i].addr,string[1]);
            var_counter++;
        }

        if ((strcmp(all[i].opc,"ld")==0) || (strcmp(all[i].opc,"st")==0)) strcpy(all[i].addr,string[2]);

        if (search(4,4,all[i].opc,jump_inst)==1) 
        {
            strcpy(all[i].label,string[1]);
            strcpy(label_arr[label_counter],string[1]);  //array of labels
            label_counter++; 
        }

        if(all[i].opc[strlen(all[i].opc)-1]==':') 
        {
            char label[strlen(all[i].opc)];
            for(int x=0 ; x<(strlen(all[i].opc)-1) ; x++) {
                label[x]=all[i].opc[x];
            } 
            label[strlen(all[i].opc)]='\0';

            strcpy(valid_label[l],label);
            label_line[l] = instructions;
            l++;
        }

        for (int j=1;j<count;j++) 
        {   
            if (search(9,6,string[j],reg_arr)) 
            {
                if (j==1) strcpy(all[i].reg1,string[j]);
                if (j==2) strcpy(all[i].reg2,string[j]);
                if (j==3) strcpy(all[i].reg3,string[j]);
            }
            
            if (string[j][0]=='$') 
            {
                char newarr[20];
                for(int k=1,h=0 ; k<sizeof(string[j]) ; k++,h++) 
                    newarr[h]=string[j][k];
                newarr[sizeof(string[j])]='\0';
                int num = atoi(newarr) ;
                all[i].imm=num;
            }
        }

        i++; instructions++;
}}

    fclose(fp);

    // for (int j=0 ; j<l ; j++){
    //     printf("%s\n",valid_label[j]);
    // }
    // printf("\n");
    // for (int j=0 ; j<l ; j++){
    //     printf("%d\n",label_line[j]);
    // }
    // printf("\n");
    
    // for (int j=0 ; j<var_counter ; j++){
    //     printf("%s", var_arr[j]);
    // }

    char* var_addresses[var_counter];

    for (int i=0; i<var_counter;i++) {
        var_addresses[i] = num_to_binary(instructions + i, 7);
    }
    
    // for (int j=0;j<instructions;j++) {
    //     printf("opcode - %s\n",all[j].opc);
    //     printf("register one - %s\n",all[j].reg1);
    //     printf("register two - %s\n",all[j].reg2);
    //     printf("register three - %s\n",all[j].reg3);
    //     printf("immediate value - %d\n",all[j].imm);
    //     printf("memory address - %s\n",all[j].addr);
    //     printf("label - %s\n",all[j].label);
    //     printf("\n");
    // }


    
    //checking for errors here

    char opinstructions[25][10] = {"add", "sub", "mov", "mov", "ld", "st", "mul", "div", "rs", "ls", "xor", "or", "and", "not", "cmp", "jmp", "jlt", "jgt", "je", "hlt"};

    int flag_v = 0;
    for (int i=0;i<instructions;i++) {
        if (strcmp(all[i].opc,"var")!=0) {
            flag_v = 1;
        }
        if (flag_v == 1) {
            if (strcmp(all[i].opc, "var")==0) {
            char str__[30];
            char num1[10];
            sprintf(num1, "%d", instructions+1);
            strcat(str__, "line ");
            strcat(str__, num1);
            strcat(str__, " : var defined at wrong place");
                fprintf(errors_file, "%s", str__);
                exit(1);
            }
        }
    }

    int flag_op = 0;

    for (int i=0;i<instructions;i++) {
            if (strcmp(all[i].opc, "var")!=0) {
                for (int j=0; j<20; j++) {
                    if (strcmp(all[i].opc, opinstructions[j])==0) {
                        flag_op = 1;
                    }
                }
            }

            else {
                flag_op = 1;
            }

        if (flag_op == 0) {
            char str2[30];
            char num2[10];
            sprintf(num2, "%d", instructions+1);
            strcat(str2, "line ");
            strcat(str2, num2);
            strcat(str2, " : typo in opcode");

           fprintf(errors_file, "%s", str2); 
           exit(1);
        }

        flag_op = 0;

    }

    int flag_varb = 0;

    for (int i=0;i<instructions;i++) {
        if (strcmp(all[i].opc, "ld")==0 || strcmp(all[i].opc, "st")==0) {

            if (strcmp(all[i].addr, "NULL")!=0) {

            for (int j=0; j<var_counter; j++) {
                if (strcmp(all[i].addr, var_arr[j])==0) flag_varb = 1;
            }
        }

            else {
                flag_varb = 1;
            }
    
        if (flag_varb==0) {

            char str3[30];
            char num3[10];
            sprintf(num3, "%d", instructions+1);
            strcat(str3, "line ");
            strcat(str3, num3);
            strcat(str3, " : memory address in load and store is not a variable");


            fprintf(errors_file, "%s", str3); 
            exit(1);
        }

        flag_varb = 0;
    }

}

    int label_count = l; //no. of labels //important

    for(int t=0;t<instructions;t++) {
        if (all[t].imm!=-1) {
        if (all[t].imm > 127 || all[t].imm < 0) {

            char str4[30];
            char num4[10];
            sprintf(num4, "%d", instructions+1);
            strcat(str4, "line ");
            strcat(str4, num4);
            strcat(str4, " : Value not in the inclusive range of 0 to 127");

            fprintf(errors_file, "%s", str4); 
            exit(1);
            }
        }
    }

    int flag_halt = 0;

    for(int i=0;i<instructions;i++) {

    if (strcmp(all[i].opc,"hlt")==0) {
        flag_halt = 1;
        if(strcmp(all[instructions-1].opc, "hlt")!=0) {

            char str5[30];
            char num5[10];
            sprintf(num5, "%d", instructions+1);
            strcat(str5, "line ");
            strcat(str5, num5);
            strcat(str5, " : hlt not at the end");

            fprintf(errors_file, "%s", str5); 
            exit(1);
            }
    }
}

if (flag_halt==0) {
        fprintf(errors_file, "%s", "halt is not present"); 
        exit(1);
    }


    int flag_lab = 0;

    for (int i=0;i<instructions;i++) {
        if (strcmp(all[i].opc, "jmp")==0 || strcmp(all[i].opc, "jlt")==0 || strcmp(all[i].opc, "jgt")==0 || strcmp(all[i].opc, "je")==0) {

            if (strcmp(all[i].label, "NULL")!=0) {

            for (int j=0; j<l; j++) {
                if (strcmp(all[i].label, valid_label[j])==0) flag_lab = 1;
            }
        }

            else {
                flag_lab = 1;
            }
    
        if (flag_lab==0) {
            char str_[30];
            char num[10];
            sprintf(num, "%d", instructions+1);
            strcat(str_, "line ");
            strcat(str_, num);
            strcat(str_, " : label used in jump instructions is not defined");
            fprintf(errors_file, "%s", str_); 
            exit(1);
        }

        flag_lab = 0;
    }
}


fclose(errors_file);

   //kindly check for errors before this point and stop execution if any are found


   char* label_addresses[label_count];
   for (int i=0; i<l;i++) {
        label_addresses[i] = num_to_binary(label_line[i], 7);
   }


    char *answers[128];
    int answer_count;
    int address_count[128];
    int flag;

    

    for (int i=0;i<instructions;i++) {
        char opcodes[25][10] = {"00000", "00001", "00010", "00011", "00100", "00101", "00110", "00111", "01000", "01001", "01010", "01011", "01100", "01101", "01110", "01111", "11100", "11101", "11111", "11010"};
        char *answer;
        for (int j=0;j<20;j++) {
            if (strcmp(all[i].opc, opinstructions[j])==0) {
                answer = opcodes[j];
                if (strcmp(all[i].reg1, "NULL")!=0) {
                    if (strcmp(all[i].reg1, "FLAGS")==0) strcat(answer, "111");
                    else {
                    // char* temp_ = all[i].reg1[1];
                    strcat(answer, num_to_binary(all[i].reg1[1], 3));
                    }
                }
                if (strcmp(all[i].reg2, "NULL")!=0) {
                    if (strcmp(all[i].reg2, "FLAGS")==0) strcat(answer, "111");
                    else {
                    // char* temp_ = all[i].reg1[2];
                    strcat(answer, num_to_binary(all[i].reg2[1], 3));
                    }
                }
                if (strcmp(all[i].reg3, "NULL")!=0) {
                    if (strcmp(all[i].reg3, "FLAGS")==0) strcat(answer, "111");
                else {
                    // char* temp_ = all[i].reg3[1];
                    strcat(answer, num_to_binary(all[i].reg3[1], 3));
                }
            }
                if (all[i].imm != -1) strcat(answer, num_to_binary(all[i].imm, 7));
                if (strcmp(all[i].addr,"NULL")!=0) {
                    for (int k=0;k<var_counter;k++) {
                        if (strcmp(all[i].addr, var_arr[k])==0) strcat(answer, var_addresses[k]);
                    }
                }
                if (strcmp(all[i].label, "NULL")!=0) {
                    for (int k=0; k<label_count; k++) {
                        if (strcmp(all[i].label, label_arr[k])==0) strcat(answer, label_addresses[k]);
                    }
                }

                if (strcmp(answer, "11010")==0) {
                    strcat(answer, "00000000000");
                }

                int unused = 16 - strlen(answer);
            
                
                fprintf(answers_file, "%s", insertZeroes(answer, 5, unused)); 
                fprintf(answers_file, "%s", "\n");
                break;

                }
        }   
    
        }

   return 0; 
}

