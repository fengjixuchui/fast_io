/*
https://stackoverflow.com/questions/26095160/why-are-stdfstreams-so-slow
*/

#include <stdio.h>
#include <chrono>
#include <fstream>
#include <iostream>
#include <functional>
#include <memory>
#ifndef __clang__
#include"../../../include/fast_io_device.h"
#endif

void measure(const std::string& test, std::function<void()> function)
{
    auto start_time = std::chrono::high_resolution_clock::now();

    function();

    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start_time);
    std::cout<<test<<" "<<static_cast<double>(duration.count()) * 0.000001<<" ms"<<std::endl;
}

#define BUFFER_SIZE (1024 * 1024 * 1024)

int main(int argc, const char * argv[])
{
    std::unique_ptr<char[]> buffer_up (new char[BUFFER_SIZE]);
    char* buffer{buffer_up.get()};
    memset(buffer, 123, BUFFER_SIZE);

    measure("FILE* write", [buffer]()
    {
        FILE* file = fopen("test_file_write.txt", "wb");
        fwrite(buffer, 1, BUFFER_SIZE, file);
        fclose(file);
    });
    measure("FILE* read", [buffer]()
    {
        FILE* file = fopen("test_file_read.txt", "rb");
        fread(buffer, 1, BUFFER_SIZE, file);
        fclose(file);
    });
    measure("fstream write", [buffer]()
    {
        std::ofstream stream("test_stream_write.txt", std::ios::binary);
        stream.write(buffer, BUFFER_SIZE);
    });
    measure("fstream read", [buffer]()
    {
        std::ifstream stream("test_stream_read.txt", std::ios::binary);
        stream.read(buffer, BUFFER_SIZE);
    });
#ifndef __clang__
    measure("fast_io::obuf_file write", [buffer]()
    {
	fast_io::obuf_file obf("test_fast_io_obuf_file_write.txt");
        write(obf,buffer, buffer+BUFFER_SIZE);
    });
    measure("fast_io::ibuf_file read", [buffer]()
    {
	fast_io::ibuf_file ibf("test_fast_io_ibuf_file_read.txt");
        read(ibf,buffer,buffer+BUFFER_SIZE);
    });

    measure("fast_io::onative_file write", [buffer]()
    {
	fast_io::onative_file onf("test_fast_io_obuf_file_write.txt");
        write(onf,buffer, buffer+BUFFER_SIZE);
    });
    measure("fast_io::inative_file read", [buffer]()
    {
	fast_io::inative_file inf("test_fast_io_inative_file_read.txt");
        read(inf,buffer,buffer+BUFFER_SIZE);
    });
#endif
}