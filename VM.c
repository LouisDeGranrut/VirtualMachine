#include <stdio.h>

#define NUM_REGS 4
int registers[NUM_REGS];//set of 4 registers

//The Program
int program[] = {0x1064,//in register 0, put 100
			  0x11C8,//in register 1, put 200
			  0x2201,//add register 0 and 1 in register 2
			  0x4402,//print what is in register 2
			  0x3302,//subtract
			  0x0000};
//0xCOMMAND + VALUE

int pcounter = 0;//program counter

//returns the content of the program at the line the program counter is pointing on
int fetch(){
    return program[pcounter++];    
}

/* instruction fields */
int instrNum = 0;
int reg1     = 0;
int reg2     = 0;
int reg3     = 0;
int immediate= 0;

/* decode a word */
void decode( int instruction )
{
  instrNum = (instruction & 0xF000) >> 12;
  reg1     = (instruction & 0xF00 ) >>  8;
  reg2     = (instruction & 0xF0  ) >>  4;
  reg3     = (instruction & 0xF   );
  immediate= (instruction & 0xFF  );
}

/* the VM runs until this flag becomes 0 */
int running = 1;

/* evaluate the last decoded instruction */
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
      printf( "add r%d r%d r%d\n", reg1, reg2, reg3 );
      registers[ reg1 ] = registers[ reg2 ] + registers[reg3 ];
      break;
    case 3:
      /* subtract */
      printf( "sub r%d r%d r%d\n", reg1, reg2, reg3 );
      registers[ reg1 ] = registers[ reg2 ] - registers[reg3 ];
      break;
    case 4:
      /* print value in register */
      printf( "print value in r%d: ", immediate);
      printf("%d\n",registers[ immediate ]);
      break;
    default:
    	printf("Error in line\n");
    	break;
  }
}

/* display all registers as 4-digit hexadecimal words */
void showRegisters()
{
  int i;
  printf( "regs = " );
  for( i=0; i<NUM_REGS; i++ )
    printf( "%04X ", registers[ i ] );
  printf( "\n" );
}

//Runs the program (fetch, decode, execute)
void Run()
{
  while( running )
  {
    //showRegisters();
    int instruction = fetch();
    decode( instruction );
    eval();
  }
  showRegisters();
}

int main( int argc, const char * argv[] )
{
  Run();
  return 0;
}
