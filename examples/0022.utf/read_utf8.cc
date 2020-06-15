#include"../../include/fast_io.h"
#include"../../include/fast_io_device.h"
#include"../../include/fast_io_legacy.h"

#include <string>
#include <cwchar>

int main()
{
    fast_io::u8ibuf_file ifile("utf_file.txt");
    std::u8string u8s;
    for (std::u32string u32_str;scan<true>(ifile, fast_io::line(u8s));) {
        u32_str.clear();
        fast_io::ostring_ref ref(u32_str);
        print(ref,fast_io::code_cvt(u8s));
        print(fast_io::code_cvt(u32_str));
    }
    return 0;
}