#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void main(){
    int f[50],index[50],ind,count,n,c=1;
    for(int i=0;i<50;i++){
        f[i]=0;
    }
    do{
       
        printf("Enter the index block index");
        scanf("%d",&ind);
        if(f[ind]==0){
            f[ind]=1;
            
        }
        else{
            printf("Index already allocated!");
            continue;
        }
        do{
        printf("Enter no of blocks:");
        scanf("%d",&n);
        count=0;
        printf("Enter blocks indexes:");
        for(int j=0;j<n;j++){
            scanf("%d",&index[j]);
            if(f[index[j]]==0){
                count++;
            }
            else{
                printf("index %d already allocated!",index[j]);
            }
        }
        if(count==n){
            for(int k=0;k<n;k++){
                f[index[k]]=1;
                printf("%d---->%d:%d",ind,index[k],1);
            }

        }
        else{
            printf("Blocks already allocated try new combination of blocks");
        }

    }while(count!=n);
    printf("Enter more files (Yes-->1 No-->0)");
    scanf("%d",&c);
    }while(c==1);
}