#include"../../include/fast_io.h"
#include"../../include/fast_io_driver/asio_driver.h"

int main()
{
	asio::io_service service;
	asio::ip::tcp::socket socket(service);
	asio::ip::tcp::endpoint tcp(asio::ip::address_v4::from_string("127.0.0.1"),4000);
	socket.connect(tcp);
	fast_io::asio_driver::ibuf_ip_tcp_socket_io_observer iob(std::addressof(socket));
	transmit(fast_io::out(),iob);
}