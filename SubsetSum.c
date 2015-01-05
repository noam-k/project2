/******************************************************************************
* FILE: SubsetSum.c
* DESCRIPTION:
* SubsetSum.c tests all the options to get a number from a given array
* AUTHOR: Alla
******************************************************************************/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS	16

//char *messages[NUM_THREADS];
int SUM_ARR[NUM_THREADS]={0};
int NUM_ARR[]={1,2,-3,6};
//int NUM_ARR[]={1,2};


struct thread_data
{
   int	thread_id;
   //int  sum;
};

struct thread_data thread_data_array[NUM_THREADS];

void *SubsetSum(void *threadarg)
{
   int taskid, sum,i,sum2=0,taskid2;
   char *hello_msg;
   struct thread_data *my_data;
   int binaryNumber[2]={0};

   sleep(1);
   my_data = (struct thread_data *) threadarg;
   taskid = my_data->thread_id;
   taskid2=taskid;
   //sum = my_data->sum;


   for(i=0; i<4; i++){
         binaryNumber[i]= taskid % 2;
         taskid = taskid / 2;
    }


  for(i=0; i<4; i++){
	sum2+=binaryNumber[i]*NUM_ARR[i];
  }
  SUM_ARR[taskid2]=sum2;
  //my_data->sum = sum2;
  printf("Thread %d: with  Sum=%d\n", taskid2, sum2);
 
   pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
pthread_t threads[NUM_THREADS];
int *taskids[NUM_THREADS];
int rc, t, sum;

sum=0;

for(t=0;t<NUM_THREADS;t++) {
  //sum = sum + t;
  thread_data_array[t].thread_id = t;
  //thread_data_array[t].sum = sum;
  printf("Creating thread %d\n", t);
  rc = pthread_create(&threads[t], NULL, SubsetSum, (void *) 
       &thread_data_array[t]);
  if (rc) {
    printf("ERROR; return code from pthread_create() is %d\n", rc);
    exit(-1);
    }
  }

   /* Free attribute and wait for the other threads */
   for(t=0; t<NUM_THREADS; t++) {
      rc = pthread_join(threads[t], NULL);
      if (rc) {
         printf("ERROR; return code from pthread_join() is %d\n", rc);
         exit(-1);
         }
      printf("Main: completed join with thread %d \n",t);
      }


printf("SUM_ARR:");
for(t=0; t<NUM_THREADS; t++){
   printf(" %d ",SUM_ARR[t]);
}
printf("\n");



for(t=0; t<NUM_THREADS; t++){
	if (SUM_ARR[t]==3) printf("Number 3 was found!\n");
}


pthread_exit(NULL);


}

