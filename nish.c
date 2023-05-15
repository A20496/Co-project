#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct store{
    char opc[20];
    char reg1[6] ; char reg2[6] ; char reg3[6] ;
    int imm ; char addr[20] ; char label[20] ;
};

int check_errors(int instructions, struct store* all,char* all_opcodes[]){
    //d&i stack
    int flg1=0;
    int i=0;

    for (i=0;i<instructions;i++){
        for(int j=0;j<20;j++){
            if ((strcmp(all[i].opc,"var")!=0) && (strcmp(all[i].opc,all_opcodes[j])==0) ){
                flg1=1;
            }
            if (flg1==1 && ((strcmp(all[i].opc,"var")==0))){
                printf("Error: Variables not declared in the beginning");
                break;
            }
        }
    }
    return 0;
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
    int p = 0;
    char filename[] = "data.txt";
    char line[100];
    struct store all[500];

    FILE *fp = fopen(filename, "r");

    if (fp == NULL) { 
        printf("Error opening file %s\n", filename);
        return 1;
    }

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

   //kindly check for errors before this point and stop execution if any are found


   int label_count = l; //no. of labels
   char* label_addresses[label_count];
   for (int i=0; i<l;i++) {
        label_addresses[i] = num_to_binary(label_line[i], 7);
   }

   char opinstructions[25][10] = {"add", "sub", "mov", "mov", "ld", "st", "mul", "div", "rs", "ls", "xor", "or", "and", "not", "cmp", "jmp", "jlt", "jgt", "je", "hlt"};

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

                // int unused = 16 - strlen(answer);
                // char* zeroes;
                // char* initial; 
                // char* final;
                // int v = 0;
                // for (int r=0; r<unused; r++) {
                //     zeroes[r] = '0';
                // }
                // for (int r=0; r<5; r++) {
                //     initial[r] = answer[r];
                // }
                // for (int r = 5 + unused; r<16; r++) {
                //     final[v++] = answer[r];
                // }

                // printf("%s", answer);
                // printf("\n");
                break;
                }
        }   
    
        }

   char* inst1[20] = {"add", "sub", "mov", "mov", "ld", "st", "mul", "div", "rs", "ls", "xor", "or", "and", "not", "cmp", "jmp", "jlt", "jgt", "je", "hlt"};
    
        check_errors(instructions,all,inst1);

   return 0; 
}

