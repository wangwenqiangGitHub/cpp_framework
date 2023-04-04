
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char cmd[128] = {0};
	char line[128] = {0};
	sprintf(cmd, "ps | grep %s", "ps");
	
	FILE *cmdFp = NULL;
	cmdFp = popen(cmd, "r");
	while (fgets(line, sizeof(line), cmdFp)) {
		char processName[128] = {0};
		int pid = -1;
		sscanf(line, "%d %s", &pid, processName);
		printf("id:%d, name:processName:%s\n",pid,processName);
		memset(line, 0, sizeof(line));
	}
	return 0;
}
