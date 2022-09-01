//=====================================================================
//
// test_httpserver_file_download.cpp - 
//
// Created by wwq on 2022/09/01
// Last Modified: 2022/09/01 16:48:03
//
//=====================================================================
#include <iostream>
#include <fstream>
#include "cpp-httplib/httplib.h"
#include "nlohmann/json.hpp"

using namespace httplib;
using namespace std;
using json = nlohmann::json;

const char *html = R"(
<form id="formElem">
<input type="file" name="file" accept="image/*">
<input type="submit">
</form>
<script>
formElem.onsubmit = async (e) => {
e.preventDefault();
let res = await fetch('/post', {
method: 'POST',
body: new FormData(formElem)
});
console.log(await res.text());
};
</script>
)";

int main(void)
{
    Server svr;

    svr.Get("/", [](const Request & /*req*/, Response &res)
            { res.set_content(html, "text/html"); });

    svr.Post("/post", [](const Request &req, Response &res)
             {
                 auto image_file = req.get_file_value("file");

                 cout << "image file length: " << image_file.content.length() << endl
                      << "image file name: " << image_file.filename << endl;

                 {
                     ofstream ofs(image_file.filename, ios::binary);
                     ofs << image_file.content;
                 }

                 json result{
                     {"code", 0},
                     {"msg", "ok"},
                     {"data", image_file.content.length()}};
                 res.set_content(result.dump(), "text/plain");
             });

    svr.listen("localhost", 5321);
}
