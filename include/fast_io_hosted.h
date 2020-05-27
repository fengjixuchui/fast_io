#pragma once
/*
https://en.cppreference.com/w/cpp/freestanding
There are two kinds of implementations defined by the C++ standard:
hosted and freestanding implementations.
For hosted implementations the set of standard library headers required by the C++ standard is much larger than for freestanding ones.
*/
//fast_io_hosted defines what we could use in a hosted environment.
#include"fast_io_freestanding.h"
#include"fast_io_hosted/mmap.h"
#include"fast_io_hosted/platforms/native.h"
#include"fast_io_hosted/omap.h"
#include"fast_io_hosted/iomutex.h"
#include"fast_io_hosted/chrono.h"
#include"fast_io_hosted/process/native.h"
#include"fast_io_hosted/global_new.h"
#include"fast_io_hosted/parallel.h"
#if __cpp_impl_coroutine >= 201902
#include<coroutine>
#include"fast_io_hosted/async_coro.h"
#endif

//#include<clocale>
//#include"fast_io_hosted/posix_locale.h"
