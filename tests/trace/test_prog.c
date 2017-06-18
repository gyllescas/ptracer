#include <stdio.h>
#include <stdlib.h>

void func1(void)
{
  asm volatile("pause");
  asm volatile("pause");
}

int
main(void)
{
  printf("This is a test\n");
  func1();
  return EXIT_SUCCESS;
}
