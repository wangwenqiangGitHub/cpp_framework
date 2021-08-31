#ifndef __BFL_UTIL_H__
#define __BFL_UTIL_H__
#include <cxxabi.h>
#include <pthread.h>
#include <vector>
#include <string>

#include "boost/lexical_cast.hpp"
namespace bfl {namespace base{

/**
 * @brief FSUtil: file system util
 */
class FSUtil
{
public:
	static void ListAllFile(std::vector<std::string>& file
			,const std::string& path
			,const std::string& subfix);
	static bool Mkdir(const std::string& pidfile);
	static bool IsRunningPidfile(const std::string& pidfile);
	static bool Rm(const std::string& path);
	static bool Mv(const std::string& from, const std::string& to);
	static bool Realpath(const std::string& path, std::string& rpath);

};

//template<class V,class Map, class K>
//V GetParamValue(const Map& m, const K& k, const V& def = V())
//{
//	auto it = m.find(k);
//	if(it == m.end())
//	{
//		return def;
//	}
//	try{
//		return boos::lexical_cast<V>
//	}
//
//}


}/// namespace base
}/// namespace bfl
#endif
