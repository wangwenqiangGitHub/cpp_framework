#include "src/config.h"
#include "yaml-cpp/yaml.h"
#include <iostream>
using namespace bfl::base;

class Person{
public:
	Person(){}
	std::string m_name;
	int m_age = 10;
	bool m_sex = 0;
	
	std::string toString() const{
		std::stringstream ss;
		ss << "[Person name=" << m_name
			<< " age=" << m_age
			<< " sex=" << m_sex
			<< "]";
		return ss.str();
	}

	bool operator==(const Person& oth) const
	{
		return m_name == oth.m_name
			&& m_age == oth.m_age
			&& m_sex == oth.m_sex;
	}
	

};

namespace bfl{ namespace base{
template<>
class LexicalCast<std::string, Person> {
public:
	Person operator()(const std::string& v) 
	{
		YAML::Node node = YAML::Load(v);
		Person p;
		p.m_name = node["name"].as<std::string>();
		p.m_age = node["age"].as<int>();
		p.m_sex = node["sex"].as<bool>();
		return p;
	}
};

template<>
class LexicalCast<Person, std::string> {
public:
	std::string operator()(const Person& p) 
	{
		YAML::Node node;
		node["name"] = p.m_name;
		node["age"] = p.m_age;
		node["sex"] = p.m_sex;
		std::stringstream ss;
		ss << node;
		return ss.str();
	}
};
}
}

ConfigVar<Person>::ptr g_person = Config::Lookup("class.person", Person(), "system person");
void test_class() 
{
	printf("%d\n", g_person->getValue().m_age);
}
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
	YAML::Node root = YAML::LoadFile("/home/kingwq/test/cppFunction/cpp_framework/cfg/test_config.yml");
	bfl::base::Config::LoadFromYaml(root);
	std::cout << "test root"<<  root["name"].IsDefined() << std::endl;
	std::printf("test1 %d\n", g_int_value_config->getValue());
	std::printf("test2 %s\n", g_float_value_config->toString().c_str());
}

int main(int argc,char** argv)
{
	std::printf("test config\n");
	test_config();
	test_class();
	return 0;
}
