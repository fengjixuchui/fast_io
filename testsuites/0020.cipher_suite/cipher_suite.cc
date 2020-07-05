#include"../../include/fast_io.h"
#include"../../include/fast_io_crypto.h"

int main()
{
	println(fast_io::tls::cipher_suite::tls_dhe_rsa_with_aes_256_cbc_sha256);
	println(fast_io::tls::cipher_suite::tls_aes_128_ccm_sha256);
}