#include <httplib.h>
#include <iostream>

int main(void)
{
	/// 下载文件地址 http://192.216.20.115:8000/update.tar.gz
	httplib::Client cli("192.216.20.115", 8000);
	cli.set_connection_timeout(0, 300000); // 300 milliseconds
	cli.set_read_timeout(5, 0);            // 5 seconds
	cli.set_write_timeout(5, 0);           // 5 seconds
	std::ofstream file("1update.tar.gz", std::ofstream::binary);
	auto res =
		cli.Get("update.tar.gz", [&](const char *data, size_t data_length) {
				file.write(data, data_length);
				return true;
				});
	//   if (res->status == 200) {}
	return 0;
}

