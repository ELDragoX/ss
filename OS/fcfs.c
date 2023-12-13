#include<stdlib.h>
#include<stdio.h>

struct process
{
    int pid,at,bt,ct,wt,tat;
}p[10];


struct process temp;
void fcfs_sort(struct process p[10],int n){
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
void main(){
    int n;
    printf("Enter number of processes:");
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        p[i].pid=i+1;
        printf("Enter arrival time of Process%d:",i+1);
        scanf("%d",&p[i].at);
        printf("Enter burst time of Process%d:",i+1);
        scanf("%d",&p[i].bt);
        p[i].ct=0;p[i].wt=0;p[i].tat=0;
    }
    fcfs_sort(p,n);
    float totwt=0;
    float tottat=0;
    float avgtat=0;
    float avgwt=0;
    int clk=0;
    for(int j=0;j<n;j++){
        if(clk<p[j].at){
            clk=p[j].at;
        }
        p[j].ct=clk+p[j].bt;
        p[j].tat=p[j].ct-p[j].at;
        p[j].wt=p[j].tat-p[j].bt;
        clk=p[j].ct;
        totwt+=p[j].wt;
        tottat+=p[j].tat;

    }
    disp_sort(p,n);
    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\tCompletion Time\n");
    for(int k=0;k<n;k++){
        printf("\n%d\t%d\t%d\t%d\t%d\t%d\n",p[k].pid,p[k].at,p[k].bt,p[k].wt,p[k].tat,p[k].ct);
    }
    printf("\nTotal Turn Around Time:%f\n",tottat);
    printf("\nTotal Waiting Time:%f\n",totwt);
    avgtat=(float)tottat/n;
    avgwt=(float)totwt/n;
    printf("\nAverage Turn Around Time:%f\n",avgtat);
    printf("\nAverage Waiting Time:%f\n",avgwt);

    
}