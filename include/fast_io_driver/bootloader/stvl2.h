#pragma once
#include<cstdint>
#include<cstddef>
#include<type_traits>
#include<bit>

/*
https://github.com/stivale/stivale

we just call it stvl2 to avoid naming collision with stivale2
*/

namespace stvl2
{

static_assert(sizeof(void*)==4||sizeof(void*)==8);
static_assert(std::endian::little==std::endian::native);
struct [[gnu::packed]] stvl2_pointer_padding
{
struct stvl2_empty{};
[[no_unique_address]] std::conditional_t<sizeof(void*)==8,stvl2_empty,std::uint32_t> pad;
};

enum class stvl2_header_tag:std::uint64_t
{
framebuffer_id=0x3ecc1bc43d0f7971,
fb_mtrr_id=0x4c7bb07731282e00,
smp_id=0x1ab015085f3273df
};

enum class stvl2_struct_tag:std::uint64_t
{
cmdline_id=0xe5e76a1b4597a781,
memmap_id=0x2187f79e8612de07,
framebuffer_id=0x506461d2950408fa,
fb_mtrr_id=0x6bc1a78ebe871172,
modules_id=0x4b6fe466aade04ce,
rsdp_id=0x9e1786930a375e78,
epoch_id=0x566a7bed888e1407,
firmware_id=0x359d837855e3858c,
smp_id=0x34d1d96339647025,
pxe_server_info=0x29d1e96239247032,
mmio32_uart=0xb813f9b8dbc78797,
dtb=0xabb29bd49a2833fa,
vmap=0xb0ed257db18cb58f
};

enum class stvl2_mmap_type:std::uint32_t
{
usable=1,
reserved=2,
acpi_reclaimable=3,
acpi_nvs=4,
bad_memory=5,
bootloader_reclaimable=0x1000,
kernel_and_modules=0x1001
};

enum class stvl2_firmware_flags:std::uint64_t
{
bios=1<<0
};

/*
use stvl2 instead of stivale2 to avoid collision with stivale2.h
*/
struct [[gnu::packed]] stvl2_tag
{
	std::uint64_t identifier;
	std::uint64_t next;
};

struct [[gnu::packed]] stvl2_header
{
	[[no_unique_address]] stvl2_pointer_padding entry_point_pointer_pading;
	void* entry_point;
	[[no_unique_address]] stvl2_pointer_padding stack_pointer_pading;
	void* stack;
	std::uint64_t flags;
	stvl2_header_tag tags;
};

struct [[gnu::packed]] stvl2_header_tag_framebuffer : stvl2_tag
{
	std::uint16_t framebuffer_width;
	std::uint16_t framebuffer_height;
	std::uint16_t framebuffer_bpp;
};

struct [[gnu::packed]] stvl2_header_tag_smp : stvl2_tag
{
	std::uint64_t flags;
};

struct [[gnu::packed]] stvl2_struct
{
	inline static constexpr std::size_t bootloader_brand_size{64};
	inline static constexpr std::size_t bootloader_version_size{64};
	char8_t bootloader_brand[bootloader_brand_size];
	char8_t bootloader_version[bootloader_version_size];
	stvl2_struct_tag tags;
};

struct [[gnu::packed]] stvl2_struct_tag_cmdline:stvl2_tag
{
	std::uint64_t cmdline;
};

struct [[gnu::packed]] stvl2_mmap_entry
{
	[[no_unique_address]] stvl2_pointer_padding base_pointer_padding;
	void* base;
	[[no_unique_address]] stvl2_pointer_padding length_padding;
	std::size_t length;
	stvl2_mmap_type type;
	std::uint32_t unused;
};

struct [[gnu::packed]] stvl2_struct_tag_memmap:stvl2_tag
{
	std::uint64_t entries;
	[[no_unique_address]] stvl2_mmap_entry memmaps[];
};

struct [[gnu::packed]] stvl2_struct_tag_framebuffer:stvl2_tag
{
	[[no_unique_address]] stvl2_pointer_padding framebuffer_addr_pointer_padding;
	void* framebuffer_addr;
	std::uint16_t framebuffer_width;
	std::uint16_t framebuffer_height;
	std::uint16_t framebuffer_pitch;
	std::uint16_t framebuffer_bpp;
	std::uint8_t  memory_model;
	std::uint8_t  red_mask_size;
	std::uint8_t  red_mask_shift;
	std::uint8_t  green_mask_size;
	std::uint8_t  green_mask_shift;
	std::uint8_t  blue_mask_size;
	std::uint8_t  blue_mask_shift;
};

struct [[gnu::packed]] stvl2_module
{
	[[no_unique_address]] stvl2_pointer_padding module_begin_pointer_padding;
	void* module_begin;
	[[no_unique_address]] stvl2_pointer_padding module_end_pointer_padding;
	void* module_end;
	static inline constexpr std::size_t module_string_size{128};
	char8_t module_string[module_string_size];
};

struct [[gnu::packed]] stvl2_struct_tag_modules:stvl2_tag
{
	[[no_unique_address]] stvl2_pointer_padding module_count_padding;
	std::size_t module_count;
	[[no_unique_address]] stvl2_module modules[];
};

struct [[gnu::packed]] stvl2_struct_tag_rsdp:stvl2_tag
{
	std::uint64_t rdsp;
};

struct [[gnu::packed]] stvl2_struct_tag_epoch:stvl2_tag
{
	std::uint64_t epoch;
};

struct [[gnu::packed]] stvl2_struct_tag_firmware:stvl2_tag
{
	stvl2_firmware_flags tag;
};

struct [[gnu::packed]] stvl2_smp_info
{
	std::uint32_t process_id;
	std::uint32_t lapic_id;
	[[no_unique_address]] stvl2_pointer_padding target_stack_pointer_padding;
	void* target_stack;
	[[no_unique_address]] stvl2_pointer_padding goto_address_pointer_padding;
	void* goto_address;
	[[no_unique_address]] stvl2_pointer_padding extra_argument_pointer_padding;
	void* extra_argument;
};

struct [[gnu::packed]] stvl2_struct_tag_smp:stvl2_tag
{
	std::uint64_t flags;
	std::uint32_t bsp_lapic_id;
	std::uint32_t unused;
	std::uint64_t cpu_count;
	[[no_unique_address]] stvl2_smp_info smp_info[];
};

struct [[gnu::packed]] stvl2_struct_tag_pxe_server_info:stvl2_tag
{
	std::uint32_t server_ip;
};

struct [[gnu::packed]] stvl2_struct_tag_mmio32_uart:stvl2_tag
{
	[[no_unique_address]] stvl2_pointer_padding addr_padding;
	void* addr;
};

struct [[gnu::packed]] stvl2_struct_tag_dtb:stvl2_tag
{
	[[no_unique_address]] stvl2_pointer_padding addr_padding;
	void* addr;
	[[no_unique_address]] stvl2_pointer_padding size_padding;
	std::size_t size;
};

struct [[gnu::packed]] stvl2_struct_vmap:stvl2_tag
{
	[[no_unique_address]] stvl2_pointer_padding addr_padding;
	void* addr;
};

}