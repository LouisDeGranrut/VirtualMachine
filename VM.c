#include <stdio.h>

#define NUM_REGS 4

int registers[NUM_REGS];//set of 4 registers
int pcounter = 0;//Program Counter
int running = 1;//This is a boolean, the machine will stop if 0

//Instructions declaration
int instrNum = 0;
int reg1     = 0;
int reg2     = 0;
int reg3     = 0;
int immediate= 0;

//The Program:
//0x + InstructionNumber + Parameter in hex
int program[] = {//example of a for loop
				0x1201,//r2 = 1 -> for(int i = 1;
			  	0x1109,//r1 = 5 ->  i< 5; i++)
			  	0x3112,//r0 = r1-r2
			  	0x4400,//print r0
			  	0x7102,//jump to line 2 if r1>r2 
			  	0x0000};//halt

//Gets the content of the program at the line the program counter is pointing at
int fetch(){
    return program[pcounter++];    
}

//Decode a word
void decode( int instruction )
{
  instrNum  = (instruction & 0xF000) >> 12;
  reg1      = (instruction & 0xF00 ) >>  8;
  reg2      = (instruction & 0xF0  ) >>  4;
  reg3      = (instruction & 0xF   );
  immediate = (instruction & 0xFF  );
}

//Evaluate the last decoded instruction
void eval()
{
  switch( instrNum )
  {
    case 0:
      /* halt */
      printf("%d ",pcounter);
      printf( "halt\n" );
      running = 0;
      break;
    case 1:
      /* load reg+value*/
      printf("%d ",pcounter);
      printf( "load r%d #%d\n", reg1, immediate );
      registers[ reg1 ] = immediate;
      break;
    case 2:
      /* add */
      printf("%d ",pcounter);
      printf( "add  r%d = r%d + r%d\n", reg1, reg2, reg3 );
      registers[ reg1 ] = registers[ reg2 ] + registers[reg3 ];
      break;
    case 3:
      /* subtract */
      printf("%d ",pcounter);
      printf( "sub  r%d = r%d - r%d\n", reg1, reg2, reg3 );
      registers[ reg1 ] = registers[ reg2 ] - registers[reg3 ];
      break;
    case 4:
      /* print value in register */
      printf("%d ",pcounter);
      printf( "show r%d: ", immediate);
      printf("%d\n",registers[ immediate ]);
      break;
    case 5:
      /* resets program counter */
      printf("%d ",pcounter);
      printf( "Reset program counter: ");
      pcounter = 0;
      break;
    case 6:
      /* jump to set address*/
      printf("%d ",pcounter);
      printf( "jump to line %d: ", immediate);
      pcounter = immediate;
      break;
    case 7:
      /* jump to set address if register a > register b*/
      printf("%d ",pcounter);
      printf( "cjump  r%d > r%d line %d\n", reg1, reg2, immediate );
      if(registers[ reg1 ] > registers[ reg2 ]){
	  	pcounter = immediate;	
	  }
      break;
    case 8:
      /* jump to set address if register a < register b*/
      printf("%d ",pcounter);
      printf( "cjump  r%d < r%d line %d\n", reg1, reg2, immediate );
      if(registers[ reg1 ] < registers[ reg2 ]){
	  	pcounter = immediate;	
	  }
      break;
    default:
    	printf("%d ",pcounter);
    	printf("Error in line\n");
    	break;
  }
}

/* display all registers as 4-digit hexadecimal words */
void showMemory()
{
  int i;
  printf( "Registers = " );
  for( i=0; i<NUM_REGS; i++ )
    printf( "%04X ", registers[ i ] );
  printf( "\n" );
}

//Runs the program (fetch, decode, execute)
void Run()
{
  while( running )
  {
    //showMemory();
    int instruction = fetch();
    decode( instruction );
    eval();
  }
  showMemory();
}

int main( int argc, const char * argv[] )
{
  Run();
  return 0;
}
