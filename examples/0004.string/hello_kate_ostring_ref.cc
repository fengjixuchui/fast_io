//CppCon 2015: Kate Gregory “Stop Teaching C"
//https://www.youtube.com/watch?v=YnWhqhNdYyk&t=744s
#include"../../include/fast_io.h"

int main()
{
	std::string name;
	scan(name);
	std::string greeting;
	fast_io::ostring_ref oref(greeting);
	print(oref,"Hello, ",name);
	if (name == "Kate")
		println(oref,", I know you!");
	else
		println(oref,", I do not know you!");
	print(greeting);
}
