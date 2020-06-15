#include"../../../include/fast_io_legacy.h"

int main()
{
	const char* kNinjaVersion = "1.9.0.git";
	int parallelism{1};

print(fast_io::c_stderr,
"usage: ninja [options] [targets...]\n"
"\n"
"if targets are unspecified, builds the 'default' target (see manual).\n"
"\n"
"options:\n"
"  --version      print ninja version (\"",kNinjaVersion,"\")\n"
"  -v, --verbose  show all command lines while building\n"
"\n"
"  -C DIR   change to DIR before doing anything else\n"
"  -f FILE  specify input build file [default=build.ninja]\n"
"\n"
"  -j N     run N jobs in parallel (0 means infinity) [default=",parallelism," on this system]\n"
"  -k N     keep going until N jobs fail (0 means infinity) [default=1]\n"
"  -l N     do not start new jobs if the load average is greater than N\n"
"  -n       dry run (don't run commands but act like they succeeded)\n"
"\n"
"  -d MODE  enable debugging (use '-d list' to list modes)\n"
"  -t TOOL  run a subtool (use '-t list' to list subtools)\n"
"    terminates toplevel options; further flags are passed to the tool\n"
"  -w FLAG  adjust warnings (use '-w list' to list warnings)\n");
}