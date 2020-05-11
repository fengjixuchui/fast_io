#include"../../../include/fast_io.h"
#include"../../../include/fast_io_network.h"
#include"../../../include/fast_io_device.h"
#include"../../../include/fast_io_driver/openssl_driver.h"

int main()
{
	fast_io::tcp_client client(fast_io::dns_once("www.google.com"),443);
	fast_io::openssl::ssl_context ssl_ctx(fast_io::openssl::tls_method::tls);
	fast_io::openssl::ibuf_ssl_file ssl(ssl_ctx,client);
	print(ssl,u8"GET / HTTP/1.1\r\n"
		"Host:www.google.com\r\n"
		"User-agent:whatever\r\n"
		"Accept-Type:*/*\r\n"
		"Connection:close\r\n\r\n");
	fast_io::skip_http_header(ssl);
	fast_io::onative_file html_file("index.html");
	transmit(html_file,ssl);
}