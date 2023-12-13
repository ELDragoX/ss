#include<stdio.h>
#include<stdlib.h>

struct process{
    int pid,at,bt,ct,tat,wt,flag;
}p[10];
struct process temp;
void sjf_sort(struct process p[10],int n)
{
    for(int i=0;i<n;i++){
        for(int j=0;j<n-i-1;j++){
            if(p[j].bt>p[j+1].bt){
                temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
        }
    }
    
};
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
    printf("Enter number of process:");
    scanf("%d",&n);

    for(int i=0;i<n;i++){
        p[i].pid=i+1;
        printf("Enter arrival time of process%d:",i+1);
        scanf("%d",&p[i].at);
        printf("Enter burst time of process%d:",i+1);
        scanf("%d",&p[i].bt);
        p[i].ct=0;p[i].wt=0;p[i].tat=0;p[i].flag=0;
    }
    sjf_sort(p,n);
    float totwt=0,tottat=0,avgwt=0,avgtat=0;
    int clk=0,flag=0;

    while(flag!=1){

        flag=1;
        int min_bt=1000;
        int min_idx=-1;

        for(int i=0;i<n;i++){
            
            if(p[i].at<=clk && p[i].flag==0 && p[i].bt<min_bt){
                min_bt=p[i].bt;
                min_idx=i;
                flag=0;
        
            }
            else if(p[i].flag==0){
                flag=0;
            }
        }

        if(min_idx==-1){
            clk++;

        }
        else{
            p[min_idx].ct=clk+p[min_idx].bt;
            p[min_idx].tat=p[min_idx].ct-p[min_idx].at;
            p[min_idx].wt=p[min_idx].tat-p[min_idx].bt;
            p[min_idx].flag=1;
            totwt+=p[min_idx].wt;
            tottat+=p[min_idx].tat;
            clk=p[min_idx].ct;

        }
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
