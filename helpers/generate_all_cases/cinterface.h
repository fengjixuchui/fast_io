void cxx_fast_io_fp_print_char(FILE*,char);
void cxx_fast_io_fp_println_char(FILE*,char);
void cxx_fast_io_fp_unlocked_print_char(FILE*,char);
void cxx_fast_io_fp_unlocked_println_char(FILE*,char);
void cxx_fast_io_fp_print_short(FILE*,short);
void cxx_fast_io_fp_println_short(FILE*,short);
void cxx_fast_io_fp_unlocked_print_short(FILE*,short);
void cxx_fast_io_fp_unlocked_println_short(FILE*,short);
void cxx_fast_io_fp_print_int(FILE*,int);
void cxx_fast_io_fp_println_int(FILE*,int);
void cxx_fast_io_fp_unlocked_print_int(FILE*,int);
void cxx_fast_io_fp_unlocked_println_int(FILE*,int);
void cxx_fast_io_fp_print_long(FILE*,long);
void cxx_fast_io_fp_println_long(FILE*,long);
void cxx_fast_io_fp_unlocked_print_long(FILE*,long);
void cxx_fast_io_fp_unlocked_println_long(FILE*,long);
void cxx_fast_io_fp_print_long_long(FILE*,long long);
void cxx_fast_io_fp_println_long_long(FILE*,long long);
void cxx_fast_io_fp_unlocked_print_long_long(FILE*,long long);
void cxx_fast_io_fp_unlocked_println_long_long(FILE*,long long);
void cxx_fast_io_fp_print_char_unsigned(FILE*,char unsigned);
void cxx_fast_io_fp_println_char_unsigned(FILE*,char unsigned);
void cxx_fast_io_fp_unlocked_print_char_unsigned(FILE*,char unsigned);
void cxx_fast_io_fp_unlocked_println_char_unsigned(FILE*,char unsigned);
void cxx_fast_io_fp_print_short_unsigned(FILE*,short unsigned);
void cxx_fast_io_fp_println_short_unsigned(FILE*,short unsigned);
void cxx_fast_io_fp_unlocked_print_short_unsigned(FILE*,short unsigned);
void cxx_fast_io_fp_unlocked_println_short_unsigned(FILE*,short unsigned);
void cxx_fast_io_fp_print_int_unsigned(FILE*,int unsigned);
void cxx_fast_io_fp_println_int_unsigned(FILE*,int unsigned);
void cxx_fast_io_fp_unlocked_print_int_unsigned(FILE*,int unsigned);
void cxx_fast_io_fp_unlocked_println_int_unsigned(FILE*,int unsigned);
void cxx_fast_io_fp_print_long_unsigned(FILE*,long unsigned);
void cxx_fast_io_fp_println_long_unsigned(FILE*,long unsigned);
void cxx_fast_io_fp_unlocked_print_long_unsigned(FILE*,long unsigned);
void cxx_fast_io_fp_unlocked_println_long_unsigned(FILE*,long unsigned);
void cxx_fast_io_fp_print_long_long_unsigned(FILE*,long long unsigned);
void cxx_fast_io_fp_println_long_long_unsigned(FILE*,long long unsigned);
void cxx_fast_io_fp_unlocked_print_long_long_unsigned(FILE*,long long unsigned);
void cxx_fast_io_fp_unlocked_println_long_long_unsigned(FILE*,long long unsigned);
void cxx_fast_io_fp_print_double(FILE*,double);
void cxx_fast_io_fp_println_double(FILE*,double);
void cxx_fast_io_fp_unlocked_print_double(FILE*,double);
void cxx_fast_io_fp_unlocked_println_double(FILE*,double);
void cxx_fast_io_fp_print_c_str(FILE*,char const*);
void cxx_fast_io_fp_println_c_str(FILE*,char const*);
void cxx_fast_io_fp_unlocked_print_c_str(FILE*,char const*);
void cxx_fast_io_fp_unlocked_println_c_str(FILE*,char const*);


#define PRINT(fp,x) _Generic((x) ,char:cxx_fast_io_fp_print_char\
,short:cxx_fast_io_fp_print_short\
,int:cxx_fast_io_fp_print_int\
,long:cxx_fast_io_fp_print_long\
,long long:cxx_fast_io_fp_print_long_long\
,char unsigned:cxx_fast_io_fp_print_char_unsigned\
,short unsigned:cxx_fast_io_fp_print_short_unsigned\
,int unsigned:cxx_fast_io_fp_print_int_unsigned\
,long unsigned:cxx_fast_io_fp_print_long_unsigned\
,long long unsigned:cxx_fast_io_fp_print_long_long_unsigned\
,double:cxx_fast_io_fp_print_double\
,char const*:cxx_fast_io_fp_print_c_str)(fp,x)

#define PRINTLN(fp,x) _Generic((x) ,char:cxx_fast_io_fp_println_char\
,short:cxx_fast_io_fp_println_short\
,int:cxx_fast_io_fp_println_int\
,long:cxx_fast_io_fp_println_long\
,long long:cxx_fast_io_fp_println_long_long\
,char unsigned:cxx_fast_io_fp_println_char_unsigned\
,short unsigned:cxx_fast_io_fp_println_short_unsigned\
,int unsigned:cxx_fast_io_fp_println_int_unsigned\
,long unsigned:cxx_fast_io_fp_println_long_unsigned\
,long long unsigned:cxx_fast_io_fp_println_long_long_unsigned\
,double:cxx_fast_io_fp_println_double\
,char const*:cxx_fast_io_fp_println_c_str)(fp,x)

#define PRINT_UNLOCKED(fp,x) _Generic((x) ,char:cxx_fast_io_fp_print_unlocked_char\
,short:cxx_fast_io_fp_print_unlocked_short\
,int:cxx_fast_io_fp_print_unlocked_int\
,long:cxx_fast_io_fp_print_unlocked_long\
,long long:cxx_fast_io_fp_print_unlocked_long_long\
,char unsigned:cxx_fast_io_fp_print_unlocked_char_unsigned\
,short unsigned:cxx_fast_io_fp_print_unlocked_short_unsigned\
,int unsigned:cxx_fast_io_fp_print_unlocked_int_unsigned\
,long unsigned:cxx_fast_io_fp_print_unlocked_long_unsigned\
,long long unsigned:cxx_fast_io_fp_print_unlocked_long_long_unsigned\
,double:cxx_fast_io_fp_print_unlocked_double\
,char const*:cxx_fast_io_fp_print_unlocked_c_str)(fp,x)

#define PRINTLN_UNLOCKED(fp,x) _Generic((x) ,char:cxx_fast_io_fp_unlocked_println_char\
,short:cxx_fast_io_fp_unlocked_println_short\
,int:cxx_fast_io_fp_unlocked_println_int\
,long:cxx_fast_io_fp_unlocked_println_long\
,long long:cxx_fast_io_fp_unlocked_println_long_long\
,char unsigned:cxx_fast_io_fp_unlocked_println_char_unsigned\
,short unsigned:cxx_fast_io_fp_unlocked_println_short_unsigned\
,int unsigned:cxx_fast_io_fp_unlocked_println_int_unsigned\
,long unsigned:cxx_fast_io_fp_unlocked_println_long_unsigned\
,long long unsigned:cxx_fast_io_fp_unlocked_println_long_long_unsigned\
,double:cxx_fast_io_fp_unlocked_println_double\
,char const*:cxx_fast_io_fp_unlocked_println_c_str)(fp,x)