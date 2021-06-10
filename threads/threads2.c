#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *myturn(void *arg)
{
	int *iptr = (int *)malloc(sizeof(int));
	*iptr = 5;
	for (int i = 0; i < 8; i++)
	{
		sleep(1);
		printf("My turn %d %d!\n",i,*iptr);
		(*iptr) += 1;
	}
	return iptr;
}

void yourturn(void)
{
	for (int i = 0; i < 3; i++)
	{
		sleep(2);
		printf("Your turn %d!\n",i);
	}
}

int main()
{
	pthread_t new_thread1,new_thread2;
	int *result;

	pthread_create(&new_thread1, NULL,myturn, NULL);	
	yourturn();
	pthread_join(new_thread1,(void *)&result);
	printf("Threads Done: \n");
	printf("Num :%d\n",*result);
	return 0;
}