//=====================================================================
//
// test_variable_args.c - 
//
// Created by wwq on 2023/04/04
// Last Modified: 2023/04/04 15:09:00
//
//=====================================================================
#include <stdio.h>
#include <stdarg.h>

void variadic_func(int count, ...)
{
	va_list args;
	va_start(args, count);
	printf("argument count = %d\n", count);
	for(int i = 0; i < count; i++)
	{
		printf("argument %d = %d\n", i+1, va_arg(args, int));
	}
	printf("\n");
	vprintf("My ARGS = %d %d %d\n", args);
	va_end(args);
}
#define MY_INPUT 10, 20, 30
int main(int argc, char *argv[])
{
	variadic_func(3, MY_INPUT);	
	return 0;
}
