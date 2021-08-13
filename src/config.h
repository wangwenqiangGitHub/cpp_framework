#ifndef __SYLLAT_CONFIG_H__
#define __SYLLAT_CONFIG_H__

#include <memory>
#include <string>
#include <sstream>
#include <type_traits>
#include <algorithm>
#include <functional>
#include <map>
#include <vector>
#include <list>
#include <unordered_map>
#include <set>
#include <unordered_set>

#include "boost/lexical_cast.hpp"
#include "yaml-cpp/yaml.h"
/**
 * ConfigVarBase 配置的基类(配置变量基类)，定义了配置项类的基础接口
 */
namespace bfl{ namespace base{
class ConfigVarBase{
public:
	typedef std::shared_ptr<ConfigVarBase> ptr;

	/**
	 * @brief 
	 *
	 * @param name
	 * @param description
	 */
	ConfigVarBase(const std::string& name, const std::string& description = "")
		:m_name(name)
		, m_description(description)
		{
			std::transform(m_name.begin(), m_name.end(), m_name.begin(),::tolower);
		}
	~ConfigVarBase(){}

	/**
	 * @brief 返回配置参数名称
	 */
	const std::string& getName()const {return m_name;}
	/**
	 * @brief 返回参数的描述
	 */
	const std::string& getDescription() const{ return m_description;}
	/**
	 * @brief 转换成字符串
	 */
	virtual std::string toString() = 0;

	/**
	 * @brief 从字符串初始化值
	 */
	virtual bool fromString(const std::string& val) = 0;

	/**
	 * @brief 返回配置参数值的类型名称
	 */
	// virtual std::string getTypeName() const = 0;

protected:
	/// 配置参数名称
	std::string m_name;
	/// 配置参数描述
	std::string m_description;
};

/**
 * 类型转换模板类(F源类型，T目标类型)
 */
template<class F, class T>
class LexicalCast{
public:
	//类型转换
	T operator()(const F&v){
		return boost::lexical_cast<T>(v);
	}
};
/**
 * 类型转换模板类偏特化(yaml string h转换成std::vector<T>)
 */

template<class T>
class LexicalCast<std::string, std::vector<T>>
{
	std::vector<T> operator()(const std::string& v)
	{
		YAML::Node node = YAML::Load(v);
		typename std::vector<T> vec;
		std::stringstream ss;
		for(size_t i =0; i < node.size(); ++i)
		{
			ss.str("");
			ss << node[i];
			vec.push_back(LexicalCast<std::string, T>()(ss.str()));

		}
		return vec;
	}
};
/**
 * @brief 类型转换模板类片特化(std::vector<T> 转换成 YAML String)
 */
template<class T>
class LexicalCast<std::vector<T>, std::string> {
public:
    std::string operator()(const std::vector<T>& v) {
        YAML::Node node(YAML::NodeType::Sequence);
        for(auto& i : v) 
		{
            node.push_back(YAML::Load(LexicalCast<T, std::string>()(i)));
        }
        std::stringstream ss;
        ss << node;
        return ss.str();
    }
};

/**
 *  * @brief 类型转换模板类片特化(YAML String 转换成 std::list<T>)
 *   */
template<class T>
class LexicalCast<std::string, std::list<T> > {
public:
	std::list<T> operator()(const std::string& v) {
		YAML::Node node = YAML::Load(v);
		typename std::list<T> vec;
		std::stringstream ss;
		for(size_t i = 0; i < node.size(); ++i) {
			ss.str("");
			ss << node[i];
			vec.push_back(LexicalCast<std::string, T>()(ss.str()));
		}
		return vec;
	}
};

/**
 *  * @brief 类型转换模板类片特化(std::list<T> 转换成 YAML String)
 *   */
template<class T>
class LexicalCast<std::list<T>, std::string> {
public:
	std::string operator()(const std::list<T>& v) {
		YAML::Node node(YAML::NodeType::Sequence);
		for(auto& i : v) {
			node.push_back(YAML::Load(LexicalCast<T, std::string>()(i)));
		}
		std::stringstream ss;
		ss << node;
		return ss.str();
	}
};

/**
 *  * @brief 类型转换模板类片特化(YAML String 转换成 std::set<T>)
 *   */
template<class T>
class LexicalCast<std::string, std::set<T> > {
public:
	std::set<T> operator()(const std::string& v) {
		YAML::Node node = YAML::Load(v);
		typename std::set<T> vec;
		std::stringstream ss;
		for(size_t i = 0; i < node.size(); ++i) {
			ss.str("");
			ss << node[i];
			vec.insert(LexicalCast<std::string, T>()(ss.str()));
		}
		return vec;
	}
};

/**
 *  * @brief 类型转换模板类片特化(std::set<T> 转换成 YAML String)
 *   */
template<class T>
class LexicalCast<std::set<T>, std::string> {
public:
std::string operator()(const std::set<T>& v) {
		YAML::Node node(YAML::NodeType::Sequence);
		for(auto& i : v) {
					node.push_back(YAML::Load(LexicalCast<T, std::string>()(i)));
				}
		std::stringstream ss;
		ss << node;
		return ss.str();
	}
};

/**
 *  * @brief 类型转换模板类片特化(YAML String 转换成 std::unordered_set<T>)
 *   */
template<class T>
class LexicalCast<std::string, std::unordered_set<T> > {
public:
	std::unordered_set<T> operator()(const std::string& v) {
		YAML::Node node = YAML::Load(v);
		typename std::unordered_set<T> vec;
		std::stringstream ss;
		for(size_t i = 0; i < node.size(); ++i) {
			ss.str("");
			ss << node[i];
			vec.insert(LexicalCast<std::string, T>()(ss.str()));
		}
		return vec;
	}
};

/**
 *  * @brief 类型转换模板类片特化(std::unordered_set<T> 转换成 YAML String)
 *   */
template<class T>
class LexicalCast<std::unordered_set<T>, std::string> {
public:
	std::string operator()(const std::unordered_set<T>& v) {
		YAML::Node node(YAML::NodeType::Sequence);
		for(auto& i : v) {
			node.push_back(YAML::Load(LexicalCast<T, std::string>()(i)));
		}
		std::stringstream ss;
		ss << node;
		return ss.str();
	}
};

/**
 *  * @brief 类型转换模板类片特化(YAML String 转换成 std::map<std::string, T>)
 *   */
template<class T>
class LexicalCast<std::string, std::map<std::string, T> > {
public:
	std::map<std::string, T> operator()(const std::string& v) {
		YAML::Node node = YAML::Load(v);
		typename std::map<std::string, T> vec;
		std::stringstream ss;
		for(auto it = node.begin();
				it != node.end(); ++it) {
			ss.str("");
			ss << it->second;
			vec.insert(std::make_pair(it->first.Scalar(),
						LexicalCast<std::string, T>()(ss.str())));
		}
		return vec;
	}
};

/**
 *  * @brief 类型转换模板类片特化(std::map<std::string, T> 转换成 YAML String)
 *   */
template<class T>
class LexicalCast<std::map<std::string, T>, std::string> {
public:
	std::string operator()(const std::map<std::string, T>& v) {
		YAML::Node node(YAML::NodeType::Map);
		for(auto& i : v) {
			node[i.first] = YAML::Load(LexicalCast<T, std::string>()(i.second));
		}
		std::stringstream ss;
		ss << node;
		return ss.str();
	}
};

/**
 *  * @brief 类型转换模板类片特化(YAML String 转换成 std::unordered_map<std::string, T>)
 *   */
template<class T>
class LexicalCast<std::string, std::unordered_map<std::string, T> > {
	public:
		std::unordered_map<std::string, T> operator()(const std::string& v) {
			YAML::Node node = YAML::Load(v);
			typename std::unordered_map<std::string, T> vec;
			std::stringstream ss;
			for(auto it = node.begin();
					it != node.end(); ++it) {
				ss.str("");
				ss << it->second;
				vec.insert(std::make_pair(it->first.Scalar(),
							LexicalCast<std::string, T>()(ss.str())));
			}
			return vec;
		}
};

/**
 *  * @brief 类型转换模板类片特化(std::unordered_map<std::string, T> 转换成 YAML String)
 *   */
template<class T>
class LexicalCast<std::unordered_map<std::string, T>, std::string> {
	public:
		std::string operator()(const std::unordered_map<std::string, T>& v) {
			YAML::Node node(YAML::NodeType::Map);
			for(auto& i : v) {
				node[i.first] = YAML::Load(LexicalCast<T, std::string>()(i.second));
			}
			std::stringstream ss;
			ss << node;
			return ss.str();
		}
};

template<class T, class FromStr = LexicalCast<std::string, T>
		, class ToStr = LexicalCast<T, std::string>>
class ConfigVar : public ConfigVarBase{
public:
	typedef std::shared_ptr<ConfigVar> ptr;
	typedef std::function<void(const T& old_value, const T& new_value)> on_change_cb;

	ConfigVar(const std::string& name
			, const T& default_value
			, const std::string& description = " ")
		:ConfigVarBase(name,description)
		,m_val(default_value){

		}
	~ConfigVar(){}

	std::string toString() override
	{
		try {
		return ToStr()(m_val);
		} catch (std::exception& e) {
			printf("erro: %s \n", e.what());
		}
		return "";
	}

	bool fromString(const std::string& val) override
	{
		try{
			setValue(FromStr()(val));
		}catch(std::exception& e)
		{
			std::printf("erro: %s \n",e.what());
		}
		return false;
	}

	const T getValue(){
		return m_val;
	}

	/*
	 * 设置当前参数的值
	 * 如果参数的值发生变化则注册在回调中
	 * */
	void setValue(const T& v)
	{
		if(v == m_val)
		{
			return;
		}
		for(auto& i: m_cbs)
		{
			i.second(m_val, v);
		}
		m_val = v;
	}

	// std::string getTypeName() const override {return TypeToName<T>();} 
private:
	T m_val;
	//变更回调数组，uint64_t key,要求唯一，一般可以用hash

	std::map<uint64_t, on_change_cb> m_cbs;
};

class Config{
public:
	typedef std::unordered_map<std::string, ConfigVarBase::ptr> ConfigVarMap;

	/// 创建对应参数的配置参数
	/// name-配置参数名称
	/// default_value 默认参数
	/// description 参数描述
	/// detail-获取参数名为name的配置参数，如果存在直接返回，如果不存在，
	/// 创建参数配置并用default_value赋值
	template<class T>
	static typename ConfigVar<T>::ptr Lookup(const std::string& name,
			const T& default_value, const std::string& description = "")
	{
		auto it = GetDatas().find(name);
		if(it != GetDatas().end())
		{
			auto tmp = std::dynamic_pointer_cast<ConfigVar<T>>(it->second);
			if(tmp)
			{
				return tmp;
			}
			else 
			{
				printf("Lookup name = %s exists but type not\n",name.c_str());
				return nullptr;
			}
		}
		if(name.find_last_not_of("abcdefghigklmnopqrstuvwxyz._0123456789")
				!= std::string::npos)
		{
			printf("lookup is invalid %s\n", name.c_str());
		}
		typename ConfigVar<T>::ptr v(new ConfigVar<T>(name, default_value, description));
		GetDatas()[name] = v;
		return v;
	}

	template<class T>
	static typename ConfigVar<T>::ptr Lookup(const std::string& name)
	{
		auto it = GetDatas().find(name);
		if(it == GetDatas().end())
		{
			return nullptr;
		}
		return std::dynamic_pointer_cast<ConfigVar<T>>(it->second);
	}

	static void LoadFromYaml(const YAML::Node& root);
	static void LoadFromConfDir(const std::string& path, bool force = false);

	static ConfigVarBase::ptr LookupBase(const std::string& name);
	static void Visit(std::function<void(ConfigVarBase::ptr)> cb);

private:
	/// 返回所有的配置项
	static ConfigVarMap& GetDatas()
	{
		static ConfigVarMap s_datas;
		return s_datas;
	}
};

}
}
#endif
