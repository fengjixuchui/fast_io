#include"../../include/fast_io.h"
#include"../../include/fast_io_driver/kernel.h"
 
extern "C" void kernel_main(void* multiboot_structure, std::uint32_t magic_number) noexcept
{
	fast_io::kernel::terminal<> terminal;
	print(terminal,"Hello Kernel!\nmultiboot_structure:",multiboot_structure,"\tmagic_number:",fast_io::hex(magic_number));
}

