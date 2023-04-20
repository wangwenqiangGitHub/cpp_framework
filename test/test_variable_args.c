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
#include <time.h>
#include <stdint.h>
#include <termio.h>

void c_print(const char* fmt, ...)
{
	int i;
	va_list ap;
	char buf[1024]= {0};
	va_start(ap, fmt);
	int plen = vsnprintf(buf, 1024, fmt, ap);
	buf[plen] = 0;
	va_end(ap);
	for(i = 0; i<plen; i++)
	{
		printf("buf:%s\n",*buf+i);
	}
}
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

typedef struct console_history_s
{
	time_t timestamp;
	uint32_t execnt;
	char data[0];
}console_history_t;

typedef struct console_context_s
{
	int fd;

	int nline;
	int nesc;
	int cursor;

	int histidx;
	int maxhist;
	char buf[1024];
	char escape[512];
	console_history_t* history[512];
	struct termios tio;
} console_context_t;
int console_print(console_context_t* ctx, const char* fmt, ...)
{

}
int main(int argc, char *argv[])
{
	variadic_func(3, MY_INPUT);
	char a[1]= "a";
	char b[1]= "b";

	c_print("%s%s", a,b);
	return 0;
}
