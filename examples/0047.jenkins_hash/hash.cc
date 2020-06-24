#include"../../include/fast_io.h"
#include"../../include/fast_io_crypto.h"
//https://github.com/vkandy/jenkins-hash-java/blob/master/test/JenkinsHashTest.java
int main()
{
	static_assert(fast_io::jenkins_hash64("")==0xdeadbeefdeadbeefL);
	static_assert(fast_io::jenkins_hash("",0,0xdeadbeef)==0xbd5b7ddedeadbeefL);
	static_assert(fast_io::jenkins_hash("",0xdeadbeef,0xdeadbeef)==0x9c093ccdbd5b7ddeL);
	static_assert(fast_io::jenkins_hash64("Four score and seven years ago")==0x17770551ce7226e6L);
	static_assert(fast_io::jenkins_hash("Four score and seven years ago",0,1)==0xe3607caebd371de4L);
	static_assert(fast_io::jenkins_hash("Four score and seven years ago",1,0)==0xcd6281616cbea4b3L);
	static_assert(fast_io::jenkins_hash("Four score and seven years ago",0)==0x17770551);
	static_assert(fast_io::jenkins_hash("Four score and seven years ago",1)==0xcd628161);
//https://wow.tools/files/#search=interface%2Ficons%2Ftemp.blp&page=1&sort=2&desc=asc
/*
https://wowdev.wiki/TACT#hashpath
Path must be upper case
all / should be replaced with \

hashpath (string path) → uint32_t
{
  string normalized = toupper (path).replace (from: '/', to: '\\')
  uint32_t pc = 0, pb = 0;
  hashlittle2 (normalized, strlen (normalized), &pc, &pb);
  return pc;
}
*/
	static_assert(fast_io::jenkins_hash64("INTERFACE\\ICONS\\TEMP.BLP")==0x7335d62c984ecc1b);

/*
https://wow.tools/files/#search=humanfemale.m2&page=1&sort=2&desc=asc
*/
	static_assert(fast_io::jenkins_hash64("CHARACTER\\HUMAN\\FEMALE\\HUMANFEMALE.M2")==0xa7ac55143c1830bf);//Human female SD model file in World of Warcraft
}