# fast_io

fast_io is a new C++20 library for extremely fast input/output and aims to replace iostream and cstdio. It is header-only (module only in the future) for easy inclusion in your project. It requires a capable C++20 compiler supporting concepts.

## Compiler Support
- VS 16.3
- Clang 10.0
- GCC 10

## Platform Support
- Windows
- Linux
- MacOS
- Android

## Design Goal

### Fast. As close to system call as possible.

- Locale support optional  
- Zero copy IO

### Safe

- No easily misused stuff like std::endl  
- No internal iomanip states (since it creates security issues)  
- Providing RAII for FILE\*&POSIX file id

### Easy to use

- Unicode/UTF-8 support  
- Compatible with C stdio and C++ iostream  
- Binary serialization for trivially copyable types and C++ standard library containers  
- All fast_io devices can be natively put in C++ containers. std::vector<fast_io::obuf> is valid  
- Support C style io format (fprint). Basic/Lua/Python/etc format (print, scan).

### Customizability

- Exception Safe & Exception neutral  
- Native Handle Interface  
- Extremely easy to support custom devices
- std::mutex mutex stream
- Compilation time open mode parse. Supports C style open mode and C++ style open mode.
- No traits_type and EOF
- Dynamic Type Support
- Pipe line support
- Cryptography (Under construction) to replace openssl
- debugging IO

## Post C++20 Plan
  1. Module support
  2. Coroutine support for async IO
  3. Improve and refactor code once [Zero-overhead deterministic exceptions](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p0709r0.pdf) are added to the standard
  4. Network handle support with coroutine. (NOT ASIO library)
  5. Partial freestanding mode

## Possible Improvements
  1. Compression/Decompression
  2. Interfaces for cloud computing algorithms like MapReduce

I'm aiming for this to be in the C++ standard library in the future :)

## Getting Started 
Please see examples in the examples folder.

compile option:
    
`g++ -o example example.cc -O2 -std=c++2a -fconcepts`

## Documentation

./doxygen/html/index.html

Since C++ 20 has not been released. No standard supporting libraries for concepts, which means a lot of Concepts Definitions are ugly. It will be changed after C++ 20 is officially published.

## Benchmarks

output 10000000 size_t to file

/fast_io/tests# ./i

| Method                     | Time        |
|----------------------------|-------------|
| std::FILE*:                | 1.03459230s |
| std::ofstream:             | 0.59182820s |
| std::ofstream with tricks: | 0.39233580s |
| obuf:                      | 0.13328110s |
| obuf_mutex:                | 0.13685030s |

input 10000000 size_t from file

fast_io/tests ./j

| Method         | Time        |
|----------------|-------------|
| std::FILE*:    | 1.04546250s |
| std::ifstream: | 0.47838780s |
| ibuf:          | 0.08077780s |

### Windows:
#### Output:

output_10M_size_t.cc -O2 -std=c++2a -fconcepts

| Method                     | Time        |
|----------------------------|-------------|
| std::FILE*:                | 2.26901100s |
| std::ofstream:             | 1.03628600s |
| std::ofstream with tricks: | 0.84219500s |
| obuf:                      | 0.13401100s |
| dynamic obuf:              | 0.13586300s |
| iobuf_dynamic native_file: | 0.13000100s |
| obuf_mutex:                | 0.15303500s |

#### Input:

input_10M_size_t.cc -O2 -std=c++2a -fconcepts

| Method                              | Time        |
|-------------------------------------|-------------|
| std::FILE*:                         | 5.53888200s |
| std::ifstream:                      | 1.27124600s |
| ibuf:                               | 0.07400200s |
| dynamic standard input stream ibuf: | 0.08899900s |
| ibuf_dynamic inative_file:          | 0.07600900s |


#### Updated benchmark with trunk gcc

I did some optimizations to my fast_io library. Now there is NO reason to use charconv any more. It is insecure and the APIs are terrible. I hope isocpp would deprecate charconv in the future.

fast_io/examples/

| Method                                 | Time        |
|----------------------------------------|-------------|
| std::FILE*:                            | 0.56558740s |
| std::ofstream:                         | 0.57254780s |
| std::ofstream with tricks:             | 0.37952570s |
| std::to_chars + ofstream rdbuf tricks: | 0.16530360s |
| std::to_chars + obuf:                  | 0.12705310s |
| obuf:                                  | 0.07508470s |
| obuf text:                             | 0.13640670s |
| steam_view for ofstream:               | 0.35196200s |
| steambuf_view for ofstream:            | 0.15705550s |
| obuf ucs_view:                         | 0.15152370s |
| obuf_mutex:                            | 0.08375820s |
| fsync:                                 | 0.17738210s |
| speck128/128:                          | 0.26626790s |
