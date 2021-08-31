#include "src/config.h"
#include "src/util.h"
#include "yaml-cpp/yaml.h"
#include "test/test_config_serverCfg.h"
#include <iostream>
#include <vector>
// using namespace bfl::base;
int main()
{
// Looup("server",) 在配置文件中第一个类的关键词是servers导致没有调试通，注意使用
static bfl::base::ConfigVar<std::vector<bfl::base::TcpServerConf>>::ptr g_servers_conf =
		bfl::base::Config::Lookup("servers", std::vector<bfl::base::TcpServerConf>(),"http server config");

	bfl::base::Config::LoadFromConfDir("/home/kingwq/test/cppFunction/cpp_framework/cfg");
	auto http_confs = g_servers_conf->getValue();
	// http_confs-
	printf("size:%d\n",http_confs.empty());
	for(auto& i : http_confs)
	{
		printf("test server msg\n");

		std::cout <<bfl::base:: LexicalCast<bfl::base::TcpServerConf, std::string>()(i) << std::endl;
	}
	return 0;
}
