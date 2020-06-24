
#include"../../include/fast_io.h"
#include"../../include/fast_io_device.h"
#include"../../include/fast_io_crypto.h"

int main(int argc,char** argv)
try
{
	std::array<std::uint8_t, 16> const key{1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8};
    std::array<std::uint8_t, 12> const nonce{1,2,3,4,5,6,7,8,9,10,11,12};
    std::span<std::byte const> skey(reinterpret_cast<std::byte const*>(key.data()), 16);
    fast_io::gmac<fast_io::crypto::rc6::rc6_enc_128> mac(skey);
    //print(mac, "aaaaaaa");
    //mac.digest();
}
catch(std::exception const& e)
{
	perrln(e);
	return 2;
}
