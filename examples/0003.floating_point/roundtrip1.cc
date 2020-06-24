#include"../../include/fast_io.h"
#include"../../include/fast_io_legacy.h"

template<std::floating_point F>
inline constexpr void test(std::string_view literal,F f)
{
	println(u8"literal:",literal,u8"->scientific:",fast_io::scientific(f),u8"\tfixed:",fast_io::fixed(f),u8"\tgeneral:",f);
}

int main()
{
	test("12342342347326444.0",12342342347326444.0);
	test("12342342347326445.0",12342342347326445.0);
/*
literal:12342342347326444.0->scientific:1.2342342347326444e+16  fixed:12342342347326444 general:12342342347326444
literal:12342342347326445.0->scientific:1.2342342347326444e+16  fixed:12342342347326444 general:12342342347326444

Since their value are the same, so we know any number between 12342342347326444.0 and 12342342347326445.0 must be the same round-trip value of 12342342347326444.0
*/
//let's verify it:
	test("12342342347326444.2351325732895712398517132895712395871329857123985712398571239857132895713289571238945712935781235",12342342347326444.2351325732895712398517132895712395871329857123985712398571239857132895713289571238945712935781235);
	test("12342342347326444.9999999999999999999999999999999999999999999999999999",12342342347326444.9999999999999999999999999999999999999999999999999999);
/*
literal:12342342347326444.2351325732895712398517132895712395871329857123985712398571239857132895713289571238945712935781235->scientific:1.2342342347326444e+16  fixed:12342342347326444 general:12342342347326444
literal:12342342347326444.9999999999999999999999999999999999999999999999999999->scientific:1.2342342347326444e+16  fixed:12342342347326444 general:12342342347326444
correct
*/
	test("12342342347326446.0",12342342347326446.0);
/*
literal:12342342347326445.0->scientific:1.2342342347326444e+16  fixed:12342342347326444 general:12342342347326444
literal:12342342347326446.0->scientific:1.2342342347326446e+16  fixed:12342342347326446 general:12342342347326446
Well the round trip value of 12342342347326446.0 is not the same as 12342342347326445.0:
Precise value of 12342342347326444.0 is 12342342347326444
Precise value of 12342342347326446.0 is 12342342347326446
We take the middle value of 12342342347326444 and 12342342347326446 is 12342342347326445
So, for any value x, if 12342342347326445<x<=12342342347326446, it must be the same round-trip value of 12342342347326446
for any value x, if 12342342347326444<=x<=12342342347326445, it must be the same round-trip value of 12342342347326445
https://baseconvert.com/ieee-754-floating-point
Binary representation of round-trip value of 12342342347326445.0 is
0 10000110100 0101111011001010010111000001101001111000000111110110. The last digit is even, so we don't take it.  5 should not be carried
*/
//let's verify it.
	test("12342342347326445.0",12342342347326445.0);
	test("12342342347326445.000000000000000000000000000000000000000000000000000000000000000001",12342342347326445.000000000000000000000000000000000000000000000000000000000000000001);
	test("12342342347326445.999999999999999999999999999999999999999999",12342342347326445.999999999999999999999999999999999999999999);
/*
literal:12342342347326445.000000000000000000000000000000000000000000000000000000000000000001->scientific:1.2342342347326446e+16 fixed:12342342347326446 general:12342342347326446
literal:12342342347326445.999999999999999999999999999999999999999999->scientific:1.2342342347326446e+16 fixed:12342342347326446 general:12342342347326446

After that we can just simply do a memcmp between the input string and 12342342347326445
*/
}