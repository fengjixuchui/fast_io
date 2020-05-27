//CppCon 2015: Kate Gregory “Stop Teaching C"
//https://www.youtube.com/watch?v=YnWhqhNdYyk&t=744s
#include"../../include/fast_io.h"

int main()
{
	std::string name;
	scan(name);
	std::string greeting = fast_io::concat("Hello, " , name);
	if (name == "Kate")
		greeting += ", I know you!";
	println(greeting);
}
