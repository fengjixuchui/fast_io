#include"../../include/fast_io.h"
#include"../../include/fast_io_legacy.h"

template<std::floating_point F>
inline constexpr void test(std::string_view literal,F f)
{
	println(fast_io::c_stdout,u8"literal:",literal,u8"->scientific:",fast_io::scientific(f),u8"\tfixed:",fast_io::fixed(f),u8"\tgeneral:",f);
}

int main()
{
	test("1.2342342347326444",1.2342342347326444);
	test("1.2342342347326445",1.2342342347326445);
/*
literal:1.2342342347326444->scientific:1.2342342347326445e+00   fixed:1.2342342347326445        general:1.2342342347326445
literal:1.2342342347326445->scientific:1.2342342347326445e+00   fixed:1.2342342347326445        general:1.2342342347326445

Since their value are the same, so we know any number between 1.2342342347326444 and 1.2342342347326445 must be the same round-trip value of 12342342347326444
*/
//let's verify it:
	test("1.23423423473264442351325732895712398517132895712395871329857123985712398571239857132895713289571238945712935781235",12342342347326444.2351325732895712398517132895712395871329857123985712398571239857132895713289571238945712935781235);
	test("1.23423423473264449999999999999999999999999999999999999999999999999999",12342342347326444.9999999999999999999999999999999999999999999999999999);
/*
literal:12342342347326444.2351325732895712398517132895712395871329857123985712398571239857132895713289571238945712935781235->scientific:1.2342342347326444e+16  fixed:12342342347326444 general:12342342347326444
literal:12342342347326444.9999999999999999999999999999999999999999999999999999->scientific:1.2342342347326444e+16	fixed:12342342347326444 general:12342342347326444
correct
*/
	test("1.2342342347326446",1.2342342347326446);
/*
literal:1.2342342347326446->scientific:1.2342342347326447e+00   fixed:1.2342342347326447        general:1.2342342347326447
Well the round trip value of 12342342347326446.0 is not the same as 12342342347326445.0:
Precise value of 1.2342342347326445 is 1.2342342347326444862432026638998650014400482177734375
Precise value of 1.2342342347326447 is 1.2342342347326447082878075889311730861663818359375
We take the middle value of 1.2342342347326444862432026638998650014400482177734375 and 1.2342342347326447082878075889311730861663818359375 is 1.23423423473264459726550512641551904380321502685546875
So, for any value x, if 1.2342342347326445<=x<1.23423423473264459726550512641551904380321502685546875, it must be the same round-trip value of 1.2342342347326445
for any value x, if 1.23423423473264459726550512641551904380321502685546875<=x<=1.2342342347326446, it must be the same round-trip value of 1.2342342347326446

Binary representation of round-trip value of 1.2342342347326445 is 0 01111111111 0011101111110110110001100101100111000111110000010111
The last digit is odd, so we take it.5 should be carried
*/
//let's verify it.
	test("1.23423423473264459726550512641551904380321502685546874999999999999999999999999999999",1.23423423473264459726550512641551904380321502685546874999999999999999999999999999999);
	test("1.23423423473264459726550512641551904380321502685546875",1.23423423473264459726550512641551904380321502685546875);
	test("1.2342342347326445972655051264155190438032150268554687500000000000000000000000000000000001",1.2342342347326445972655051264155190438032150268554687500000000000000000000000000000000001);

/*
literal:1.23423423473264459726550512641551904380321502685546874999999999999999999999999999999->scientific:1.2342342347326445e+00        fixed:1.2342342347326445        general:1.2342342347326445
literal:1.23423423473264459726550512641551904380321502685546875->scientific:1.2342342347326447e+00      fixed:1.2342342347326447        general:1.2342342347326447
literal:1.2342342347326445972655051264155190438032150268554687500000000000000000000000000000000001->scientific:1.2342342347326447e+00   fixed:1.2342342347326447        general:1.2342342347326447

After that we can just simply do a memcmp between the first 54 characters of the input string and 123423423473264459726550512641551904380321502685546875

KISS. No need complex multiprecision algorithm. The middle value can be calculated by doing with strings and then we multiply 5.
*/
}