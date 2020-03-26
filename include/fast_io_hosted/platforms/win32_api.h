#pragma once
//Referenced from : https://github.com/ned14/status-code/blob/master/include/win32_code.hpp

namespace fast_io::win32
{
extern "C"
{
std::uint32_t __stdcall GetLastError(void);
void * __stdcall LoadLibraryW(wchar_t const*);

// Used to retrieve a locale-specific message string for some error code
std::uint32_t __stdcall FormatMessageA(std::uint32_t, void const*, std::uint32_t,std::uint32_t, char*, std::uint32_t, void /*va_list*/ *);

struct security_attributes
{
	std::uint32_t nLength;
	void* lpSecurityDescriptor;
	int bInheritHandle;
};

int __stdcall CloseHandle(void*);

void* __stdcall CreateFileW(wchar_t const*,std::uint32_t,std::uint32_t,security_attributes*,std::uint32_t,std::uint32_t,void*);

void* __stdcall CreateFileA(char const*,std::uint32_t,std::uint32_t,security_attributes*,std::uint32_t,std::uint32_t,void*);

struct overlapped
{
#if defined(_WIN64) || defined(__MINGW64__)
	std::uint64_t Internal,InternalHigh;
#else
	std::uint32_t Internal,InternalHigh;
#endif
union
{
struct
{
std::uint32_t Offset;
std::uint32_t OffsetHigh;
} DUMMYSTRUCTNAME;
void* Pointer;
}
DUMMYUNIONNAME;
void* hEvent;
};
struct transmit_file_buffer
{
void* Head;
std::uint32_t  HeadLength;
void* Tail;
std::uint32_t  TailLength;
};

void* __stdcall CreateFileMappingW(void*,security_attributes*,std::uint32_t,std::uint32_t,std::uint32_t,wchar_t const*);

void* __stdcall MapViewOfFile(void*,std::uint32_t,std::uint32_t,std::uint32_t,std::size_t);

int __stdcall SetEndOfFile(void*);

int __stdcall UnmapViewOfFile(void const*);

int __stdcall WriteFile(void*,void const*,std::uint32_t,std::uint32_t*,overlapped*);

int __stdcall ReadFile(void*,void const*,std::uint32_t,std::uint32_t*,overlapped*);

int __stdcall SetFilePointerEx(void*,std::int64_t,std::int64_t*,std::uint32_t);

void* __stdcall GetCurrentProcess();

int __stdcall DuplicateHandle(void*,void*,void*,void**,std::uint32_t,int,std::uint32_t);

void* __stdcall GetStdHandle(std::uint32_t);

int __stdcall CreatePipe(void**,void**,security_attributes*,std::uint32_t);

int __stdcall FreeLibrary(void*);

int __stdcall TransmitFile(std::uintptr_t,void*,std::uint32_t,std::uint32_t,overlapped*,transmit_file_buffer*,std::uint32_t);

using farproc = intptr_t(__stdcall*)();

farproc __stdcall GetProcAddress(void*,char const*);

void* __stdcall GetModuleHandleW(wchar_t const*);

int __stdcall AllocConsole();

std::uint32_t __stdcall WaitForSingleObject(void*,std::uint32_t);

std::uint32_t __stdcall ResumeThread(void*);

struct startupinfo
{
std::uint32_t cb;
wchar_t* lpReserved;
wchar_t* lpDesktop;
wchar_t* lpTitle;
std::uint32_t dwX;
std::uint32_t dwY;
std::uint32_t dwXSize;
std::uint32_t dwYSize;
std::uint32_t dwXCountChars;
std::uint32_t dwYCountChars;
std::uint32_t dwFillAttribute;
std::uint32_t dwFlags;
std::uint16_t wShowWindow;
std::uint16_t cbReserved2;
int* lpReserved2;
void* hStdInput;
void* hStdOutput;
void* hStdError;
};
struct process_information
{
void* hProcess;
void* hThread;
std::uint32_t dwProcessId;
std::uint32_t dwThreadId;
};
int __stdcall CreateProcessA(char const*,char const*,
void*,void*,int,uint32_t,
void* lpEnvironment,
char const* lpCurrentDirectory,
startupinfo* lpStartupInfo,
process_information* lpProcessInformation);


int __stdcall GetHandleInformation(void*,std::uint32_t*);
int __stdcall SetHandleInformation(void*,std::uint32_t,std::uint32_t);
int __stdcall GetFileSizeEx(void*,std::uint64_t*);
/*
struct win32_memory_range_entry
{
void*  VirtualAddress;
std::size_t NumberOfBytes;
};
int __stdcall PrefetchVirtualMemory(void*,std::size_t,win32_memory_range_entry*,std::uint32_t flags);*/
}


}