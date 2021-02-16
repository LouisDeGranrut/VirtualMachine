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
int program[] = {
				0x1064,//in register 0, put 100
			  	0x11C8,//in register 1, put 200
			  	0x2201,//add register 0 and 1 in register 2
			  	0x4402,//print what is in register 2
			  	0x3201,//subtract 0 and 
			  	0x4402,//print what is in register 2
			  	0x6603,//jump to line 3
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
      printf( "halt\n" );
      running = 0;
      break;
    case 1:
      /* load reg+value*/
      printf( "load r%d #%d\n", reg1, immediate );
      registers[ reg1 ] = immediate;
      break;
    case 2:
      /* add */
      printf( "add  r%d r%d r%d\n", reg1, reg2, reg3 );
      registers[ reg1 ] = registers[ reg2 ] + registers[reg3 ];
      break;
    case 3:
      /* subtract */
      printf( "sub  r%d r%d r%d\n", reg1, reg2, reg3 );
      registers[ reg1 ] = registers[ reg2 ] - registers[reg3 ];
      break;
    case 4:
      /* print value in register */
      printf( "show r%d: ", immediate);
      printf("%d\n",registers[ immediate ]);
      break;
    case 5:
      /* resets program counter */
      printf( "Reset program counter: ");
      pcounter = 0;
      break;
    case 6:
      /* jump to set adress*/
      printf( "jump to r%d: ", immediate);
      pcounter = immediate;
      break;
    default:
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
