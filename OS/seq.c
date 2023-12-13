#include<stdio.h>
#include<stdlib.h>

struct memory{
    int data;
};

void main(){
    int nb;
    printf("\nEnter total number of memory blocks:");
    scanf("%d",&nb);
    struct memory memblock[nb];
    for(int i=0;i<nb;i++){
        memblock[i].data=0;
    }
    int ch=0;
    while(ch!=3){
        printf("\n1.Add Files \n 2.Display Files \n 3.Exit\n");
        printf("\nEnter choice:");
        scanf("%d",&ch);
        switch(ch){
            case 1:{
                int idx;
                int fsize;
                printf("\nEnter size of file:");
                scanf("%d",&fsize);
                
                printf("\nEnter starting index of memory to add files:");
                scanf("%d",&idx);
                if(memblock[idx].data==1){
                    printf("\nmemory Index already allocated\n");
                    break;
                }
                int flag=0;
                for(int i=idx;i<idx+fsize;i++){
                    if(memblock[i].data==1){
                        flag=1;
                    }
                }
                if(flag==0){
                    for(int j=idx;j<idx+fsize;j++){
                        memblock[j].data=1;
                    }
                }else{
                    printf("\nError allocating files insufficient memory\n");

                }
    
                break;

            }
            case 2:{
                printf("MEMORY ALLOCATED");
                for(int k=0;k<nb;k++){
                    if(memblock[k].data == 1){
                        printf("\n%d------>1\n",k);
                    }
                    else{
                        printf("\n%d\n",k);
                    }
                }
            }
            
            
        }
    }
}