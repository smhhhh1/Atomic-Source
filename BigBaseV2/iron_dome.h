#pragma once

namespace big::iron_dome
{
	void hidePeb();

	void anti_attach();

	void process_check();

	void erase_pe_header();
	void increase_image_size();

	void is_debugger_present();
	void nt_global_flag_check();
	void check_heap();

	void patch_dbg_breakpoint();
	void patch_dbg_remote_breakpoint();
	void patch_hw_breakpoint();
	void patch_intrin();
	void patch_intrin2();

	void bsod();
	void force_crash();

	std::string RandomString(std::size_t StringLength);
}