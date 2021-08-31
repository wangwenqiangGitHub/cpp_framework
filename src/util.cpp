#include <string>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>

#include "util.h"

namespace bfl {namespace base{


void FSUtil::ListAllFile(std::vector<std::string>& files 
						,const std::string& path 
						,const std::string& subfix)
{
	if(access(path.c_str(), 0) != 0)
	{
		return;
	}
	DIR* dir = opendir(path.c_str());
	if(dir == nullptr)
	{
		return;
	}
	struct dirent* dp = nullptr;
	while((dp = readdir(dir)) != nullptr)
	{
		if(dp->d_type == DT_DIR)
		{
			if(!strcmp(dp->d_name, ".") || !strcmp(dp->d_name, ".."))
			{
				continue;
			}
			ListAllFile(files, path + "/" + dp->d_name, subfix);
		}
		else if(dp->d_type == DT_REG)
		{
			std::string filename(dp->d_name);
			if(subfix.empty())
			{
				files.push_back(path + "/" + filename);
			}
			else
			{
				if(filename.size() < subfix.size())
				{
					continue;
				}
				if(filename.substr(filename.length() - subfix.size()) == subfix)
				{
					files.push_back(path + "/" +filename);
				}
			}
		}
	}
	closedir(dir);
}

/**
 * @brief 
 * @param file 文件的路径
 * @param st 描述linux文件系统中的文件结构属性
 * @return EBADF：文件描述词无效； EFAULT:地址空间不可访问; ELOOP:遍历路径时遇到太多的符号连接 
 *		0表示成功
 */
static int __lstat(const char* file, struct stat* st = nullptr)
{
	struct stat lst;
	int ret = lstat(file, &lst);
	if(st)
	{
		*st = lst;
	}
	return ret;
}

static int __mkdir(const char* dirname)
{
	if(access(dirname, F_OK) == 0)
	{
		return 0;
	}
	return mkdir(dirname, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
}

bool FSUtil:: Mkdir(const std::string& dirname)
{
	if(__lstat(dirname.c_str()) == 0)
	{
		return true;
	}
	// 拷贝字符串的一个副本
	char* path = strdup(dirname.c_str());
	// 在该函数返回在字符串 str 中第一次出现字符 c 的位置，如果未找到该字符则返回 NULL
	char* ptr = strchr(path + 1, '/');
	do{
		for(; ptr; *ptr = '/', ptr = strchr(ptr + 1, '/'))
		{
			if(__mkdir(path) != 0)
			{
				break;
			}
		}
		if(ptr != nullptr)
		{
			break;
		}
		else if(__mkdir(path) != 0)
		{
			break;
		}
		free(path);
		return true;
	}while(0);
	free(path);
	return false;
}
bool FSUtil:: IsRunningPidfile(const std::string& pidfile)
{
	return true;
}
bool FSUtil:: Rm(const std::string& path)
{
	return true;
}
bool FSUtil:: Mv(const std::string& from, const std::string& to)
{
	return true;
}
bool FSUtil:: Realpath(const std::string& path, std::string& rpath)
{
	return true;
}

}
}
