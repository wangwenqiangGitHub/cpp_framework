#include "src/config.h"
#include "yaml-cpp/yaml.h"
#include <iostream>
using namespace bfl::base;

void print_yaml(const YAML::Node& node)
{
	// 是纯量
	if(node.IsScalar())
	{

	}
	// 是数组
	if(node.IsSequence())
	{

	}
	if(node.IsMap())
	{

	}


}

bfl::base::ConfigVar<int>::ptr g_int_value_config = 
	bfl::base::Config::Lookup("system.port", (int)8080, "system port");

bfl::base::ConfigVar<float>::ptr g_float_value_config =
	bfl::base::Config::Lookup("system.value", (float)10.2f, "system value");
void test_config()
{
 YAML::Node root = YAML::LoadFile("/home/kingwq/test/cppFunction/syllar/cfg/test_config.yml");
 bfl::base::Config::LoadFromYaml(root);

 std::printf("%d\n", g_int_value_config->getValue());
 std::printf("%s\n",g_float_value_config->toString().c_str());
}

int main(int argc,char** argv)
{
	std::printf("test config\n");
	test_config();
	return 0;
}
