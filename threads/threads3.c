#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define BIG 1000000000UL
int counter = 0;
pthread_mutex_t lock ;

void *count_to_big(void *arg)
{
	for(int i = 0; i < BIG;i++)
	{
		pthread_mutex_lock(&lock);
		counter ++;
		pthread_mutex_unlock(&lock);
	}
	return NULL;
}

int main(void)
{
	pthread_t thr;
	pthread_create(&thr, NULL,count_to_big,NULL);
	// count_to_big(NULL);
	count_to_big(NULL);
	pthread_join(thr,NULL);
	printf("DONE Count = %u\n",counter);

	return 0;
}




