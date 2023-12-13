#include<stdio.h>
#include<stdlib.h>

struct process{
    int pid,at,bt,ct,wt,tat,rt,flag;
}p[10];

struct process temp;



void disp_sort(struct process p[10],int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n-i-1;j++){
            if(p[j].pid>p[j+1].pid){
                temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
        }
    }
}

void rr_sort(struct process p[10],int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n-i-1;j++){
            if(p[j].at>p[j+1].at){
                temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
        }
    }
}

void main(){
    int n,tq;
    int front=-1,rear=-1;
    printf("Enter number of process:");
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        p[i].pid=i+1;
        printf("Enter arrival time of Process%d",i+1);
        scanf("%d",&p[i].at);
        printf("Enter burst time of Process%d",i+1);
        scanf("%d",&p[i].bt);
        p[i].ct=0,p[i].wt=0,p[i].tat=0,p[i].rt=p[i].bt,p[i].flag=0;
    }
    printf("Enter time Quanta:");
    scanf("%d",&tq);
    rr_sort(p,n);
    int clk=p[0].at;
    int flag=0;
    while(flag!=1){
        for(int i=0;i<n;i++){
            
        }
    }
}
