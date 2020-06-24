#include"../../include/fast_io.h"
#include"../../include/fast_io_device.h"
#include"../../include/fast_io_crypto.h"

int main()
{
    std::array<std::uint8_t, 16> const key{1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8};
    std::array<std::uint8_t, 8> const nonce{1,2,3,4,5,6,7,8};
    {
        fast_io::crypto::octr_little_endian<fast_io::obuf_file, fast_io::crypto::speck::speck_enc_128_128> 
            ob(std::piecewise_construct,std::forward_as_tuple("text.txt"),
            std::forward_as_tuple(std::as_bytes(std::span(key)), std::as_bytes(std::span(nonce))));
        print(ob,"hello world\nxxxx\n8988\n");
    }
    {
        fast_io::crypto::ictr_little_endian<fast_io::ibuf_file, fast_io::crypto::speck::speck_enc_128_128> 
            ib(std::piecewise_construct,std::forward_as_tuple("text.txt"),
            std::forward_as_tuple(std::as_bytes(std::span(key)), std::as_bytes(std::span(nonce))));
        transmit(fast_io::out(),ib);
    }
/*    {
        fast_io::crypto::octr_big_endian<fast_io::obuf_file, fast_io::crypto::speck::speck_enc_128_128> 
            ob(std::piecewise_construct,std::forward_as_tuple("text.txt"),
            std::forward_as_tuple(std::as_bytes(std::span(key)), std::as_bytes(std::span(nonce))));
        print(ob,"hello world\nxxxx\n8988\n");
    }
    {
        fast_io::crypto::ictr_big_endian<fast_io::ibuf_file, fast_io::crypto::speck::speck_enc_128_128> 
            ib(std::piecewise_construct,std::forward_as_tuple("text.txt"),
            std::forward_as_tuple(std::as_bytes(std::span(key)), std::as_bytes(std::span(nonce))));
        transmit(fast_io::out(),ib);
    }*/
}