#include"../../include/fast_io.h"
#include<iostream>

struct floating_decimal_128 {
  __uint128_t mantissa;
  int32_t exponent;
  bool sign;
};

extern "C" struct floating_decimal_128 float_to_fd128(float f) noexcept;
extern "C" struct floating_decimal_128 double_to_fd128(double d) noexcept;
extern "C" struct floating_decimal_128 long_double_to_fd128(long double d) noexcept;
extern "C" int generic_to_chars(const struct floating_decimal_128 v, char* const result);
int main()
{
	std::array<char,100> array;
	long double d(1.244563);//wrong 1e2
	int n=generic_to_chars(long_double_to_fd128(d),array.data());
	array[n++]='\n';
	write(fast_io::out(),array.data(),array.data()+n);
	print("\n\n\n\n");
	println("my result:",d);

}