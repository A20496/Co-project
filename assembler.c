#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct store{
    char opc[20];
    char reg1[6] ; char reg2[6] ; char reg3[6] ;
    int imm ; char addr[50] ; char label[50] ;
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
    while (num > 0) {         //preferred to make separate functions to check binary and length 7 
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
    char label_arr[200][200];      //label used
    char valid_label[200][200];    //label defined
    int label_line[200];
    char error_arr[200][200];
    int err=0;

    char jump_inst[4][4]={"jmp","jlt","jgt","je"};
    char inst[25][10]={"var","add","sub","mov","ld","st","mul","div","rs","ls","xor","or","and","not",
    "cmp","jmp","jlt","jgt","je","hlt"};
    char* inst1[25][10]={"add","sub","mov","ld","st","mul","div","rs","ls","xor","or","and","not",
    "cmp","jmp","jlt","jgt","je","hlt"};
    char reg_arr[8][6]={"R0","R1","R2","R3","R4","R5","R6","FLAGS"};


    while (fgets(line, sizeof(line), fp) != NULL) {

        line[strcspn(line, "\n")] = '\0'; 

        if(strlen(line)>0) {
        char string[10][20];
        char *token = strtok(line, " "); 
        char save[50]="NULL";
        //printf("%s ",token);
        if(search(25,10,token,inst)) 
        {
            strcpy(string[0],token);
            //printf("%s ",string[0]);
        }
        else if (token[strlen(token)-1]==':') 
        {
            strcpy(save,token);
            char label[strlen(token)];
            for(int x=0 ; x<(strlen(token)-1) ; x++) 
            {
                label[x]=token[x];
            } 
                label[strlen(token)-1]='\0';
                strcpy(valid_label[l],label);  //array of label defined
                label_line[l] = instructions;
                l++; 

            //strcpy(all[i].label,label);
            //printf("%s\n",all[i].label);
        }
        token=strtok(NULL, " ");
        if (token)
        {
            //printf("%s ",token);
          if(search(25,10,token,inst)) 
        {
            strcpy(string[0],token);
            token = strtok(NULL, " "); 
            //printf("%s ",string[0]);
        }
          
        }  

        
        int count=1;
        //printf("%s ",token);
        while (token != NULL) 
        {  
            strcpy(string[count],token);
            //printf("%s ", token);
            //printf("%s ",string[count]);
            token = strtok(NULL, " ");
            count++;
        }
        //printf("\n");
        if (strcmp(save,"NULL")!=0) 
        {
            //strcpy(string[count],save);
            count++;
        }

        //printf("\n%d\n ",count);
        
        //for (int j=0;j<count;j++) printf("%s ", string[j]);
            //printf("\n");

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
            strcpy(label_arr[label_counter],string[1]);  //array of labels used
            label_counter++; 
        }

        if (search(label_counter,200,string[0],label_arr)==1){
                //to check colon after label
                char* label=string[0];
                int ll=strlen(label);
                if (label[ll-1]!=":"){
                    printf("Label needs ':' to be valid");
               }
    }

        char typeA[10][10]={"add","sub","mul","xor","or","and"};
        char typeB[10][10]={"mov","rs","ls"};
        char typeC[10][10]={"mov","div","cmp"};
        char typeD[10][10]={"ld","st"};
        char typeE[10][10]={"jlt","jgt","je","jmp"}; //typeF halt
        

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
    }
//printf("y\n");
}

    fclose(fp);

    /*for (int j=0 ; j<l ; j++){
        printf("%s\n",valid_label[j]);
    }
    printf("\n");
    for (int j=0 ; j<l ; j++){
        printf("%d\n",label_line[j]); //counting from 0
    }
    printf("\n");
    /*for (int j=0 ; j<var_counter ; j++){
        printf("%s ",var_arr[j]);
    }*/
    //printf("y\n");

        char* var_addresses[var_counter];

    for (int i=0; i<var_counter;i++) {
        var_addresses[i] = num_to_binary(instructions + i - 1, 7);
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


        char typeA[10][10]={"add","sub","mul","xor","or","and"};
        char typeB[10][10]={"mov","rs","ls"};
        char typeC[10][10]={"mov","div","cmp"};
        char typeD[10][10]={"ld","st"};
        char typeE[10][10]={"jlt","jgt","je","jmp"}; //typeF halt


        for(int j=0 ; j<instructions ; j++)
        {

        // illegal use of flag 

        if ((!strcmp(all[j].reg1,"FLAGS"))||(!strcmp(all[j].reg2,"FLAGS"))||(!strcmp(all[j].reg3,"FLAGS")))
        {
            if (strcmp(all[j].opc,"mov")!=0)
            {
                char str1[100];
                sprintf(str1,"line %d : illegal use of flag\n",j+1);
                //printf("%s",str1);
                fprintf(errors_file, "%s", str1);
                //fputs(str1,errors_file); 
                exit(1);
                
            }
            

            else 
            {
                if ((!strcmp(all[j].reg1,"FLAGS"))|| (!strcmp(all[j].reg3,"FLAGS")))
                {
                char str1[100];
                sprintf(str1,"line %d : illegal use of flag\n",j+1);
                //printf("%s",str1);
                fprintf(errors_file, "%s", str1);
                //fputs(str1,errors_file); 
                exit(1);
                
                }
            }
        }

        // syntax error 
        if (search(10,10,all[j].opc,typeA)) 
        {
            if ((!strcmp(all[j].reg1,"NULL"))||(!strcmp(all[j].reg2,"NULL"))||(!strcmp(all[j].reg3,"NULL")))
            {
                char str1[100];
                sprintf(str1,"line %d : syntax error/invalid register name\n",j+1);
                fprintf(errors_file, "%s", str1); 
                
            }
        }

        else if (!strcmp(all[j].opc,"mov"))
        {
            if (!strcmp(all[j].reg1,"NULL"))
            {
                char str1[100];
                sprintf(str1,"line %d : syntax error/invalid register name\n",j+1);
                fprintf(errors_file, "%s", str1); 
                exit(1);
            }
            else if ((!strcmp(all[j].reg2,"NULL"))&&(all[j].imm==-1))
            {
                char str1[100];
                sprintf(str1,"line %d : syntax error/invalid register name\n",j+1);
                fprintf(errors_file, "%s", str1); 
                exit(1);
            }
        }
        else if (search(10,10,all[j].opc,typeB))
        {
            if ((!strcmp(all[j].reg1,"NULL")) || (all[j].imm==-1))
            {
                char str1[100];
                sprintf(str1,"line %d : syntax error/invalid register name\n",j+1);
                fprintf(errors_file, "%s", str1); 
                exit(1);
            }
        }

        else if (search(10,10,all[j].opc,typeC))
        {
            if ((!strcmp(all[j].reg1,"NULL"))||(!strcmp(all[j].reg2,"NULL")))
            {
                char str1[100];
                sprintf(str1,"line %d : syntax error/invalid register name\n",j+1);
                fprintf(errors_file, "%s", str1); 
                exit(1);    
            }
        }
        else if (search(10,10,all[j].opc,typeD))
        {
            if ((!strcmp(all[j].reg1,"NULL"))||(!strcmp(all[j].addr,"NULL")))
            {
                char str1[100];
                sprintf(str1,"line %d : syntax error/invalid register name\n",j+1);
                fprintf(errors_file, "%s", str1); 
                exit(1);
            }
        }
        else if (search(10,10,all[j].opc,typeE))
        {
            if(!strcmp(all[j].label,"NULL")) 
            {
                char str1[100];
                sprintf(str1,"line %d : syntax error/invalid register name\n",j+1);
                fprintf(errors_file, "%s", str1); 
                exit(1);
            }
        }
    }
    for (int k=0;k<var_counter;k++){
                if (search(label_counter,200,label_arr[k], var_arr)==1){
                   printf("misuse of labels and variables"); 
               }
    }

 char opinstructions[25][10] = {"add", "sub", "mov", "mov", "ld", "st", "mul", "div", "rs", "ls", "xor", "or", "and", "not", "cmp", "jmp", "jlt", "jgt", "je", "hlt"};

    //checking for errors below this point


    int flag_v = 0;
    for (int i=0;i<instructions;i++) {
        if (strcmp(all[i].opc,"var")!=0) {
            flag_v = 1;
        }
        if (flag_v == 1) {
            if (strcmp(all[i].opc, "var")==0) {
            char str__[30];
            char num1[10];
            sprintf(num1, "%d", i+1);
            strcat(str__, "line ");
            strcat(str__, num1);
            strcat(str__, " : var defined at wrong place");
                fprintf(errors_file, "%s", str__);
                exit(1);
            }
        }
    }


    return 0;

}