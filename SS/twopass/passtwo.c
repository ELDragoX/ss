#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct SYMTAB{
    char label[10],addr[10];
    
}ST[30];

struct OPTAB{
    char opcode[10],hexcode[10];
}OT[30];

FILE *imfp,*otfp,*stfp,*plfp,*alfp,*ocfp;
int o=-1,s=-1;
char address[10],label[10],opcode[10],operand[10],s_addr[10],w[10],b[10],line[100];


void read_optab(){
   
    while(1){
        o++;
        fscanf(otfp,"%s%s",OT[o].opcode,OT[o].hexcode);
        if(getc(otfp)==EOF){
            break;
        }
    }
}
void read_symtab(){
  
    while(1){
        s++;
        fscanf(stfp,"%s%s",ST[s].label,ST[s].addr);
        if(getc(stfp)==EOF){
            break;
        }
    }
}

void pass2(){
   
    imfp=fopen("intermfile.txt","r");
    otfp=fopen("optab.txt","r");
    stfp=fopen("symtab.txt","r");
    plfp=fopen("proglen.txt","r");
    alfp=fopen("asl.txt","w");
    ocfp=fopen("objcode.txt","w");
    
    int prog_len,obj_len;

    fgets(line,100,plfp);
    char *token=strtok(line,"-");
    prog_len=strtol(token,NULL,16);
    token=strtok(NULL, "\n");
    obj_len=strtol(token,NULL,16);
   
    read_optab();
    read_symtab();
    
    fscanf(imfp,"%s\t%s\t%s",label,opcode,operand);
    strcpy(s_addr,operand);
    if(strcmp(opcode,"START")==0){
        
        fprintf(alfp,"\t%s\t%s\t%s\n",label,opcode,operand);
        fprintf(ocfp,"H^%6s^%06s^%06x\n",label,operand,prog_len);
        fprintf(ocfp,"T^%06s^%02x",operand,obj_len);
        fscanf(imfp,"%s\t%s\t%s\t%s",address,label,opcode,operand);
    }
    while(strcmp(opcode,"END")!=0){
       
       if(strcmp(opcode,"WORD")==0){
            sprintf(w,"%x",atoi(operand));
            fprintf(alfp,"%s\t%s\t%s\t%s\t%06s\n",address,label,opcode,operand,w);
            fprintf(ocfp,"^%06s",w);

        }
        else if(strcmp(opcode,"BYTE")==0){
            sprintf(b,"%x",operand[2]);
            fprintf(alfp,"%s\t%s\t%s\t%s\t%06s\n",address,label,opcode,operand,b);
            fprintf(ocfp,"^%06s",b);
        }
        else if(strcmp(opcode,"RESB")==0 || strcmp(opcode,"RESW")==0){
            
            fprintf(alfp,"%s\t%s\t%s\t%s\n",address,label,opcode,operand);
        }
        else{
            
            int j=0;
            while(strcmp(opcode,OT[j].opcode)!=0){
                j++;
            }
            int i=0;
            while(strcmp(operand,ST[i].label)!=0){
                i++;
            }
            fprintf(alfp,"%s\t%s\t%s\t%s\t%02s%04s\n",address,label,opcode,operand,OT[j].hexcode,ST[i].addr);
            fprintf(ocfp,"^%s%s",OT[j].hexcode,ST[i].addr);

        }
        fscanf(imfp,"%s\t%s\t%s\t%s",address,label,opcode,operand);

    }
    fprintf(alfp,"\t%s\t%s\t%s",label,opcode,operand);
    fprintf(ocfp,"\nE^%06s",s_addr);
    fclose(otfp);
    fclose(stfp);
    fclose(imfp);
    fclose(alfp);
    fclose(plfp);
    fclose(ocfp);
}


void main(){
    
    pass2();
    
}