#include <stdio.h>
#include<string.h>

struct store{
    char opc[20];
    char reg1[6] ; char reg2[6] ; char reg3[6] ;
    int imm ; char addr[20] ; char label[20] ;
};
 
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
    int label_counter=0;
    char label_arr[200][200];
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

    /*for (int j=0 ; j<label_counter ; j++){
        printf("%s",label_arr[j]);
    }
    printf("\n");
    for (int j=0 ; j<var_counter ; j++){
        printf("%s",var_arr[j]);
    }*/
    
    for (int j=0;j<instructions;j++) {
        printf("opcode - %s\n",all[j].opc);
        printf("register one - %s\n",all[j].reg1);
        printf("register two - %s\n",all[j].reg2);
        printf("register three - %s\n",all[j].reg3);
        printf("immediate value - %d\n",all[j].imm);
        printf("memory address - %s\n",all[j].addr);
        printf("label - %s\n",all[j].label);
        printf("\n");
    }
    
    return 0; 
}

