#pragma once

//The problem is that std::exception/std::system_error reports message with char const* instead of char8_t const*
//To prevent compiler or C locale screw up this library, we have to add a layer for EBCDIC.
//Also we have to use system call on Linux systems directly to avoid issue for introducing stupid libc runtime
//However, this can also be used for code converting from EBCDIC to ASCII or vice versa.

//https://www.ibm.com/support/knowledgecenter/en/SSZJPZ_11.3.0/com.ibm.swg.im.iis.ds.parjob.adref.doc/topics/r_deeadvrf_ASCII_to_EBCDIC.html
//https://www.ibm.com/support/knowledgecenter/en/SSZJPZ_11.3.0/com.ibm.swg.im.iis.ds.parjob.adref.doc/topics/r_deeadvrf_EBCDIC_to_ASCII.html

namespace fast_io
{

class ascii_to_ebcdic
{
public:
template<std::integral I>
inline constexpr I operator()(I ch) noexcept
{
switch(static_cast<std::make_unsigned_t<I>>(ch))
{
	case 0x00:return 0x00;
	case 0x01:return 0x01;
	case 0x02:return 0x02;
	case 0x03:return 0x03;
	case 0x04:return 0x1A;
	case 0x05:return 0x09;
	case 0x06:return 0x1A;
	case 0x07:return 0x7F;
	case 0x08:return 0x1A;
	case 0x09:return 0x1A;
	case 0x0A:return 0x1A;
	case 0x0B:return 0x0B;
	case 0x0C:return 0x0C;
	case 0x0D:return 0x0D;
	case 0x0E:return 0x0E;
	case 0x0F:return 0x0F;
	case 0x10:return 0x10;
	case 0x11:return 0x11;
	case 0x12:return 0x12;
	case 0x13:return 0x13;
	case 0x14:return 0x3C;
	case 0x15:return 0x3D;
	case 0x16:return 0x32;
	case 0x17:return 0x26;
	case 0x18:return 0x18;
	case 0x19:return 0x19;
	case 0x1A:return 0x3F;
	case 0x1B:return 0x27;
	case 0x1C:return 0x1C;
	case 0x1D:return 0x1D;
	case 0x1E:return 0x1E;
	case 0x1F:return 0x1F;
	case 0x20:return 0x40;
	case 0x21:return 0x4F;
	case 0x22:return 0x7F;
	case 0x23:return 0x7B;
	case 0x24:return 0x5B;
	case 0x25:return 0x6C;
	case 0x26:return 0x50;
	case 0x27:return 0x7D;
	case 0x28:return 0x4D;
	case 0x29:return 0x5D;
	case 0x2A:return 0x5C;
	case 0x2B:return 0x4E;
	case 0x2C:return 0x6B;
	case 0x2D:return 0x60;
	case 0x2E:return 0x4B;
	case 0x2F:return 0x61;
	case 0x30:return 0xF0;
	case 0x31:return 0xF1;
	case 0x32:return 0xF2;
	case 0x33:return 0xF3;
	case 0x34:return 0xF4;
	case 0x35:return 0xF5;
	case 0x36:return 0xF6;
	case 0x37:return 0xF7;
	case 0x38:return 0xF8;
	case 0x39:return 0xF9;
	case 0x3A:return 0x7A;
	case 0x3B:return 0x5E;
	case 0x3C:return 0x4C;
	case 0x3D:return 0x7E;
	case 0x3E:return 0x6E;
	case 0x3F:return 0x6F;
	case 0x40:return 0x7C;
	case 0x41:return 0xC1;
	case 0x42:return 0xC2;
	case 0x43:return 0xC3;
	case 0x44:return 0xC4;
	case 0x45:return 0xC5;
	case 0x46:return 0xC6;
	case 0x47:return 0xC7;
	case 0x48:return 0xC8;
	case 0x49:return 0xC9;
	case 0x4A:return 0xD1;
	case 0x4B:return 0xD2;
	case 0x4C:return 0xD3;
	case 0x4D:return 0xD4;
	case 0x4E:return 0xD5;
	case 0x4F:return 0xD6;
	case 0x50:return 0xD7;
	case 0x51:return 0xD8;
	case 0x52:return 0xD9;
	case 0x53:return 0xE2;
	case 0x54:return 0xE3;
	case 0x55:return 0xE4;
	case 0x56:return 0xE5;
	case 0x57:return 0xE6;
	case 0x58:return 0xE7;
	case 0x59:return 0xE8;
	case 0x5A:return 0xE9;
	case 0x5B:return 0x4A;
	case 0x5C:return 0xE0;
	case 0x5D:return 0x5A;
	case 0x5E:return 0x5F;
	case 0x5F:return 0x6D;
	case 0x60:return 0x79;
	case 0x61:return 0x81;
	case 0x62:return 0x82;
	case 0x63:return 0x83;
	case 0x64:return 0x84;
	case 0x65:return 0x85;
	case 0x66:return 0x86;
	case 0x67:return 0x87;
	case 0x68:return 0x88;
	case 0x69:return 0x89;
	case 0x6A:return 0x91;
	case 0x6B:return 0x92;
	case 0x6C:return 0x93;
	case 0x6D:return 0x94;
	case 0x6E:return 0x95;
	case 0x6F:return 0x96;
	case 0x70:return 0x97;
	case 0x71:return 0x98;
	case 0x72:return 0x99;
	case 0x73:return 0xA2;
	case 0x74:return 0xA3;
	case 0x75:return 0xA4;
	case 0x76:return 0xA5;
	case 0x77:return 0xA6;
	case 0x78:return 0xA7;
	case 0x79:return 0xA8;
	case 0x7A:return 0xA9;
	case 0x7B:return 0xC0;
	case 0x7C:return 0x6A;
	case 0x7D:return 0xD0;
	case 0x7E:return 0xA1;
	case 0x7F:return 0x07;
	default:return 0x3F;
}
}
template<buffer_output_stream output,std::contiguous_iterator Iter>
inline constexpr auto write_proxy(output& out,Iter begin,Iter end)
{
	for(auto iter(begin);iter!=end;++iter)
		*iter=operator()(*iter);
	write(out,begin,end);
	return end;
}
template<buffer_input_stream input,std::contiguous_iterator Iter>
inline constexpr Iter read_proxy(input& in,Iter b,Iter e)
{
//This is basically text stream
	for(;b!=e;++b)
	{
		auto ch(front<1>(in));
		if(!ch.second)
			break;
		if(ch.first==u8'\r')
		{
			if(!ireserve(in,2)||begin(in)+1==end(in))
				return b;
			if(begin(in)[1]==u8'\n')
			{
				*b=0x15;
				in+=2;
				continue;
			}
		}
		*b=operator()(ch.first);
		++in;
	}
	return b;
}
};

class ebcdic_to_ascii
{
public:
template<std::integral T>
inline constexpr T operator()(T ch)
{
switch(static_cast<std::make_unsigned_t<T>>(ch))
{
	case 0x00:return 0x00;
	case 0x01:return 0x01;
	case 0x02:return 0x02;
	case 0x03:return 0x03;
	case 0x05:return 0x09;
	case 0x07:return 0x7F;
	case 0x0B:return 0x0B;
	case 0x0C:return 0x0C;
	case 0x0D:return 0x0D;
	case 0x0E:return 0x0E;
	case 0x0F:return 0x0F;
	case 0x10:return 0x10;
	case 0x11:return 0x11;
	case 0x12:return 0x12;
	case 0x13:return 0x13;
	case 0x16:return 0x08;
	case 0x18:return 0x18;
	case 0x19:return 0x19;
	case 0x1C:return 0x1C;
	case 0x1D:return 0x1D;
	case 0x1E:return 0x1E;
	case 0x1F:return 0x1F;
	case 0x25:return 0x0A;
	case 0x26:return 0x17;
	case 0x27:return 0x1B;
	case 0x2D:return 0x05;
	case 0x2E:return 0x06;
	case 0x2F:return 0x07;
	case 0x32:return 0x16;
	case 0x37:return 0x04;
	case 0x3C:return 0x14;
	case 0x3D:return 0x15;
	case 0x40:return 0x20;
	case 0x4A:return 0x5B;
	case 0x4B:return 0x2E;
	case 0x4C:return 0x3C;
	case 0x4D:return 0x28;
	case 0x4E:return 0x2B;
	case 0x4F:return 0x21;
	case 0x50:return 0x26;
	case 0x5A:return 0x5D;
	case 0x5B:return 0x24;
	case 0x5C:return 0x2A;
	case 0x5D:return 0x29;
	case 0x5E:return 0x3B;
	case 0x5F:return 0x5E;
	case 0x60:return 0x2D;
	case 0x6A:return 0x7C;
	case 0x6B:return 0x2C;
	case 0x6C:return 0x25;
	case 0x6D:return 0x5F;
	case 0x6E:return 0x3E;
	case 0x6F:return 0x3F;
	case 0x79:return 0x60;
	case 0x7A:return 0x3A;
	case 0x7B:return 0x23;
	case 0x7C:return 0x40;
	case 0x7D:return 0x27;
	case 0x7E:return 0x3D;
	case 0x7F:return 0x22;
	case 0x81:return 0x61;
	case 0x82:return 0x62;
	case 0x83:return 0x63;
	case 0x84:return 0x64;
	case 0x85:return 0x65;
	case 0x86:return 0x66;
	case 0x87:return 0x67;
	case 0x88:return 0x68;
	case 0x89:return 0x69;
	case 0x91:return 0x6A;
	case 0x92:return 0x6B;
	case 0x93:return 0x6C;
	case 0x94:return 0x6D;
	case 0x95:return 0x6E;
	case 0x96:return 0x6F;
	case 0x97:return 0x70;
	case 0x98:return 0x71;
	case 0x99:return 0x72;
	case 0xA1:return 0x7E;
	case 0xA2:return 0x73;
	case 0xA3:return 0x74;
	case 0xA4:return 0x75;
	case 0xA5:return 0x76;
	case 0xA6:return 0x77;
	case 0xA7:return 0x78;
	case 0xA8:return 0x79;
	case 0xA9:return 0x7A;
	case 0xC0:return 0x7B;
	case 0xC1:return 0x41;
	case 0xC2:return 0x42;
	case 0xC3:return 0x43;
	case 0xC4:return 0x44;
	case 0xC5:return 0x45;
	case 0xC6:return 0x46;
	case 0xC7:return 0x47;
	case 0xC8:return 0x48;
	case 0xC9:return 0x49;
	case 0xD0:return 0x7D;
	case 0xD1:return 0x4A;
	case 0xD2:return 0x4B;
	case 0xD3:return 0x4C;
	case 0xD4:return 0x4D;
	case 0xD5:return 0x4E;
	case 0xD6:return 0x4F;
	case 0xD7:return 0x50;
	case 0xD8:return 0x51;
	case 0xD9:return 0x52;
	case 0xE0:return 0x5C;
	case 0xE2:return 0x53;
	case 0xE3:return 0x54;
	case 0xE4:return 0x55;
	case 0xE5:return 0x56;
	case 0xE6:return 0x57;
	case 0xE7:return 0x58;
	case 0xE8:return 0x59;
	case 0xE9:return 0x5A;
	case 0xF0:return 0x30;
	case 0xF1:return 0x31;
	case 0xF2:return 0x32;
	case 0xF3:return 0x33;
	case 0xF4:return 0x34;
	case 0xF5:return 0x35;
	case 0xF6:return 0x36;
	case 0xF7:return 0x37;
	case 0xF8:return 0x38;
	case 0xF9:return 0x39;
	default:return 0x1A;
}
}
template<buffer_output_stream output,std::contiguous_iterator Iter>
inline constexpr auto write_proxy(output& out,Iter begin,Iter end)
{
	for(auto iter(begin);iter!=end;++iter)
	{
		if(*iter==0x15)[[unlikely]]
		{
			write(out,begin,iter);
			put(out,u8'\r');
			*iter=u8'\n';
			begin=iter;
		}
		else
			*iter=operator()(*iter);
/*https://www.ibm.com/support/knowledgecenter/en/SSMKHH_9.0.0/com.ibm.etools.mft.doc/ac11630_.htm
IBM's own words. We need treat 0x15 NL as u8"\r\n"
"
You might want to change newline (NL) characters in a text message to carriage return (CR) and line feed (LF) character pairs. This example shows one way in which you can convert these characters.

This conversion might be useful if messages from an EBCDIC platform (for example, using CCSID 1047) are sent to an ASCII platform (for example, using CCSID 437). Problems can arise because the EBCDIC NL character hex '15' is converted to the undefined ASCII character hex '7F'. The ASCII code page has no corresponding code point for the NL character.

In this example, a message flow is created that interprets the input message as a message in the BLOB domain. This message is passed into a ResetContentDescriptor node to reset the data to a message in the MRM domain. The message is called msg_nl (a set of repeating string elements delimited by EBCDIC NL characters). A Compute node is then used to create an output based on another message in the MRM domain called msg_crlf (a set of repeating string elements delimited by CR LF pairs). The message domain is then changed back to BLOB in another ResetContentDescriptor node. This message flow is shown in the following diagram.
"
*/
	}
	write(out,begin,end);
	return end;
}

};


template<buffer_output_stream T,std::integral ch_type=typename T::char_type,std::size_t sz=4096>
using oascii_to_ebcdic=otransform_function_default_construct<T,ascii_to_ebcdic,ch_type,sz>;

template<buffer_output_stream T,std::integral ch_type=char,std::size_t sz=4096>
using oebcdic_to_ascii=otransform_function_default_construct<T,ebcdic_to_ascii,ch_type,sz>;


template<buffer_input_stream T,std::integral ch_type=char,std::size_t sz=4096>
using iascii_to_ebcdic=itransform_function_default_construct<T,ascii_to_ebcdic,ch_type,sz>;

template<buffer_input_stream T,std::integral ch_type=typename T::char_type,std::size_t sz=4096>
using iebcdic_to_ascii=itransform_function_default_construct<T,ebcdic_to_ascii,ch_type,sz>;

}