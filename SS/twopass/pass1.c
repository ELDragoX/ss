#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char label[10];
char opcode[10];
char operand[10];
char code[10];
char mnemonic[3];

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

void pass1(){
    FILE *otfp,*stfp,*imfp,*infp,*plfp;
    otfp=fopen("optab.txt","r");
    stfp=fopen("symtab.txt","w");
    infp=fopen("input.txt","r");
    imfp=fopen("intermfile.txt","w");
    plfp=fopen("proglen.txt","w");

    int locctr,proglen,start;

    fscanf(infp,"%s\t%s\t%s",label,opcode,operand);
    if(strcmp(opcode,"START")==0){
        start=atoi(operand);
        locctr=start;
        fprintf(imfp,"\t%s\t%s\t%s\n",label,opcode,operand);
        fscanf(infp,"%s\t%s\t%s",label,opcode,operand);
    }
    else{
        locctr=0;
        start=0;
        fprintf(imfp,"****\t****\tSTART\t0000\n");
    }
    while(strcmp(opcode,"END")!=0){
        fprintf(imfp,"%d\t%s\t%s\t%s\n",locctr,label,opcode,operand);
        if(strcmp(label,"****")!=0){
            fprintf(stfp,"%s\t%d\n",label,locctr);
        }
        fscanf(otfp,"%s\t%s",code,mnemonic);
        while(strcmp(code,"END")!=0){
            if(strcmp(code,opcode)==0){
                locctr+=3;
                break;
            }
            fscanf(otfp,"%s\t%s",code,mnemonic);
        }
        if(strcmp(opcode,"WORD")==0){
            locctr+=3;
        }
        else if(strcmp(opcode,"RESW")==0){
            locctr+=(3*(atoi(operand)));
        }
        else if(strcmp(opcode,"RESB")==0){
            locctr+=atoi(operand);
        }
        else if(strcmp(opcode,"BYTE")==0){
            locctr+=strlen(operand);
        }

      fscanf(infp,"%s\t%s\t%s",label,opcode,operand);
    }
  fprintf(imfp,"%d\t%s\t%s\t%s\n",locctr,label,opcode,operand);
  fclose(otfp);
  fclose(stfp);
  fclose(imfp);
  fclose(infp);
  
  proglen = locctr - start;
  fprintf(plfp,"%d",proglen);
  fclose(plfp);
  
  display();
}

int main(){

  pass1();
  return 0;
}