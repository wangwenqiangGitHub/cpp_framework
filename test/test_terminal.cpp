#include <unistd.h>
#include <vector>
#include <iostream>
#include <algorithm>
// 测试daemon()程序后台启动。
// reinterpret_cast<>是对于无关类型的转换
// void(var)是对未使用变量的警告消息的消除
int main(int argc, char**argv)
{
	bool m_daemon = false;
	std::vector<std::string> args(reinterpret_cast<char**>(argv),reinterpret_cast<char**>(argv) + argc);
	if(std::find(args.begin(),args.end(), "--help")!= args.end())
	{
		printf("hello word\n");
	}
	
	if(std::find(args.begin(),args.end(), "--d")!= args.end() || 
		std::find(args.begin(),args.end(), "-d")!= args.end() 	)
	{
		m_daemon = true;
		printf("hello word -d\n");
	}
	
	if(std::find(args.begin(),args.end(), "-h")!= args.end())
	{
		printf("hello word -h\n");
	}
	
	if(m_daemon)
	{
		int n = daemon(1, 0);
		(void)n;
	}
	while (1) {
		printf("test daemon \n");
		sleep(1);
	}
	return 0;
}
