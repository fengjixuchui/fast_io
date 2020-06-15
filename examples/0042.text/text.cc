#include"../../include/fast_io.h"
#include"../../include/fast_io_device.h"

int main()
{
	{
		fast_io::ibuf_file ibf("lf_source.txt");
		fast_io::obuf_text_file obf_text("crlf1.txt");
		transmit(obf_text,ibf);
	}
	{
		fast_io::ibuf_text_file ibf_text("crlf1.txt");
		fast_io::obuf_text_file obf_text("crlf2.txt");
		transmit(obf_text,ibf_text);
	}
	{
		fast_io::ibuf_text_file ibf_text("crlf2.txt");
		fast_io::obuf_file obf("lf_dest.txt");
		transmit(obf,ibf_text);
	}
}