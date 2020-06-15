#include<iostream>

int main()
{
    std::cerr <<
      "Usage: cmake --build <dir> [options] [-- [native-options]]\n"
      "Options:\n"
      "  <dir>          = Project binary directory to be built.\n"
      "  --parallel [<jobs>], -j [<jobs>]\n"
      "                 = Build in parallel using the given number of jobs. \n"
      "                   If <jobs> is omitted the native build tool's \n"
      "                   default number is used.\n"
      "                   The CMAKE_BUILD_PARALLEL_LEVEL environment "
      "variable\n"
      "                   specifies a default parallel level when this "
      "option\n"
      "                   is not given.\n"
      "  --target <tgt>..., -t <tgt>... \n"
      "                 = Build <tgt> instead of default targets.\n"
      "  --config <cfg> = For multi-configuration tools, choose <cfg>.\n"
      "  --clean-first  = Build target 'clean' first, then build.\n"
      "                   (To clean only, use --target 'clean'.)\n"
      "  --verbose, -v  = Enable verbose output - if supported - including\n"
      "                   the build commands to be executed. \n"
      "  --             = Pass remaining options to the native tool.\n"
      ;
}