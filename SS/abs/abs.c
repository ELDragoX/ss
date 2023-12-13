#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main() {
    FILE *infp,*opfp;
    char line[100],obj[6];
    int t_addr,t_len;
    
    infp=fopen("input.txt","r");
    opfp=fopen("output.txt","w");
    
    
    while (fgets(line, 100, infp) != NULL) {
        char *token=strtok(line,"^");
        if (strcmp(token,"T")==0) {
            t_addr=strtol(strtok(NULL,"^"),NULL,16);
            t_len=strtol(strtok(NULL,"^"),NULL,16);  
            token=strtok(NULL,"^");
            while(token!=NULL){
                strcpy(obj,token);
                fprintf(opfp,"%06X : %s\n",t_addr,obj);
                t_addr+=0x3;
            token=strtok(NULL,"^");
            }
        } else if (strcmp(token,"E")==0) {
            break; 
        }
    }
    fclose(infp);
    fclose(opfp);
}
