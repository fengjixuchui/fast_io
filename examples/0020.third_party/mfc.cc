#include"../../include/fast_io_third_party.h"
#include"../../include/fast_io.h"

int main()
try
{
	fast_io::obuf_mfc_file mfcf("wb.txt");
	print(mfcf,"Hello World\n");
}
catch(std::exception const& e)
{
	perrln(e);
	return 1;
}