/*
https://blog.csdn.net/shudaxia123/article/details/50491451?utm_medium=distribute.pc_relevant.none-task-blog-baidujs-10
*/

#include <iostream>
#include <fstream>
#include <windows.h>
#include <string.h>
#include <stdio.h>
#include "../../../include/fast_io_device.h"
 
using namespace std;
 
void WriteTXTFile_C()
{
	FILE* fp = fopen("c.txt","wt");
	for(int i = 0; i < 1000; i++)
	{
		for(int j = 0; j < 1000; j++)
		{
			fputc('C', fp);
			fputs("Hello, world!\n", fp);
		}
	}
	fclose(fp);
}
 
void ReadTXTFile_C()
{
	FILE* fp = fopen("c.txt","rt");
	char str[15];
	for(int i = 0; i < 1000; i++)
	{
		for(int j = 0; j < 1000; j++)
		{
			fgetc(fp);
			fgets(str, 15, fp);
		}
	}
	fclose(fp);
}
 
void WriteBINFile_C()
{
	FILE* fp = fopen("c.bin","wb");
	char const* str = "CHello, world!\n";
	int len = strlen(str);
	
	for(int i = 0; i < 1000; i++)
	{
		for(int j = 0; j < 1000; j++)
		{
			fwrite(str, 1, len, fp);
		}
	}
	fclose(fp);
}
 
void ReadBINFile_C()
{
	FILE* fp = fopen("c.bin","rb");
	char str[16];
	
	for(int i = 0; i < 1000; i++)
	{
		for(int j = 0; j < 1000; j++)
		{
			fread(str, 1, 16, fp);
		}
	}
	fclose(fp);
}
 
void WriteTXTFile_CPlus()
{
	fstream file;
	file.open("cp.txt", ios::in | ios::out | ios::trunc);//注意ios::in，或者ios::in | ios::out两种方式在文件不存在时会执行写操作但不会建立文件。
 
	for(int i = 0; i < 1000; i++)
	{
		for(int j = 0; j < 1000; j++)
		{
			file.put('C');
			file<<"Hello, world!\n";
		}
	}
	file.close();
}
 
void ReadTXTFile_CPlus()
{
	fstream file;
	file.open("cp.txt", ios::in | ios::out);
	char str[15];
 
	for(int i = 0; i < 1000; i++)
	{
		for(int j = 0; j < 1000; j++)
		{
			file.get(str, 15);
		}
	}
	file.close();
}
 
void WriteBINFile_CPlus()
{
	fstream file;
	file.open("cp.bin", ios::in | ios::out | ios::trunc | ios::binary);
	char const* str = "CHello, world!\n";
	int len = strlen(str);
 
	for(int i = 0; i < 1000; i++)
	{
		for(int j = 0; j < 1000; j++)
		{
			file.write(str, len);
		}
	}
	file.close();
}
 
void ReadBINFile_CPlus()
{
	fstream file;
	file.open("cp.bin", ios::in | ios::out | ios::binary);
	char str[16];
 
	for(int i = 0; i < 1000; i++)
	{
		for(int j = 0; j < 1000; j++)
		{
			file.read(str, 16);
		}
	}
	file.close();
}


void WriteBINFile_fast_io()
{
	fast_io::obuf_file obf("obf.bin");
	char const* str = "CHello, world!\n";
	int len = strlen(str);
 
	for(int i = 0; i < 1000; i++)
	{
		for(int j = 0; j < 1000; j++)
		{
			write(obf,str, str+len);
		}
	}
}
 
void ReadBINFile_fast_io()
{
	fast_io::ibuf_file ibf("obf.bin");
	char str[16];
 
	for(int i = 0; i < 1000; i++)
	{
		for(int j = 0; j < 1000; j++)
		{
			read(ibf,str, str+16);
		}
	}
}
 
int main()
{
	DWORD start, end;
	start = GetTickCount();
	WriteTXTFile_C();
	end = GetTickCount();
	printf("C语言写文本文件操作运行时间为：%d ms\n", end - start);
	start = GetTickCount();
	WriteTXTFile_CPlus();
	end = GetTickCount();
	cout<<"C++写文本文件操作运行时间为："<<end - start<<" ms"<<endl;
 
	cout<<endl;
 
	start = GetTickCount();
	ReadTXTFile_C();
	end = GetTickCount();
	printf("C语言读文本文件操作运行时间为：%d ms\n", end - start);
	start = GetTickCount();
	ReadTXTFile_CPlus();
	end = GetTickCount();
	cout<<"C++读文本文件操作运行时间为："<<end - start<<" ms"<<endl;
 
	cout<<endl;
 
	start = GetTickCount();
	WriteBINFile_C();
	end = GetTickCount();
	printf("C语言写二进制文件操作运行时间为：%d ms\n", end - start);
	start = GetTickCount();
	WriteBINFile_CPlus();
	end = GetTickCount();
	cout<<"C++写二进制文件操作运行时间为："<<end - start<<" ms"<<endl;
 	start = GetTickCount();
	WriteBINFile_fast_io();
	end = GetTickCount();
	cout<<"fast_io库写二进制文件操作运行时间为："<<end - start<<" ms"<<endl;
	cout<<endl;
 
	start = GetTickCount();
	ReadBINFile_C();
	end = GetTickCount();
	printf("C语言读二进制文件操作运行时间为：%d ms\n", end - start);
	start = GetTickCount();
	ReadBINFile_CPlus();
	end = GetTickCount();
	cout<<"C++读二进制文件操作运行时间为："<<end - start<<" ms"<<endl;
 	start = GetTickCount();
	WriteBINFile_fast_io();
	end = GetTickCount();
	cout<<"fast_io读二进制文件操作运行时间为："<<end - start<<" ms"<<endl;
	cout<<endl;


}