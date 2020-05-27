//CppCon 2015: Kate Gregory “Stop Teaching C"
//https://www.youtube.com/watch?v=YnWhqhNdYyk&t=744s
#include"../../include/fast_io.h"

int main()
{
	std::string name;
	scan(name);
	if (name == "Kate")
		println(fast_io::concat("Hello, " , name, ", I Know you!"));
	else
		println("Hello, ", name, ", I Don't Know you!");
}
