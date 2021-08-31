#include <stdio.h>
#include "src/util.h"
#include <vector>
#include <string>
using namespace bfl::base;
int main()
{
	std::vector<std::string> files;
	std::string path = "/home/kingwq/test/cppFunction/cpp_framework/cfg";
	FSUtil::ListAllFile(files, path, ".yml");
	for(auto s : files)
	{
		printf("files : %s\n",s.c_str());
	}
	return 0;
}
