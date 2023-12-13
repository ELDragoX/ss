#include<stdio.h>
#include<stdlib.h>

struct process{
    int pid,at,bt,ct,wt,tat,prt,flag;
}p[10];

struct process temp;

void priority_sort(struct process p[10],int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n-i-1;j++){
            if(p[j].prt > p[j+1].prt){
                temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
        }
    }
}
void disp_sort(struct process p[10],int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n-i-1;j++){
            if(p[j].pid > p[j+1].pid){
                temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
        }
    }
}

void main(){
    int n;
    printf("Enter number of process:");
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        p[i].pid=i+1;
        printf("Enter arrival time of Process%d:",i+1);
        scanf("%d",&p[i].at);
        printf("Enter burst time of Process%d:",i+1);
        scanf("%d",&p[i].bt);
        printf("Enter priority of Process%d:",i+1);
        scanf("%d",&p[i].prt);
        p[i].ct=0,p[i].wt=0,p[i].tat=0,p[i].flag=0;
    }

    priority_sort(p,n);
    float tottat=0,totwt=0,avgtat=0,avgwt=0;
    int clk=0,flag=0;

    while(flag!=1){
            flag=1;
            int prt=1000;
            int prt_idx=-1;

            for(int i=0;i<n;i++){
                if(p[i].at<=clk && p[i].flag==0 && p[i].prt<prt){
                    prt=p[i].prt;
                    prt_idx=i;
                    flag=0;
                }
                else if(p[i].flag==0){
                    flag=0;
                }
            }

            if(prt_idx==-1){
                clk++;
            }
            else{
                p[prt_idx].ct=clk+p[prt_idx].bt;
                p[prt_idx].tat=p[prt_idx].ct-p[prt_idx].at;
                p[prt_idx].wt=p[prt_idx].tat-p[prt_idx].bt;
                p[prt_idx].flag=1;
                clk=p[prt_idx].ct;
                tottat+=p[prt_idx].tat;
                totwt+=p[prt_idx].wt;
                
            }
    }
    
    disp_sort(p,n);
    
    printf("\nProcess\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\tCompletion Time\n");
    
    for(int k=0;k<n;k++){
        printf("\n%d\t%d\t%d\t%d\t%d\t%d\t%d\n",p[k].pid,p[k].at,p[k].bt,p[k].prt,p[k].wt,p[k].tat,p[k].ct);
    }


    printf("\nTotal Turn Around Time:%f\n",tottat);
    printf("\nTotal Waiting Time:%f\n",totwt);
    avgtat=(float)tottat/n;
    avgwt=(float)totwt/n;
    printf("\nAverage Turn Around Time:%f\n",avgtat);
    printf("\nAverage Waiting Time:%f\n",avgwt);
}
