#include <stdio.h>

int main(int argc, char* argv[])
{
  FILE* file;
  unsigned char value;

  value = 94;

  file = fopen("values.dat", "wb");
  fwrite(&value, sizeof(value), 1, file);
  fclose(file);

  return 0;
}
