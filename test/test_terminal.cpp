#include <vector>
#include <iostream>
#include <algorithm>

int main(int argc, char**argv)
{
	std::vector<std::string> args(reinterpret_cast<char**>(argv),reinterpret_cast<char**>(argv) + argc);
	if(std::find(args.begin(),args.end(), "--help")!= args.end())
	{
		printf("hello word\n");
	}
	
	if(std::find(args.begin(),args.end(), "--d")!= args.end())
	{
		printf("hello word -d\n");
	}
	
	if(std::find(args.begin(),args.end(), "-h")!= args.end())
	{
		printf("hello word -h\n");
	}

	return 0;
}
