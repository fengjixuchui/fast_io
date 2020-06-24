#include"../../include/fast_io.h"
#include"../../include/fast_io_driver/win32_internet.h"

int main()
{
	auto session(fast_io::win32_internet_open("Microsoft Internet Explorer",INTERNET_OPEN_TYPE_PRECONFIG,nullptr,nullptr,0));
	auto connection(fast_io::win32_internet_connect(session,"www.google.com",443,nullptr,nullptr,INTERNET_SERVICE_HTTP,0,0));
	auto request(fast_io::win32_http_open_request(connection,"GET","index.html",HTTP_VERSION,nullptr,nullptr,
		INTERNET_FLAG_RELOAD | INTERNET_FLAG_SECURE | INTERNET_FLAG_KEEP_CONNECTION |
		INTERNET_FLAG_NO_AUTO_REDIRECT | INTERNET_FLAG_READ_PREFETCH | INTERNET_FLAG_NO_COOKIES |
		INTERNET_FLAG_NO_AUTH |	INTERNET_FLAG_RESTRICTED_ZONE |	INTERNET_FLAG_CACHE_IF_NET_FAIL |
		INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTP |	INTERNET_FLAG_IGNORE_CERT_CN_INVALID | INTERNET_FLAG_NO_UI,
	0));
	win32_http_send_request(request);
	fast_io::ibuf_win32_internet_io_observer internet_iob(request.handle);
	transmit(fast_io::out(),internet_iob);
}