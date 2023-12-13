#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void bit_mask(int bit[3],int mask[12]){
    int m1,m2,m3,m4;
    long b;
    for(int i=0;i<3;i++){
        b=bit[i];
        // printf("%ld",b);
        switch(b){
            case 0:{
                m1=0,m2=0,m3=0,m4=0;
                break;
            }
            case 1:{
                m1=0,m2=0,m3=0,m4=1;
                break;
            }
            case 2:{
                m1=0,m2=0,m3=1,m4=0;
                break;
            }
            case 3:{
                m1=0,m2=0,m3=1,m4=1;
                break;
            }
            case 4:{
                m1=0,m2=1,m3=0,m4=0;
                break;
            }
            case 5:{
                m1=0,m2=1,m3=0,m4=1;
                break;
            }
            case 6:{
                m1=0,m2=1,m3=1,m4=0;
                break;
            }
            case 7:{
                m1=0,m2=1,m3=1,m4=1;
                break;
            }
            case 8:{
                m1=1,m2=0,m3=0,m4=0;
                break;
            }
            case 9:{
                m1=1,m2=0,m3=0,m4=1;
                break;
            }
            case 10:{
                m1=1,m2=0,m3=1,m4=0;
                break;
            }
            case 11:{
                m1=1,m2=0,m3=1,m4=1;
                break;
            }
            case 12:{
                m1=1,m2=1,m3=0,m4=0;
                break;
            }
            case 13:{
                m1=1,m2=1,m3=0,m4=1;
                break;
            }
            case 14:{
                m1=1,m2=1,m3=1,m4=0;
                break;
            }
            case 15:{
                m1=1,m2=1,m3=1,m4=1;
                break;
            }
        }
    mask[4*i]=m1;
    mask[4*i+1]=m2;
    mask[4*i+2]=m3;
    mask[4*i+3]=m4;
    }
}

void main(){
    FILE *infp,*opfp;
    infp=fopen("input.txt","r");
    opfp=fopen("output.txt","w");

    int rel_addr,s_addr,p_len,t_addr,t_len,obj,bitmask,bit[3],mask[12];
    char line[100],name[6],type[1],c[1];


    printf("Enter relocation Address:");
    scanf("%06x",&rel_addr);
    printf("Rellocation Address: %06x",rel_addr);
while(fgets(line,100,infp)!=NULL){
char *token=strtok(line,"^");
strcpy(type,token);
if(strcmp(type,"H")==0){
    token=strtok(NULL,"^");
    strcpy(name,token);
    token=strtok(NULL,"^");
    s_addr=strtol(token,NULL,16);
    token=strtok(NULL,"^");
    p_len=strtol(token,NULL,16);
    fprintf(opfp,"%s^%s^%06x^%06x",type,name,s_addr+rel_addr,p_len);
    
}
else if(strcmp(type,"T")==0){
    token=strtok(NULL,"^");
    t_addr=strtol(token,NULL,16);
    token=strtok(NULL,"^");
    t_len=strtol(token,NULL,16);
    token=strtok(NULL,"^");
    bitmask=strtol(token,NULL,16);
    for(int i=0;i<3;i++){
        strncpy(c,token,1);
        bit[i]=strtol(c,NULL,16);
        token++;
    }
    bit_mask(bit,mask);
    token=strtok(NULL,"^");
    
    fprintf(opfp,"\n%s^%06x^%02x^%03x",type,t_addr+rel_addr,t_len,bitmask);
    int count=0;
    while(token!=NULL){
        obj=strtol(token,NULL,16);
        if(mask[count]==1){
            fprintf(opfp,"^%06x",obj+rel_addr);
        }
        else{
            fprintf(opfp,"^%06x",obj);
        }
        count++;
        token=strtok(NULL,"^");
    }
   

}
else if(strcmp(type,"E")==0){
    fprintf(opfp,"\n%s^%06x\n",type,s_addr+rel_addr);
    break;
}
}




    fclose(infp);
    fclose(opfp);
}