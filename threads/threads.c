#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *myturn(void *arg)
{
	for (int i = 0; i >= 0; i++)
	{
		printf("My turn %d!\n",i);
	}
	return NULL;
}

void yourturn()
{
	for (int i = 0; i >= 0; i++)
	{
		printf("Your turn %d!\n",i);
	}
}

void *elseturn(void *arg)
{
	for (int i = 0;i >= 0;i++)
	{
		printf("Hi there!\n");
	}
	return NULL;
}

int main()
{
	pthread_t new_thread1,new_thread2;
	pthread_create(&new_thread1, NULL,myturn, NULL);	
	pthread_create(&new_thread2,NULL,elseturn,NULL);
	yourturn();
	// pthread_join(new_thread1, NULL);
	return 0;
}