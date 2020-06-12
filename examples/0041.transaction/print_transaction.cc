#include"../../include/fast_io_legacy.h"

int main()
{
	print_transaction(fast_io::c_stdout,[](auto& m)
	{
		print(m,"Hello  world\n");
		print(m,"Hello  world\n");
		print(m,"Hello  world\n");
		print(m,"Hello  world\n");
		print(m,"Hello  world\n");
		print(m,"Hello  world\n");
		print(m,"Hello  world\n");
		print(m,"Hello  world\n");
		print(m,"Hello  world\n");
		print(m,"Hello  world\n");
		print(m,"Hello  world\n");
		print(m,"Hello  world\n");
		print(m,"Hello  world\n");
	});
}