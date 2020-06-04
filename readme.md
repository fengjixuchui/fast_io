# fast_io

fast_io is a new C++20 library for extremely fast input/output and aims to replace iostream and cstdio. It is header-only (module only in the future) for easy inclusion in your project. It requires a capable C++20 compiler supporting concepts.

## Hello World

```cpp
#include<fast_io.h>

int main()
{
	print("Hello World!\n");
}
```

## Compiler Support
- GCC 11.
You can download the latest GCC compiler for windows here. https://bitbucket.org/ejsvifq_mabmip/mingw-gcc/src/master/ 
For Linux, you can watch this video to help you install the latest GCC easily. https://www.youtube.com/watch?v=qFToZjo2x24
- VS 19.26
- No Clang since Clang has not yet correctly support Concepts

## Platform Support
- Windows
- Linux
- BSD platforms (Including FreeBSD, NetBSD, OpenBSD and Mac)
- Todo: Webassembly

## Supported libc FILE* hacks platforms
- glibc
- MSVCRT
- Universal CRT
- BSD libc
- MUSL libc
- To do: Bionic

## Supported C++ standard library std::streambuf/std::filebuf hacks platforms
- GCC libstdc++
- LLVM libc++
- MSVC STL

## Design Goal

A general purpose I/O library to replace stdio.h and iostream

- As close to system call as possible.
- No default locale. It is optional.

### Safe

- No easily misused stuff like std::endl  
- No internal iomanip states (since it creates security issues)  
- Providing RAII for C FILE\*&POSIX fd&win32 HANDLE
- No dual error reporting mechanism. Exception as the ONLY error reporting mechanism.
- No std::error_code and std::system_error

### Easy to use

- Unicode/UTF-8 support  
- Compatible with C stdio and C++ iostream  
- Binary serialization for trivially copyable types and C++ standard library containers  
- All fast_io devices can be natively put in C++ containers. std::vector<fast_io::obuf_file> is valid  
- Basic/Lua/Python/etc format (print, scan). No support to C and C++ since they are security hazards.
- Static I/O manipulator
- Provide APIs to expose the internal implementation of C FILE* and C++ stream.

### Customizability

- Exception Safe & Exception neutral  
- Native Handle Interface  
- Extremely easy to support custom devices
- std::mutex mutex stream
- Compilation time open mode parse. Supports C style open mode and C++ style open mode.
- No traits_type and EOF
- Dynamic Type Support
- Multi Process
- Memory map
- Cryptography (Under construction) to replace openssl
- debugging IO
- GUI debugging IO
- Freestanding mode
- Round-trip floating point algorithm
- Network

## Post C++20 Plan
  1. Module support
  2. Coroutine support for async IO
  3. Improve and refactor code once [Zero-overhead deterministic exceptions](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p0709r0.pdf) are added to the standard

## Possible Improvements
  1. Compression/Decompression
  2. Interfaces for cloud computing algorithms like MapReduce

I'm aiming for this to be in the C++ standard library in the future :)

## Getting Started 
Please see examples in the examples folder.

compile option:
    
`g++ -o example example.cc -Ofast -std=c++20 -s`

## Documentation

See Wiki Page: https://github.com/expnkx/fast_io/wiki

## Benchmarks


1. I/O 10M integers

Goal: Print out ten million integers from 0 to 10M to file. Then reopen that file to scan back.

All benchmarks are in benchmarks/0000.10m_size_t/unit.

Notice: I modified libstdc++'s BUFSIZ 1048576 due to BUFSIZE is too small (512 bytes) for MinGW-W64, or it performs horribly.


| Platform                       |        Windows          |MinGW-W64 GCC 11.0.0   |   MSVCRT + libstdc++                                 |
|--------------------------------|-------------------------|-----------------------|------------------------------------------------------|
|                                                                                                                                         |

| Method                         |       Output time       |      Input time       |   Comment                                            |
|--------------------------------|-------------------------|-----------------------|------------------------------------------------------|
| stdio.h(fprintf/fscanf)        |      2.412987s          |   5.607791s           |                                                      |
| fstream                        |      0.462012s          |   1.192s              |                                                      |
| fstream with rdbuf.sputc trick |      0.33895s           |   1.170173s           |                                                      |
| fast_io::i/obuf_file           |      0.04903s           |   0.080996s           |                                                      |
| fast_io::i/obuf_file_mutex     |      0.146064s          |   0.113155s           | thread safe                                          |
| c_locale_i/obuf_file ("C")     |      0.065988s          |   0.086012s           | imbued with locale, locale "C"                       |
| c_locale_i/obuf_file local     |      0.153995s          |   Meaningless         | imbued with locale, locale ""                        |
| fmt::format_int+obuf_file      |      0.122999s          |   Meaningless         |                                                      |
| fmt::format_int+ofstream       |      0.209055s          |   Meaningless         |                                                      |
| fmt::format+ofstream           |      0.548s             |   Meaningless         | fmt makes things slower                              |
| fmt::print                     |      0.663996s          |   Meaningless         | fmt makes things slower                              |
| std::to_chars+obuf_file        |      0.12s              |   Meaningless         |                                                      |
| std::to_chars+ofstream         |      0.192s             |   Meaningless         |                                                      |
| fast_io::c_file_unlocked       |      0.098999s          |   0.126003s           | I hacked MSVCRT's FILE* implementation               |
| fast_io::c_file                |      0.298988s          |   0.318001s           | Thread Safe. I hacked MSVCRET's FILE* implementation |
| fast_io::filebuf_file          |      0.048999s          |   0.081s              | I hacked libstdc++'s streambuf/filebuf implementation|


Run the same test on MSVC 19.26.28805.


| Platform                       |       Windows           |  MSVC 19.26.28805     |  Install fmtlib wastes time of my life               |
|--------------------------------|-------------------------|-----------------------|------------------------------------------------------|
|                                                                                                                                         |

| Method                         |       Output time       |      Input time       |   Comment                                            |
|--------------------------------|-------------------------|-----------------------|------------------------------------------------------|
| stdio.h(fprintf/fscanf)        |      1.5353597s         |   1.4157233s          |                                                      |
| fstream                        |      3.6350262s         |   3.8420339s          |                                                      |
| fstream with rdbuf.sputc trick |      3.3735902s         |   3.8145566s          |                                                      |
| fast_io::i/obuf_file           |      0.0631433s         |   0.1030554s          |                                                      |
| fast_io::i/obuf_file_mutex     |      0.2190659s         |   0.2485886s          | thread safe                                          |
| std::to_chars+obuf_file        |      0.1641641s         |   Meaningless         |                                                      |
| std::to_chars+ofstream         |      0.5461922s         |   Meaningless         |                                                      |
| fast_io::c_file_unlocked       |      0.1102575s         |   0.2399757s          | I hacked Universal CRT's FILE* implementation        |
| fast_io::c_file                |      0.2034755s         |   0.2621148s          | Thread Safe. I hacked UCRT's FILE* implementation    |
| fast_io::filebuf_file          |      0.126661s          |   0.2378803s          | I hacked MSVC STL's streambuf/filebuf implementation |

Run the same test on GCC 11. glibc + libstdc++


| Platform                       |       Linux             |  GCC 11.0.0           |         glibc + libstdc++                            |
|--------------------------------|-------------------------|-----------------------|------------------------------------------------------|
|                                                                                                                                         |

| Method                         |       Output time       |      Input time       |   Comment                                            |
|--------------------------------|-------------------------|-----------------------|------------------------------------------------------|
| stdio.h(fprintf/fscanf)        |      0.532792935s       |   0.591907111s        |                                                      |
| fstream with rdbuf.sputc trick |      0.318896068s       |   0.429406415s        |                                                      |
| fast_io::i/obuf_file           |      0.050300857s       |   0.065372395s        |                                                      |
| fast_io::i/obuf_file_mutex     |      0.05290654s        |   0.083040518s        | thread safe                                          |
| c_locale_i/obuf_file ("C")     |      0.051939052s       |   0.065820056s        | imbued with locale, locale "C"                       |
| c_locale_i/obuf_file local     |      0.162406082s       |   Meaningless         | imbued with locale, locale ""                        |
| std::to_chars+obuf_file        |      0.115453587s       |   Meaningless         |                                                      |
| fmt::format_int+obuf_file      |      0.1183587s         |   Meaningless         |                                                      |
| fmt::format_int+ofstream       |      0.195914384s       |   Meaningless         |                                                      |
| fmt::format+ofstream           |      0.633590975s       |   Meaningless         | fmt makes things slower                              |
| fmt::print                     |      0.495270371s       |   Meaningless         | fmt makes things slower                              |
| boost::iostreams               |      0.400906063s       |   0.444717051s        | Using boost iostreams does not make your code faster |
| fast_io::c_file_unlocked       |      0.060076723s       |   0.073299716s        | I hacked glibc's FILE* implementation                |
| fast_io::c_file                |      0.092490191s       |   0.104545535s        | Thread Safe. I hacked glibc's FILE* implementation   |
| fast_io::filebuf_file          |      0.052251608s       |   0.06655806s         | I hacked libstdc++'s streambuf/filebuf implementation|

You can see fast_io can also boost the performance of existing facilities for 10x! Yes, it can even improve FILE* and fstream's performance for 10x depending on platforms since I use concepts to abstract them all. fmtlib actually slows down I/O performance. In general, fmtlib and charconv fucking sucks.

2. Output 10M double in round-trip mode with Ryu algorithm

We only perform this test for MSVC since only msvc's charconv implements it. Yes. fast_io defeats msvc's charconv for over 20% for running the same algorithm.

All benchmarks are in benchmarks/0001.10m_double/charconv.

Run the same test on MSVC 19.26.28805.


| Platform                       |       Windows           |  MSVC 19.26.28805     |  Install fmtlib wastes time of my life               |
|--------------------------------|-------------------------|-----------------------|------------------------------------------------------|
|                                                                                                                                         |

| Method                         |       Output time       |                           Comment                                            |
|--------------------------------|-------------------------|------------------------------------------------------------------------------|
| i/obuf_file                    |      0.4653818s         |                                                                              |
| charconv + obuf_file           |      0.6011s            |                                                                              |

3. Raw I/O Performance

All benchmarks are in benchmarks/0014.file_io/file_io.

Output 100000000x "Hello World\n"

Notice: I modified libstdc++'s std::filebuf's BUFSIZ to 1048576 due to BUFSIZE is too small (512 bytes) for MinGW-W64 or it performs horribly.



| Platform                       |        Windows          |MinGW-W64 GCC 11.0.0   |   MSVCRT + libstdc++                                 |
|--------------------------------|-------------------------|-----------------------|------------------------------------------------------|
|                                                                                                                                         |

| Method                         |       Output time       |                           Comment                                            |
|--------------------------------|-------------------------|------------------------------------------------------------------------------|
| fwrite                         |      2.524001s          |                                                                              |
| fstream                        |      1.013001s          |                                                                              |
| fast_io::obuf_file             |      0.437998s          |                                                                              |
| fast_io::obuf_file_mutex       |      1.371s             |Thread safe                                                                   |
| fast_io::c_file_unlocked       |      1.164997s          |I hacked MSVCRT's FILE* implementation                                        |
| fast_io::c_file                |      3.337945s          |Thread Safe. I hacked MSVCRT's FILE* implementation. Need further optimization|
| fast_io::filebuf_file          |      0.467001s          |I hacked libstdc++'s std::filebuf implementation                              |


| Platform                       |        Linux            |          GCC 11.0.0   |     glibc + libstdc++                                |
|--------------------------------|-------------------------|-----------------------|------------------------------------------------------|
|                                                                                                                                         |

| Method                         |       Output time       |                           Comment                                            |
|--------------------------------|-------------------------|------------------------------------------------------------------------------|
| fwrite                         |      1.457288317s       |                                                                              |
| fstream                        |      1.249783346s       |                                                                              |
| fast_io::obuf_file             |      0.494827134s       |                                                                              |
| fast_io::obuf_file_mutex       |      0.497138826s       |Thread safe                                                                   |
| fast_io::c_file_unlocked       |      0.687976666s       |I hacked glibc's FILE* implementation                                         |
| fast_io::c_file                |      0.910792697s       |Thread Safe. I hacked glibc's FILE* implementation                            |
| fast_io::filebuf_file          |      0.526955039s       |I hacked libstdc++'s std::filebuf implementation                              |


| Platform                       |        Windows          |  MSVC 19.26.28805     |      UCRT + MSVC STL                                 |
|--------------------------------|-------------------------|-----------------------|------------------------------------------------------|
|                                                                                                                                         |

| Method                         |       Output time       |                           Comment                                            |
|--------------------------------|-------------------------|------------------------------------------------------------------------------|
| fwrite                         |      3.3139122s         |                                                                              |
| fstream                        |      1.7184119s         |                                                                              |
| fast_io::obuf_file             |      0.7996034s         |                                                                              |
| fast_io::obuf_file_mutex       |      2.2949221s         |Thread safe. It looks like std::mutex is horribly slow for MSVC STL.          |
| fast_io::c_file_unlocked       |      1.2103924s         |I hacked UCRT's FILE* implementation                                          |
| fast_io::c_file                |      2.3604295s         |Thread Safe. I hacked UCRT's FILE* implementation                             |
| fast_io::filebuf_file          |      1.2805368s         |I hacked MSVC STL's std::filebuf implementation                               |


4. Binary Size
Just use the benchmark in benchmarks/0014.file_io/file_io.
That would introduce Ryu floating table for printing time, and I did not compile the code with -DFAST_IO_OPTIMIZE_SIZE. Or it would be nothing.
Dude, you should avoid stream as plague tbh. It is not healthy.


| Platform                       |        Windows          |MinGW-W64 GCC 11.0.0   |   MSVCRT + libstdc++ + static compile                |
|--------------------------------|-------------------------|-----------------------|------------------------------------------------------|
|                                                                                                                                         |

| Method                         |      Binary Size        |                           Comment                                            |
|--------------------------------|-------------------------|------------------------------------------------------------------------------|
| fstream                        |      925KB              |Use fstream is not good for your health since std::locale bloats your binary. |
| fast_io::obuf_file             |      155KB              |                                                                              |
| fast_io::c_file_unlocked       |      157KB              |I hacked MSVCRT's FILE* implementation                                        |
| fast_io::c_file                |      157KB              |Thread Safe. I hacked MSVCRT's FILE* implementation                           |
| fast_io::filebuf_file          |      933KB              |I hacked libstdc++'s std::filebuf implementation. C++ stream sucks            |
