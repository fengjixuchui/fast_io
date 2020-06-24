#include"../../include/fast_io.h"
#include"../../include/fast_io_device.h"
#include"../../include/fast_io_crypto.h"

int main()
{
    std::array<std::uint8_t, 16> const key{1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8};
    std::array<std::uint8_t, 16> const iv{1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8};
    {
        fast_io::crypto::ocbc_encrypt<fast_io::obuf_file, fast_io::crypto::rc6::rc6_enc_128> 
            ob(std::piecewise_construct,std::forward_as_tuple("text.txt"),
            std::forward_as_tuple(std::as_bytes(std::span(key)), std::as_bytes(std::span(iv))));
        print(ob,"hello world\nxxxx\n8988\n");
    }
    {
        fast_io::crypto::icbc_decrypt<fast_io::ibuf_file, fast_io::crypto::rc6::rc6_dec_128> 
            ib(std::piecewise_construct,std::forward_as_tuple("text.txt"),
            std::forward_as_tuple(std::as_bytes(std::span(key)), std::as_bytes(std::span(iv))));
        transmit(fast_io::out(),ib);
    }
}