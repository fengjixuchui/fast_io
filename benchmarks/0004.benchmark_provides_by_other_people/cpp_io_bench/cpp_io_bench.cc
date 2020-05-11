//https://cristianadam.eu/20160410/c-plus-plus-i-slash-o-benchmark/
#include"../../timer.h"
#include"../../../include/fast_io_device.h"
#include"../../../include/fast_io_legacy.h"
#include"../../../include/fast_io_third_party.h"
#include<map>
#include<vector>
#include<functional>

#ifndef O_BINARY
#define O_BINARY 0
#endif

struct measure
{
template<typename F, typename ...Args>
static auto ms(F func, Args&&... args)
{
	auto start = std::chrono::high_resolution_clock::now();
	func->second(std::forward<Args>(args)...);
	auto stop = std::chrono::high_resolution_clock::now();
	println(func->first,"\t",stop-start);	
	return stop - start;
}
};

void testCFileIO(const char* inFile, const char* outFile, std::vector<char>& inBuffer)
{
    FILE* in = ::fopen(inFile, "rb");
    if (!in)
    {
        println("Can't open output file: ", inFile);
        return;
    }
 
    FILE* out = ::fopen(outFile, "wb"); 
    if (!out)
    {
        println("Can't open output file: ", outFile);
        return;
    }
 
    fseek(in, 0, SEEK_END);
    size_t inFileSize = ::ftell(in);
    fseek(in, 0, SEEK_SET);
   
    for (size_t bytesLeft = inFileSize, chunk = inBuffer.size(); bytesLeft > 0; bytesLeft -= chunk)
    {
        if (bytesLeft < chunk)
        {
            chunk = bytesLeft;
        }
        
        ::fread(&inBuffer[0], 1, chunk, in);
        ::fwrite(&inBuffer[0], 1, chunk, out);
    }
  
    ::fclose(out);
    ::fclose(in);
}

void testCppIO(const char* inFile, const char* outFile, std::vector<char>& inBuffer)
{
    std::ifstream in(inFile, std::ifstream::binary);
    if (!in.is_open())
    {
        println("Can't open output file: ", inFile);
        return;
    }
 
    std::ofstream out(outFile, std::ofstream::binary);
    if (!out.is_open())
    {
        println("Can't open output file: ", outFile);
        return;
    }
 
    in.seekg(0, std::ifstream::end);
    size_t inFileSize = in.tellg();
    in.seekg(0, std::ifstream::beg);
   
    for (size_t bytesLeft = inFileSize, chunk = inBuffer.size(); bytesLeft > 0; bytesLeft -= chunk)
    {
        if (bytesLeft < chunk)
        {
            chunk = bytesLeft;
        }
        
        in.read(&inBuffer[0], chunk);
        out.write(&inBuffer[0], chunk);
    }
}

void testCppIO2(const char* inFile, const char* outFile, std::vector<char>&)
{
    std::ifstream in(inFile, std::ifstream::binary);
    if (!in.is_open())
    {
        println("Can't open output file: ", inFile);
        return;
    }
 
    std::ofstream out(outFile, std::ofstream::binary);
    if (!out.is_open())
    {
        println("Can't open output file: ", outFile);
        return;
    }
	out<<in.rdbuf();
}

void testPosixIO(const char* inFile, const char* outFile, std::vector<char>& inBuffer)
{
    int in = ::open(inFile, O_RDONLY | O_BINARY);
    if (in < 0)
    {
        println("Can't open output file: ", inFile);
        return;
    }

    int out = ::open(outFile, O_CREAT | O_WRONLY | O_BINARY, 0666);
    if (out < 0)
    {
        println("Can't open output file: ", outFile);
        return;
    }
 
    size_t inFileSize = ::lseek(in, 0, SEEK_END);
    ::lseek(in, 0, SEEK_SET);
   
    for (size_t bytesLeft = inFileSize, chunk = inBuffer.size(); bytesLeft > 0; bytesLeft -= chunk)
    {
        if (bytesLeft < chunk)
        {
            chunk = bytesLeft;
        }

        ::read(in, &inBuffer[0], chunk);
        ::write(out, &inBuffer[0], chunk);
    }

    ::close(out);
    ::close(in);
}

template<fast_io::input_stream input_stm,fast_io::output_stream output_stm>
void test_fast_io(std::string_view in_file,std::string_view out_file, std::vector<char>&)
{
	input_stm in(in_file,fast_io::open_interface<fast_io::open_mode::binary|fast_io::open_mode::in>);
	output_stm ot(out_file,fast_io::open_interface<fast_io::open_mode::binary|fast_io::open_mode::out>);
	transmit(ot,in);
}

void test_fast_io2(char const* inFile,char const* outFile, std::vector<char>&)
{
    std::ifstream in(inFile, std::ifstream::binary);
    if (!in.is_open())
    {
        println("Can't open output file: ", inFile);
        return;
    }
 
    std::ofstream out(outFile, std::ofstream::binary);
    if (!out.is_open())
    {
        println("Can't open output file: ", outFile);
        return;
    }
    fast_io::filebuf_io_observer fiob_out(out.rdbuf());
    fast_io::filebuf_io_observer fiob_in(in.rdbuf());
	transmit(fiob_out,fiob_in);
}


int main(int argc,char** argv)
{
    std::vector<std::string> args(argv, argv + argc);
    if (args.size() != 4)
    {
        println("Usage: ", args[0], " copy_method (c, posix, c++, c++2, "
#if defined(__WINNT__) || defined(_MSC_VER)
		"fast_io_win32_file, "
#endif
		"fast_io_posix_file, fast_io_c_file_unlocked, fast_io_c_file, fast_io_ibuf_file"
", fast_io_filebuf_io_observer"
#ifdef _AFXDLL
", fast_io_mfc_file"
#endif
") in_file number_of_times");
        return 1;
    }

    typedef std::map<std::string, std::function<void (const char*, const char*, std::vector<char>&)>> FuncMap;
    FuncMap funcMap { {"c", testCFileIO}, {"posix", testPosixIO}, {"c++", testCppIO},
	{"c++2", testCppIO2},
#if defined(__WINNT__) || defined(_MSC_VER)
	{"fast_io_win32_file",test_fast_io<fast_io::win32_file,fast_io::win32_file>},
#endif
	{"fast_io_posix_file",test_fast_io<fast_io::posix_file,fast_io::posix_file>},
	{"fast_io_c_file_unlocked",test_fast_io<fast_io::c_file_unlocked,fast_io::c_file_unlocked>},
	{"fast_io_c_file",test_fast_io<fast_io::c_file,fast_io::c_file>},
	{"fast_io_ibuf_file",test_fast_io<fast_io::ibuf_file,fast_io::native_file>}
	,{"fast_io_filebuf_io_observer",test_fast_io2}
#ifdef _AFXDLL
    ,{"fast_io_mfc_file",test_fast_io<fast_io::mfc_file,fast_io::mfc_file>}
#endif
};

    auto it = funcMap.find(args[1]);
    if (it != funcMap.end())
    {       
        std::vector<char> inBuffer(1024 * 1024);
        
        auto dest = args[2] + ".copy";
        ::unlink(dest.c_str());
        const auto times = std::stoul(args[3]);
        decltype(std::chrono::high_resolution_clock::now()-std::chrono::high_resolution_clock::now())
			total{};
        for (unsigned int i = 0; i < times; ++i)
        {
            total += measure::ms(it,args[2].c_str(), dest.c_str(), inBuffer);
            ::unlink(dest.c_str());
        }
		println("Average ", args[1], " I/O took: " , total / times);
    }
    else
    {
        println(fast_io::err,"Not supported copy method: " , args[1]);
    } 	
}