#include <stdio.h>
#include <stdlib.h>
#include "interruptStruct.h"

int main()
{

	Interrupt_Vector_Table *IVT_TABLE;
	IVT_TABLE = (Interrupt_Vector_Table *) malloc(sizeof(Interrupt_Vector_Table));
	IVT_TABLE->IVT = get_IVT(IVT_TABLE->IVT);
	IVT_TABLE->IVTR = get_IVTR(IVT_TABLE->IVTR);

	SET_BIT(IVT_TABLE->IVTR,ENABLE_REG,2);
	SET_BIT(IVT_TABLE->IVTR,ENABLE_REG,0);
	SET_BIT(IVT_TABLE->IVTR,ENABLE_REG,1);
	SET_BIT(IVT_TABLE->IVTR,ENABLE_REG,3);

	SET_BIT(IVT_TABLE->IVTR,PENDING_REG,2);
	SET_BIT(IVT_TABLE->IVTR,PENDING_REG,0);
	SET_BIT(IVT_TABLE->IVTR,PENDING_REG,1);
	SET_BIT(IVT_TABLE->IVTR,PENDING_REG,3);


	StackFrame process_stackFrame,store_stackFrame;
	init_stackFrame(&process_stackFrame,1);
	init_stackFrame(&store_stackFrame,0);

	for(int i=0;i<INTERRUPTS;i++)
	{
		printf("%p ",IVT_TABLE->IVT[i]);
	}
	printf("\n\n");

	interrupt_generate(&process_stackFrame,&store_stackFrame,0,IVT_TABLE->IVTR[3][0],IVT_TABLE->IVT[0]);
	interrupt_generate(&process_stackFrame,&store_stackFrame,2,IVT_TABLE->IVTR[3][2],IVT_TABLE->IVT[2]);
	interrupt_generate(&process_stackFrame,&store_stackFrame,1,IVT_TABLE->IVTR[3][1],IVT_TABLE->IVT[1]);
	interrupt_generate(&process_stackFrame,&store_stackFrame,3,IVT_TABLE->IVTR[3][3],IVT_TABLE->IVT[3]);

	printf("Process stack: \n");
	print_stackFrame(&process_stackFrame);
	printf("Storage stack : \n");
	print_stackFrame(&store_stackFrame);

	interrupt_handler(&process_stackFrame,&store_stackFrame,IVT_TABLE);

	freed(&process_stackFrame);
	freed(&store_stackFrame);
	free_ivt(IVT_TABLE);

	return 0;
}