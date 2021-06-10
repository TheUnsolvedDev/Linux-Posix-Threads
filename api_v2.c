#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interruptStruct.h"
#define  INTERRUPTS 4

int process_count = 0;
int store_count = 0;

void SET_BIT(int **ivtr,int register_type,int interrupt_id){
	ivtr[register_type][interrupt_id] = 1;
}

void CLEAR_BIT(int **ivtr,int register_val,int interrupt_id){
	ivtr[register_val][interrupt_id] = 0;
}

int process_call(FUNC_ADDR addr,int a,int b){
	return addr(a,b);
}

int add(int a,int b){
	return a+b;
}

int multi(int a,int b){
	return a*b;
}

int sub(int a,int b){
	return a-b;
}

int power(int b,int ex){
	int r = 1;
	for(int i=0;i<ex;i++){
		r *= b;
	}
	return r;
}

FUNC_ADDR *get_IVT(FUNC_ADDR *ivt){
	ivt = (FUNC_ADDR *) malloc(sizeof(FUNC_ADDR *) * INTERRUPTS);
	ivt[0] = add;
	ivt[1] = multi;
	ivt[2] = sub;
	ivt[3] = power;
	return ivt;
}

int **get_IVTR(int **ivtr){
	ivtr = (int **) malloc(sizeof(int*)*4);
	for(int i=0;i<4;i++)
	{
		ivtr[i] = (int *)malloc(sizeof(int)*INTERRUPTS);
		memset(*(ivtr+i),0,INTERRUPTS);
	}
	for(int i=1;i<=INTERRUPTS;i++)
	{
		ivtr[3][i-1] = (power(-1,i))*(2*i)+5*i;
	}
	return ivtr;
}

InterruptService pop(StackFrame *main_stack,int *count)
{	
	InterruptService itr = main_stack->stack[*count-1];
	main_stack->stack = (InterruptService *) realloc(main_stack->stack,sizeof(InterruptService)*(*count));
	*count -= 1;
	return itr;
}

void free_ivt(Interrupt_Vector_Table *ivt){
	free(ivt->IVT);	
	for(int i=0;i<4;i++)
	{
		free(ivt->IVTR[i]);
		ivt->IVTR[i] = NULL;
	}
	free(ivt->IVTR);
	ivt->IVT = NULL;
	free(ivt);

}

void freed(StackFrame *main_stack){
	free(main_stack->stack);
	main_stack->stack = NULL;
}

void init_stackFrame(StackFrame *main_stack,int type){
	main_stack->stack = (InterruptService *) malloc(sizeof(InterruptService));
	main_stack->stack_type = type;
}

void push(StackFrame *main_stack,InterruptService *interrupt,int *count){
	if(*count!=0)
	{
		main_stack->stack = (InterruptService *) realloc(main_stack->stack,sizeof(InterruptService)*(*count+1));
	}
	main_stack->stack[*count] = *interrupt;
	*count += 1;
}

void print_stackFrame(StackFrame *stackframe){	
	int count;
	if(stackframe->stack_type==0)
	{
		count = store_count;
	}
	else{
		count = process_count;
	}	
	for(int i=0;i<count;i++)
	{
		printf("\nInterrupt id : %d\n",stackframe->stack[i].uid);
		printf("Interrupt priority : %d\n",stackframe->stack[i].priority);
		printf("Interrupt address : %p\n",stackframe->stack[i].address);
	}
	printf("-------------------------------\n\n");	
}

void interrupt_handler(StackFrame *process_stackFrame,StackFrame *store_stackFrame,Interrupt_Vector_Table *ivt){
	int output;
	InterruptService itr_s;
	while(process_count!=0)
	{
		if(store_count<=0)
		{
			output = ivt->IVT[process_stackFrame->stack->uid](10,20);
			printf("output : %d\n",output);
			printf("\nInterrupts handled successfully !!!\n\n");
			process_count = 0;
		}
		else{
			output = ivt->IVT[process_stackFrame->stack->uid](10,20);
			process_count = 0;
			itr_s = pop(store_stackFrame,&store_count);
			push(process_stackFrame,&itr_s,&process_count);
			printf("output : %d\n",output);
		}
	}
}

void interrupt_generate(StackFrame *process_stackFrame,StackFrame *store_stackFrame,int uid,int priority,FUNC_ADDR loc){	
	InterruptService *interrupt;
	interrupt = (InterruptService *)malloc(sizeof(InterruptService));

	interrupt->uid = uid;
	interrupt->priority = priority;
	interrupt->address = loc;
	if(process_count==0)
	{
		push(process_stackFrame,interrupt,&process_count);
	}
	else
	{
		if(process_stackFrame->stack[process_count-1].priority < interrupt->priority)
		{
			push(store_stackFrame,process_stackFrame->stack,&store_count);
			process_count = 0;
			push(process_stackFrame,interrupt,&process_count);
		}
	}
	free(interrupt);
	interrupt = NULL;
}