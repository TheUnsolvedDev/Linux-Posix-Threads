#define INTERRUPTS 4
#define ENABLE_REG 0
#define ACTIVE_REG 1
#define PENDING_REG 2

typedef int (*FUNC_ADDR)(int,int);		// Used to store the address of a Interrupt

typedef struct {
	int **IVTR; 		// IVTR table the holds->(enable register,active register, pendibg register, priority)
	FUNC_ADDR *IVT; 	// Holds the interrupt ID and ISR address
} Interrupt_Vector_Table;

typedef struct {
	int uid;
	int priority;
	FUNC_ADDR address;
} InterruptService;

typedef struct {
	InterruptService *stack; 
	int stack_type; // to differentiate betwn store_stack and process_stack
} StackFrame;

void SET_BIT(int **ivtr,int register_val,int interrupt_id);

void CLEAR_BIT(int **ivtr,int register_val,int interrupt_id);

void free_ivt(Interrupt_Vector_Table *ivt);

void interrupt_handler(StackFrame *process_stack,StackFrame *store_stack,Interrupt_Vector_Table *ivt);

int process_call(FUNC_ADDR addr,int a,int b);

FUNC_ADDR *get_IVT(FUNC_ADDR *Ivt);

int **get_IVTR(int **Ivtr);

void freed(StackFrame *Sframe);

void interrupt_generate(StackFrame *process_stackFrame,StackFrame *store_stackFrame,int uid,int priority,FUNC_ADDR address);

void init_stackFrame(StackFrame *Sframe,int type);

void push(StackFrame *Sframe,InterruptService *interrupt,int *count);

void print_stackFrame(StackFrame *Sframe);