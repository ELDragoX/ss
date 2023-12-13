#include<stdio.h>
#include<stdlib.h>
#include<string.h>

FILE *otfp,*stfp,*imfp,*infp,*plfp;
int o=-1,s=-1,opd,locctr,start,proglen,size;
char opcode[10],operand[10],label[10];

struct SYMTAB{
    char label[10];
    int addr;
}ST[30];

struct OPTAB{
    char opcode[10],hexcode[10];
}OT[30];

void read_optab(){
    while(1){
        o++;
        fscanf(otfp,"%s%s",OT[o].opcode,OT[o].hexcode);
        if(getc(otfp)==EOF){
            break;
        }
    }
}
void passone(){

    otfp=fopen("optab.txt","r");
    stfp=fopen("symtab.txt","w");
    infp=fopen("input.txt","r");
    imfp=fopen("intermfile.txt","w");
    plfp=fopen("proglen.txt","w"); 

    read_optab();

    fscanf(infp,"%s%s%x",label,opcode,&opd);
    if(strcmp(opcode,"START")==0){
        start=opd;
        locctr=start;
        fprintf(imfp,"\t%s\t%s\t%x\n",label,opcode,opd);
        fscanf(infp,"%s\t%s\t%s",label,opcode,operand);
    }
    else{
        locctr=0;
    }

    while(strcmp(opcode,"END")!=0){
      fprintf(imfp,"%x\t%s\t%s\t%s\n",locctr,label,opcode,operand);
      if(strcmp(label,"****")!=0){
        for(int i=0;i<=s;i++){
          if(strcmp(ST[i].label,label)==0){
            printf("duplicate symbol");
            exit(0);
          }
        }
        s++;
        strcpy(ST[s].label,label);
        ST[s].addr=locctr;
        fprintf(stfp,"%s\t%x\n",label,locctr);
      }

      int flag = 0;
      for(int i=0; i<=o; i++){
        if(strcmp(OT[i].opcode,opcode) == 0){
          locctr+=0x3;
          flag = 1;
          size+=3;
          break;
        }
      }

      if(flag==0){
        if(strcmp(opcode, "RESW")==0){
          locctr += atoi(operand)*0x3;
        }
        else if(strcmp(opcode,"WORD")==0){
          locctr+=0x3;
          size+=3;
          
        }
        else if(strcmp(opcode,"RESB")==0){
          locctr+=atoi(operand);
        }
        else if(strcmp(opcode,"BYTE")==0){
          int l = strlen(operand);
          if(operand[0] == 'C' || operand[0] == 'c'){
            l = l-3;
          }
          else{
            l=(l-3)/2;
          }
          locctr+=l;
          size+=l;
      
        }
        else{
            printf("Invalid opcode!");
            exit(0);
        }
    
      }
      fscanf(infp,"%s\t%s\t%s",label,opcode,operand);
    }
  fprintf(imfp,"%x\t%s\t%s\t%s\n",locctr,label,opcode,operand);
  
  fclose(otfp);
  fclose(stfp);
  fclose(imfp);
  fclose(infp);

  proglen = locctr - start;
  fprintf(plfp,"%d-%d",proglen,size);
  fclose(plfp);
}


void display(){
    FILE *otfp,*stfp,*imfp,*infp,*plfp;
    char str;
    printf("INPUT FILE");
    infp=fopen("input.txt","r");
    str=fgetc(infp);
    while(str!=EOF){
        printf("%c",str);
        str=fgetc(infp);
    }
    fclose(infp);

    printf("OPTAB");
    otfp=fopen("optab.txt","r");
    str=fgetc(otfp);
    while(str!=EOF){
        printf("%c",str);
        str=fgetc(otfp);
    }
    fclose(otfp);

    printf("SYMTAB");
    stfp=fopen("symtab.txt","r");
    str=fgetc(stfp);
    while(str!=EOF){
        printf("%c",str);
        str=fgetc(stfp);
    }
    fclose(stfp);

    printf("INTERMEDIATE FILE");
    imfp=fopen("intermfile.txt","r");
    str=fgetc(imfp);
    while(str!=EOF){
        printf("%c",str);
        str=fgetc(imfp);
    }
    fclose(imfp);

    printf("PROGRAM LENGTH");
    plfp=fopen("proglen.txt","r");
    str=fgetc(plfp);
    while(str!=EOF){
        printf("%c",str);
        str=fgetc(plfp);
    }
    fclose(plfp);

}
int main(){
    passone();
    display();
    return 0;
}