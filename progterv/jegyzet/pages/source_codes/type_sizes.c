#include <stdio.h>

int main(int argc, char* argv[])
{
  printf("\nunsigned char  :  %d bit\n", (int)(8 * sizeof(unsigned char)));
  printf("unsigned short : %d bit\n", (int)(8 * sizeof(unsigned short)));
  printf("unsigned int   : %d bit\n", (int)(8 * sizeof(unsigned int)));
  printf("unsigned long  : %d bit\n\n", (int)(8 * sizeof(unsigned long)));
  printf("char  :  %d bit\n", (int)(8 * sizeof(char)));
  printf("short : %d bit\n", (int)(8 * sizeof(short)));
  printf("int   : %d bit\n", (int)(8 * sizeof(int)));
  printf("long  : %d bit\n\n", (int)(8 * sizeof(long)));
  printf("float  : %d bit\n", (int)(8 * sizeof(float)));
  printf("double : %d bit\n\n", (int)(8 * sizeof(double)));
  return 0;
}
