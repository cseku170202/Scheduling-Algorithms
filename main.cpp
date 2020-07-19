#include<bits/stdc++.h>
using namespace std;
#define MAX_PROCESS 1000

///For FCFS
struct process_FCFS
{
    int pid;
    int arrival_time;
    int burst_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
} ;
typedef struct process_FCFS Process1;

void print_table_FCFS(Process1 p[], int n,int arr[],int num);
void print_gantt_chart_FCFS(Process1 p[], int n,int arr[],int num);
///Done FCFS

///For SJF
typedef struct
{
    int pid;
    int burst_time;
    int arrival_time;
    int waiting_time;
    int turnaround_time;
}Process2;

void print_gantt_chart_SJF(Process2 p[], int n,int arr[],int num);
void print_table_SJF(Process2 p[],int n, int arr[],int num);
///Done SJF

///priority scheduling
struct priority_scheduling
{
    int pid;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int priority;
};
typedef struct priority_scheduling Process3;

void finding(Process3 p[],int n,int total_time,int arr[],int num);
void display(Process3 p[],int n,int arr[],int num);
void print_gantt_chart_Priority(Process3 p[], int n ,int arr[],int num);

void print_gantt_chart_Priority_checkzero(Process3 p[], int n,int arr[],int num);
void print_table_Priority_checkzero(Process3 p[],int n, int arr[],int num);
///Priority Scheduling done

///For ROUND ROBIN
typedef struct
{
    int pid;
    int burst_time;
    int remaining_burst_time;
    int waiting_time;
    int turnaround_time;
}Process4;

void print_gantt_chart_RR(Process4 p[], int n,int arr[],int num,int gc[],int l,int prid[],int pi);
void print_table_RR(Process4 p[],int n, int arr[],int num);
///Done ROUND ROBIN

int main()
{
    int option;
    puts("==============================================================");
	puts("|Options: 1:FCFS | 2:SJF | 3:Priority | 4:Round Robin | 5:Exit|");
	puts("==============================================================\n");
	cout<<"Choose Option=>";
	cin>>option;
	puts("");
	switch(option)
	{
        case 1:
        {
                Process1 p[MAX_PROCESS];
                int i, j, n,temp;
                int arr[10]={1,2,3,4,5,6,7,8,.9,10};
                int num=10;
                int sum_waiting_time = 0, sum_turnaround_time = 0;
                printf("Enter total number of process: ");
                scanf("%d", &n);
                printf("\n");
                printf("Enter burst time and arrival time for each process:\n");
                printf("\n");
                for(i=0; i<n; i++)
                {
                     p[i].pid = i+1;
                     printf("For P%d Process  ", i+1);
                     printf("\nBurst Time  :");
                     scanf("%d", &p[i].burst_time);
                     printf("Arrival Time:");
                     scanf("%d",&p[i].arrival_time);
                     p[i].waiting_time =  0;
                     p[i].turnaround_time = 0;
                     p[i].completion_time = 0;
                     printf("\n");
                }

                for(i=0;i<n;i++)
                {
                    for(j=0;j<n;j++)
                    {
                         if(p[i].arrival_time < p[j].arrival_time)
                         {
                             temp = arr[j];
                             arr[j]=arr[i];
                             arr[i]=temp;

                             temp = p[j].arrival_time;
                             p[j].arrival_time = p[i].arrival_time;
                             p[i].arrival_time = temp;

                             temp = p[j].burst_time;
                             p[j].burst_time = p[i].burst_time;
                             p[i].burst_time = temp;
                         }
                    }
                }

                ///calculate the turnaround time
                p[0].turnaround_time = p[0].burst_time;
                for(i=1;i<n;i++)
                {
                    for(j=0;j<=i;j++)
                    {
                         p[i].completion_time = p[i].completion_time + p[j].burst_time;
                    }
                    p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
                }

                ///calculate the waiting time
                for(i=0;i<n;i++)
                {
                     p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
                }

                /// calculate sum of waiting time and sum of turnaround time
                for(i=0; i<n; i++)
                {
                    sum_waiting_time = sum_waiting_time + p[i].waiting_time;
                    sum_turnaround_time = sum_turnaround_time + p[i].turnaround_time;
                }

                puts("");
                printf("The Result Table for FCFS:");
                puts("");
                print_table_FCFS(p,n,arr,num);
                puts("");

                printf("Total Waiting Time      : %2d\n", sum_waiting_time);
                printf("Average Waiting Time    : %2.2lf\n", (double)sum_waiting_time / (double) n);
                printf("Total Turnaround Time   : %2d\n", sum_turnaround_time);
                printf("Average Turnaround Time : %2.2lf\n", (double)sum_turnaround_time / (double) n);

                puts("");
                puts("GANTT CHART:");
                print_gantt_chart_FCFS(p,n,arr,num);
                puts("");
		}
 	    break;
	    case 2:
		{
		    Process2 p[MAX_PROCESS];
            int n, i, j,temp;
            int waiting_time_sum=0,turnaround_time_sum=0;
            int arr[10]={1,2,3,4,5,6,7,8,9,10};
            int num=10;
            double avg_waiting_time,avg_turnaround_time;
            int bt,ta=0,sum=0,k=1,min;
            printf("Enter total process: ");
            scanf("%d", &n);
            printf("Enter burst time for each process:\n");
            for(i=0; i<n; i++)
            {
                printf("P[%d]: ", i+1);
                scanf("%d", &p[i].burst_time);
                p[i].pid = i+1;
                p[i].turnaround_time = 0;
            }
            printf("Enter arrival time for each process:\n");
            for(i=0; i<n; i++)
            {
                printf("P[%d]: ", i+1);
                scanf("%d", &p[i].arrival_time);
                p[i].pid = i+1;
                p[i].waiting_time = 0;
            }
            /// sorting according to arrival time
            for(i=0;i<n;i++)
            {
                for(j=0;j<n;j++)
                {
                     if(p[i].arrival_time < p[j].arrival_time)
                     {
                         temp = arr[j];
                         arr[j]=arr[i];
                         arr[i]=temp;

                         temp = p[j].arrival_time;
                         p[j].arrival_time = p[i].arrival_time;
                         p[i].arrival_time = temp;

                         temp = p[j].burst_time;
                         p[j].burst_time = p[i].burst_time;
                         p[i].burst_time = temp;
                      }
                 }
             }
             ///Sorting the p[] araay by considering both arrival time & burst time
             for(j=0;j<n;j++)
             {
                 bt = bt + p[j].burst_time;
                 min = p[k].burst_time;
                 for(i=k;i<n;i++)
                 {
                     if(bt>=p[i].arrival_time && p[i].burst_time<min)
                     {
                         temp = arr[k];
                         arr[k] = arr[i];
                         arr[i] = temp;

                         temp = p[k].arrival_time;
                         p[k].arrival_time = p[i].arrival_time;
                         p[i].arrival_time = temp;

                         temp = p[k].burst_time;
                         p[k].burst_time = p[i].burst_time;
                         p[i].burst_time = temp;
                      }
                  }
                k++;
              }
              ///calcutate waiting time
              p[0].waiting_time = 0;
              for(i=1;i<n;i++)
              {
                  sum = sum + p[i-1].burst_time;
                  p[i].waiting_time = sum - p[i].arrival_time;
                  waiting_time_sum = waiting_time_sum + p[i].waiting_time;
              }
              avg_waiting_time =(float)(waiting_time_sum/n);
              /// calculate turnaround time
              for(i=0;i<n;i++)
              {
                  ta = ta + p[i].burst_time;
                  p[i].turnaround_time = ta - p[i].arrival_time;
                  turnaround_time_sum = turnaround_time_sum + p[i].turnaround_time;
              }
              avg_turnaround_time = (float)(turnaround_time_sum/n);
              ///print table
              puts("");
              puts("THE RESULT TABLE FOR SJF:");
              print_table_SJF(p,n,arr,num);
              puts("");

              puts("");
              printf("Total Waiting Time      : %2d\n",waiting_time_sum);
              printf("Average Waiting Time    : %0.2lf\n",avg_waiting_time);
              printf("Total Turnaround Time   : %2d\n",turnaround_time_sum);
              printf("Average Turnaround Time : %0.2lf\n",avg_turnaround_time);
              puts("");

              printf("Gantt Chart:\n");
              print_gantt_chart_SJF(p, n ,arr ,num);
              puts("");
		}
        break;
        case 3:
        {
             Process3 p[MAX_PROCESS];
             Process3 temp;
             int n, i, j,pos,total_time=0,check=0,temp1;
             int arr[10]={0};
             int num=10;
             printf("Enter Total Number of Processes:");
             scanf("%d",&n);
             printf("\nEnter the Arrival Time , Burst Time and Priority for each process\n");
             for(i=0;i<n;i++)
             {
                 printf("\nFor P%d Process\n",i+1);
                 printf("Arrival Time:");
                 scanf("%d",&p[i].arrival_time);
                 printf("Burst Time  :");
                 scanf("%d",&p[i].burst_time);
                 printf("Priority    :");
                 scanf("%d",&p[i].priority);
                 arr[i]=i+1;
                 p[i].pid=i+1;
             }
             for(i=0;i<n;i++)
             {
                  if(p[i].arrival_time==0)
                  {
                      continue;
                  }
                  if(p[i].arrival_time!=0)
                  {
                      check++;
                      break;
                  }
             }
             if(check==0)
             {
                  int waiting_time_sum=0,turnaround_time_sum=0;
                  double avg_waiting_time,avg_turnaround_time;
                  ///sorting burst time, priority and process number in ascending order using selection sort
                  for(i=0;i<n;i++)
                  {
                      pos=i;
                      for(j=i+1;j<n;j++)
                      {
                          if(p[j].priority < p[pos].priority)
                          pos=j;
                      }

                      temp1 = p[i].priority;
                      p[i].priority = p[pos].priority;
                      p[pos].priority = temp1;

                      temp1 = p[i].burst_time;
                      p[i].burst_time = p[pos].burst_time;
                      p[pos].burst_time = temp1;

                      temp1 = arr[i];
                      arr[i] = arr[pos];
                      arr[pos] = temp1;
                  }

                  p[0].waiting_time = 0;	///waiting time for first process is zero
                  ///calculate waiting time
                  for(i=1;i<n;i++)
                  {
                      p[i].waiting_time = 0;
                      for(j=0;j<i;j++)
                      {
                          p[i].waiting_time = p[i].waiting_time + p[j].burst_time;
                      }

                      waiting_time_sum = waiting_time_sum + p[i].waiting_time;
                  }
                  avg_waiting_time = (double)waiting_time_sum/n;

                  ///calculate turnaround time
                  for(i=0;i<n;i++)
                  {
                      p[i].turnaround_time = p[i].burst_time + p[i].waiting_time;
                      turnaround_time_sum = turnaround_time_sum + p[i].turnaround_time;
                  }

                  avg_turnaround_time = (double)turnaround_time_sum/n;

                  ///print table
                  puts("");
                  puts("");
                  puts("THE RESULT TABLE FOR PRIORITY SCHEDULING:");
                  print_table_Priority_checkzero(p,n,arr,num);
                  puts("");

                  puts("");
                  printf("Total Waiting Time      : %2d\n",waiting_time_sum);
                  printf("Average Waiting Time    : %0.2lf\n",avg_waiting_time);
                  printf("Total Turnaround Time   : %2d\n",turnaround_time_sum);
                  printf("Average Turnaround Time : %0.2lf\n",avg_turnaround_time);
                  puts("");

                  printf("Gantt Chart:\n");
                  print_gantt_chart_Priority_checkzero(p, n ,arr ,num);
                  puts("");
                  goto ext;
              }
              if(check>0)
              {
                  ///sorting
                  for(i=0;i<n;i++)
                  {
                      for(j=i;j>=1;j--)
                      {
                          if(p[j].arrival_time < p[j-1].arrival_time)
                          {
                              temp = p[j-1];
                              p[j-1] = p[j];
                              p[j] = temp;
                          }
                      }
                  }
                  ///finding the total time
                  total_time += p[0].arrival_time + p[0].burst_time;
                  for(i=1;i<n;i++)
                  {
                      if(p[i].arrival_time > total_time)
                      total_time= p[i].arrival_time;//coz if the next process arives after a while after the b4 process has //complted
                      total_time+= p[i].burst_time;
                  }
                  ///finding the ct
                  finding(p,n,total_time,arr,num);
              }
        }
        break;
        case 4:
	    {
	        Process4 p[MAX_PROCESS];
            int n, i, j,temp,quantam,l=0,pi=0,k;
            int waiting_time_sum=0,turnaround_time_sum=0;
            int arr[10]={1,2,3,4,5,6,7,8,9,10};
            int gc[1000]={0};
            int prid[1000]={0};
            int num=10;
            double avg_waiting_time,avg_turnaround_time;
            printf("Enter total process: ");
            scanf("%d", &n);
            printf("Enter burst time for each process:\n");
            for(i=0; i<n; i++)
            {
                printf("P[%d]: ", i+1);
                scanf("%d", &p[i].burst_time);
                p[i].pid = i+1;
                p[i].turnaround_time = 0;
                p[i].waiting_time = 0;
            }
            puts("");
            printf("Enter The Time quantam:");
            scanf("%d",&quantam);
            ///waiting time calculation
            for (int i = 0 ; i < n ; i++)
            {
                p[i].remaining_burst_time =  p[i].burst_time;
            }
            int t = 0;
            while (1)
            {
                bool done = true;
                for (int i = 0 ; i < n; i++)
                {
                    if (p[i].remaining_burst_time > 0)
                    {
                        done = false; /// There is a pending process
                        if (p[i].remaining_burst_time > quantam)
                        {
                            t = t + quantam;
                            gc[l] = t;
                            l++;

                            prid[pi] = i;
                            pi++;

                            p[i].remaining_burst_time = p[i].remaining_burst_time - quantam;
                         }

                         else
                         {
                             t = t + p[i].remaining_burst_time;
                             gc[l] = t;
                             l++;

                             prid[pi] = i;
                             pi++;

                             p[i].waiting_time = t - p[i].burst_time;

                             p[i].remaining_burst_time = 0;
                         }
                    }
               }
               if (done == true)
               break;
            }/// waiting time calculation done

            ///calculate the turnaround time
            for (int i = 0; i < n ; i++)
            {
                p[i].turnaround_time = p[i].burst_time + p[i].waiting_time;
            }

            /// Calculate total waiting time and total turnaround time
            for (int i=0; i<n; i++)
            {
                 waiting_time_sum = waiting_time_sum + p[i].waiting_time;
                 turnaround_time_sum = turnaround_time_sum + p[i].turnaround_time;
            }
            puts("");
            printf("The Result Table for RR:");
            puts(""); /// print table
            print_table_RR(p,n,arr,num);
            puts("");
            printf("Total Waiting Time      : %2d\n",waiting_time_sum);
            printf("Average Waiting Time    : %2.2lf\n", (double)waiting_time_sum / (double) n);
            printf("Total Turnaround Time   : %2d\n", turnaround_time_sum);
            printf("Average Turnaround Time : %2.2lf\n", (double)turnaround_time_sum / (double) n);
            puts("");

            printf("Gantt Chart:\n");
            print_gantt_chart_RR(p, n ,arr ,num , gc , l , prid , pi);
            puts("");
            puts("");
        }
	    break;
        case 5:
        {
            goto ext;
        }
        default:
	    {
            printf("Your Have Entered an Invalid Number\n");
	    }
	}
	ext:
    return 0;
}

void print_table_FCFS(Process1 p[], int n,int arr[],int num)
{
    int i;
    puts("+-----+---------------+------------+--------------+-----------------+");
    puts("| PID |  Arrival Time | Burst Time | Waiting Time | Turnaround Time |" );
    puts("+-----+---------------+------------+--------------+-----------------+");
    for(i=0;i<n;i++)
    {
        printf("| p%d  |     %2d        |     %2d     |      %2d      |       %2d        |\n"
               ,arr[i] , p[i].arrival_time , p[i].burst_time , p[i].waiting_time , p[i].turnaround_time);
        puts("+-----+---------------+------------+--------------+-----------------+");
    }
}

void print_gantt_chart_FCFS(Process1 p[], int n,int arr[],int num)
{
    int i, j,s=0;
    // print top bar
    printf(" ");
    for(i=0; i<n; i++)
    {
        for(j=0; j<p[i].burst_time; j++)
        {
            printf("--");
        }
        printf(" ");
    }
    printf("\n|");
    // printing process id in the middle
    for(i=0; i<n; i++)
    {
        for(j=0; j<p[i].burst_time - 1; j++)
        {
            printf(" ");
        }
        printf("P%d", arr[i]);
        for(j=0; j<p[i].burst_time - 1; j++)
        {
            printf(" ");
        }
        printf("|");
    }
    printf("\n ");
    // printing bottom bar
    for(i=0; i<n; i++)
    {
        for(j=0; j<p[i].burst_time; j++)
        {
            printf("--");
        }
        printf(" ");
    }
    printf("\n");
    // printing the time line
    printf("0");
    for(i=0; i<n; i++)
    {
        for(j=0; j<p[i].burst_time; j++)
        {
            printf("  ");
        }
        s = s + p[i].burst_time;
        if( s  > 9)
        {
            printf("\b"); /// if the number is greater than 9 then remove 1 space
        }
        printf("%d", s);

    }
    printf("\n");
}

void print_table_SJF(Process2 p[],int n , int arr[],int num)
{
    int i;
    puts("+-----+---------------+------------+--------------+-----------------+");
    puts("| PID |  Arrival Time | Burst Time | Waiting Time | Turnaround Time |" );
    puts("+-----+---------------+------------+--------------+-----------------+");
    for(i=0;i<n;i++)
    {
        printf("| p%d  |     %2d        |     %2d     |      %2d      |       %2d        |\n"
               ,arr[i] , p[i].arrival_time , p[i].burst_time , p[i].waiting_time , p[i].turnaround_time);
        puts("+-----+---------------+------------+--------------+-----------------+");
    }
}

void print_gantt_chart_SJF(Process2 p[], int n ,int arr[],int num)
{
    int i, j;
    int s=0;
    printf(" ");
    for(i=0; i<n; i++)
    {
        for(j=0; j<p[i].burst_time; j++)
        {
                printf("--");
        }
        printf(" ");
    }
    printf("\n|");
    /// middle position (Process ID)
    for(i=0; i<n; i++)
    {
        for(j=0; j<p[i].burst_time-1; j++)
        {
            printf(" ");
        }
        printf("p%d", arr[i]);
        for(j=0; j<p[i].burst_time-1; j++)
        {
             printf(" ");
        }
        printf("|");
    }
    printf("\n ");
    // bottom bar
    for(i=0; i<n; i++)
    {
        for(j=0; j<p[i].burst_time; j++)
        {
            printf("--");
        }
        printf(" ");
    }
    printf("\n");
    /// printing the time line
    printf("0");
    for(i=0; i<n; i++)
    {
        for(j=0; j<p[i].burst_time; j++)
        {
            printf("  ");
        }
        s = s + p[i].burst_time;
        if(s > 9)
        {
            printf("\b"); /// if the number is greater than 9 then remove 1 space
        }
        printf("%d", s);
    }
}

void finding(Process3 p[],int n,int total_time,int arr[],int num)
{
       int i,j;
       int time=0,x,c=0;
       while(time<total_time)
       {
          j=0;
          for(i=0;i<n;i++)
          {
              if(p[i].arrival_time<=time)
              {
                  j=i+1;
              }///storing the list of processes that have arrived
          }
          if(j>0)
          {
              int x=0,min_pr = p[0].priority;
              for(i=1;i<j;i++)
              {
                   if(min_pr > p[i].priority)
                   {
                       x = i;
                       min_pr = p[i].priority;
                   }
                   else if(min_pr==p[i].priority)
                   {
                       if(p[x].arrival_time > p[i].arrival_time)
                       {
                           x = i;
                           min_pr = p[i].priority;
                       }
                       else if( p[x].arrival_time== p[i].arrival_time)
                       {
                           if(p[x].burst_time > p[i].burst_time)
                           {
                               x = i;
                               min_pr = p[i].priority;
                           }
                       }
                   }
              }
            time+= p[x].burst_time;///x is the process with min service time
            p[x].completion_time = time;
            p[x].priority += 1000;///so that it not selected again
            p[x].arrival_time += 1000;

         }
         else
         {
             time++;
         }
     }
     for(i=0;i<n;i++)
     {
          p[i].priority -= 1000;
          p[i].arrival_time -=1000;
     }//so that its values return ack to narmal
      display(p,n,arr,num);
}

void display(Process3 p[],int n,int arr[],int num)
{
    int i,j;
    int waiting_time_sum=0,turnaround_time_sum=0;
    double avg_waiting_time,avg_turnaround_time;

    for(i=0;i<n;i++)
    {
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
    }
    for(i=0;i<n;i++)
    {
       turnaround_time_sum += p[i].turnaround_time;
       waiting_time_sum += p[i].waiting_time;
    }
    avg_turnaround_time = (double)turnaround_time_sum/n;
    avg_waiting_time = (double)waiting_time_sum/n;

    puts("");
    puts("");
    puts("+-----+---------------+--------------+------------+--------------+-----------------+");
    puts("| PID |  priority     | Arrival Time | Burst Time | Waiting Time | Turnaround Time |" );
    puts("+-----+---------------+--------------+------------+--------------+-----------------+");

    for(i=0;i<n;i++)
    {
        printf("| p%d  |     %2d        |      %2d      |     %2d     |      %2d      |       %2d        |\n"
               ,p[i].pid,p[i].priority ,p[i].arrival_time, p[i].burst_time , p[i].waiting_time , p[i].turnaround_time);
         puts("+-----+---------------+--------------+------------+--------------+-----------------+");

    }

    puts("");
    printf("Total Waiting Time      : %2d\n",waiting_time_sum);
    printf("Average Waiting Time    : %0.2lf\n",avg_waiting_time);
    printf("Total Turnaround Time   : %2d\n",turnaround_time_sum);
    printf("Average Turnaround Time : %0.2lf\n",avg_turnaround_time);
    puts("");

    puts("");
    printf("Gantt Chart:\n");
    print_gantt_chart_Priority(p, n ,arr ,num);
    puts("");
}

void print_gantt_chart_Priority(Process3 p[], int n ,int arr[],int num)
{
    int i, j;
    int s=0;
    ///the top bar
    printf(" ");
    for(i=0; i<n; i++)
    {
        for(j=0; j<p[i].burst_time; j++)
        {
                printf("--");
        }
        printf(" ");
    }
    printf("\n|");
    /// middle position (Process ID)
    for(i=0; i<n; i++)
    {
        for(j=0; j<p[i].burst_time-1; j++)
        {
            printf(" ");
        }
        printf("p%d", p[i].pid);
        for(j=0; j<p[i].burst_time-1; j++)
        {
             printf(" ");
        }
        printf("|");
    }
    printf("\n ");
    /// bottom bar
    for(i=0; i<n; i++)
    {
        for(j=0; j<p[i].burst_time; j++)
        {
            printf("--");
        }
        printf(" ");
    }
    printf("\n");
    /// printing the time line
    printf("0");
    for(i=0; i<n; i++)
    {
        for(j=0; j<p[i].burst_time; j++)
        {
            printf("  ");
        }
        s = s + p[i].burst_time;
        if(s > 9)
        {
            printf("\b"); /// if the number is greater than 9 then remove 1 space
        }
        printf("%d", s);
    }
}

void print_table_Priority_checkzero(Process3 p[],int n , int arr[],int num)
{
    int i;
    puts("");
    puts("+-----+---------------+--------------+------------+--------------+-----------------+");
    puts("| PID |  priority     | Arrival Time | Burst Time | Waiting Time | Turnaround Time |" );
    puts("+-----+---------------+--------------+------------+--------------+-----------------+");

    for(i=0;i<n;i++)
    {
        printf("| p%d  |     %2d        |      %2d      |     %2d     |      %2d      |       %2d        |\n"
               ,arr[i],p[i].priority ,p[i].arrival_time, p[i].burst_time , p[i].waiting_time , p[i].turnaround_time);
         puts("+-----+---------------+--------------+------------+--------------+-----------------+");

    }
}

void print_gantt_chart_Priority_checkzero(Process3 p[], int n ,int arr[],int num)
{
    int i, j;
    int s=0;
    ///the top bar
    printf(" ");
    for(i=0; i<n; i++)
    {
        for(j=0; j<p[i].burst_time; j++)
        {
                printf("--");
        }
        printf(" ");
    }
    printf("\n|");
    /// middle position (Process ID)
    for(i=0; i<n; i++)
    {
        for(j=0; j<p[i].burst_time-1; j++)
        {
            printf(" ");
        }
        printf("p%d", arr[i]);
        for(j=0; j<p[i].burst_time-1; j++)
        {
             printf(" ");
        }
        printf("|");
    }
    printf("\n ");
    // bottom bar
    for(i=0; i<n; i++)
    {
        for(j=0; j<p[i].burst_time; j++)
        {
            printf("--");
        }
        printf(" ");
    }
    printf("\n");
    /// printing the time line
    printf("0");
    for(i=0; i<n; i++)
    {
        for(j=0; j<p[i].burst_time; j++)
        {
            printf("  ");
        }
        s = s + p[i].burst_time;
        if(s > 9)
        {
            printf("\b"); /// if the number is greater than 9 then remove 1 space
        }
        printf("%d", s);
    }
}

void print_table_RR(Process4 p[],int n, int arr[],int num)
{
    int i;
    puts("+-----+------------+--------------+-----------------+");
    puts("| PID | Burst Time | Waiting Time | Turnaround Time |");
    puts("+-----+------------+--------------+-----------------+");
    for(i=0; i<n; i++)
    {
        printf("| p%d  |     %2d     |      %2d      |        %2d      |\n"
               , arr[i], p[i].burst_time, p[i].waiting_time, p[i].turnaround_time );
        puts("+-----+------------+--------------+-----------------+");
    }
}

void print_gantt_chart_RR(Process4 p[], int n ,int arr[],int num,int gc[],int l,int prid[],int pi)
{
    int i, j,k=0,m=0;
    int s=0;
    printf(" ");
    for(i=0; i<l; i++)
    {
        for(j=0; j<4; j++)
        {
                printf("--");
        }
        printf(" ");
    }
    printf("\n|");
    /// middle position (Process ID)
    for(i=0; i<l; i++)
    {
        for(j=0; j<2; j++)
        {
            printf(" ");
        }
        printf("p%d", prid[k]+1);
        k++;

        for(j=0; j<4; j++)
        {
             printf(" ");
        }
        printf("|");
    }
    printf("\n ");
    ///bottom bar
    for(i=0; i<l; i++)
    {
        for(j=0; j<4; j++)
        {
                printf("--");
        }
        printf(" ");
    }
    printf("\n");
    /// printing the time line
    printf("0");
    for(i=0; i<l; i++)
    {
        for(j=0; j<4; j++)
        {
            printf("  ");
        }
        s = gc[m];
        m++;
        if(s<9)
        {
            printf("%d", s);
        }
        else if(s > 9 && s<=99)
        {
            printf("\b");
            printf("%d", s);/// if the number is greater than 9 then remove 1 space
        }
        else if(s>99 && s<=999)
        {
            printf("\b\b");
            printf("%d", s);
        }
        else if(s>=1000 && s<=9999)
        {
            printf("\b\b\b");
            printf("%d", s);
        }
    }
}


