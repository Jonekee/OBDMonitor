#include <stdio.h>
#include <stm32f4xx.h>

struct __FILE { int handle; /* Add whatever is needed */ };
FILE __stdout;
FILE __stdin;

int fputc(int ch, FILE *f) {
  return ITM_SendChar(ch);
}
