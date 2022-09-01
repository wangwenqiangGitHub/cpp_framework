//=====================================================================
//
// test_httpclient_file_upload.cpp - 
//
// Created by wwq on 2022/09/01
// Last Modified: 2022/09/01 16:51:55
//
//=====================================================================
#include "cpp-httplib/httplib.h"
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

int main(int argc, char const *argv[])
{
    httplib::Client cli("http://localhost:5321");

    ifstream fin("/var/log.log", ios::binary);
    ostringstream os;
    os << fin.rdbuf();
    std::string content = os.str();
    cout << content.length() << endl;
    fin.close();

    httplib::MultipartFormDataItems items = {
        {"file", content, "log.log", "application/octet-stream"},
    };

    auto res = cli.Post("/post", items);
	// http返回的消息
    cout << res->body;

    return 0;
}
