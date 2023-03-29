//=====================================================================
//
// test_json-c.c - 
//
// Created by wwq on 2023/02/24
// Last Modified: 2023/02/24 09:42:16
//
//=====================================================================
#include <json-c/json_object.h>
#include <json-c/json_tokener.h>
#include <stdio.h>
#include <json-c/json.h>

// json对象 json_object* mm
// json对象指针定义后，采用json_object_put去释放
int main(int argc, char** argv)
{
	FILE *fp;
	char buff[1024];

	struct json_object* parse_json;
	struct json_object* name;
	struct json_object* age;
	struct json_object* friends;

	struct json_object* friend;

	size_t n_friends;
	size_t i;
	fp = fopen("../cfg/test_json_file.json", "r");
	fread(buff, 1024, 1, fp);
	fclose(fp);

	parse_json = json_tokener_parse(buff);
	json_object_object_get_ex(parse_json, "name", &name);
	json_object_object_get_ex(parse_json, "age", &age);
	json_object_object_get_ex(parse_json, "friends", & friends);
	n_friends = json_object_array_length(friends);

	printf("find %lu friends\n", n_friends);
	for(i = 0; i < n_friends; i++)
	{
		friend = json_object_array_get_idx(friends, i);
		printf("%lu. %s\n",i+1, json_object_get_string(friend));
	}


	return 0;
}
