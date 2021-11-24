#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

int main(int argc, char** argv)
{
	static const struct option long_option[]={
		        {"bs",required_argument,NULL,1},
                {"id",required_argument,NULL,2},
                {"bm",no_argument,NULL,3},
                {"rs",required_argument,NULL,4},
                {"rm",required_argument,NULL,5},
                {"mid",required_argument,NULL,6},
                {"sid",required_argument,NULL,7},
                //{"tid",required_argument,NULL,6},
                {NULL,0,NULL,0}
	};
	int opt;
	/* int agreeResult = 1; */
	char* endptr = 0;
	while ((opt = getopt_long(argc,argv,"dc:h", long_option, NULL))!=-1) {
		printf("___________get opt is %d\n",opt);
		switch(opt)
		{
		case 0:
			break;
		case 'c':
			{
			int agreeResult = strtol(optarg, &endptr, 10);
			printf("-c 0:rejet, 1:agree, agreeResut %d invalid\n",agreeResult);
			if(agreeResult > 1)
			{
				printf("-c 0:rejet, 1:agree, agreeResut %d invalid\n",agreeResult);
                exit(0);
			}
			printf("-c\n");
				
			}
			break;
		case 'd':
			printf("-d\n");
			break;
		case 1:
			printf("-bs\n");
			break;
		}
	}
	return 0;
}
