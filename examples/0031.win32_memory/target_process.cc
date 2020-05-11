#include<thread>
#include<condition_variable>
#include<mutex>
#include"../../include/fast_io.h"

int main()
{
	std::array<char,8192> arr;
	arr.fill('0');
	println(fast_io::unsigned_view(arr.data()));
	std::condition_variable cv;
	std::mutex m;
	std::unique_lock<std::mutex> lock(m);
	cv.wait(lock, []{return false;});
}