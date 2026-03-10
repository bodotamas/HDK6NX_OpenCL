#include <stdio.h>

int main(int argc, char* argv[])
{
  FILE* file;
  unsigned char value;

  file = fopen("values.dat", "rb");
  fread(&value, sizeof(value), 1, file);
  fclose(file);

  printf("value = %u\n", value);

  return 0;
}
