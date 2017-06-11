#include <stdio.h>
#include <stdlib.h>

int
func1(void)
{
  printf("Hello world\n");
}

int
main(void)
{
  printf("This is a test\n");
  func1();
  return EXIT_SUCCESS;
}
