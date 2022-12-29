#include "hooking.hpp"
#include "caller.hpp"
namespace big
{
	uint64_t sub_140F14DF4(uint64_t a1) {
		uint64_t v1; // rdx
		uint64_t v2; // rcx
		uint64_t v3; // rdx
		uint64_t result; // rax

		v1 = *(uint64_t*)(a1 + 80);
		v2 = 0;

		if (v1) {
			v3 = *(uint64_t*)(v1 + 72);
		}
		else {
			v3 = 0;
		}

		if (v3 && (*(uint32_t*)(v3 + 92) & 0xFu) >= 2)
			result = *(uint64_t*)v3;
		else
			result = 0;
		if (result) {
			if (*(uint8_t*)(result + 40) == 3)
				v2 = result;
			result = v2;
		}

		return result;
	}

	bool hooks::hk_indecent_exposure_hook_patch(__int64 a1, __int64 a2)
	{
		if (a1 && a2 == 2)
			if (const auto ptr = *reinterpret_cast<uintptr_t*>((a1 + 0x48)); ptr)
				if (const auto ptr2 = *reinterpret_cast<uintptr_t*>((ptr + 0x30)); ptr2)
					if (*reinterpret_cast<uintptr_t*>(ptr2 + 0x2C8) == 0)
						return 0;

	    return g_hooking->og_indecent_exposure_hook_patch.get_original<decltype(&hooks::hk_indecent_exposure_hook_patch)>()(a1, a2);	
	
	}
	bool hooks::hk_meltdown_crash_patch(__int64 a1)
	{
		__try
		{
			return g_hooking->og_meltdown_crash_patch.get_original<decltype(&hooks::hk_meltdown_crash_patch)>()(a1);
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
		{
			return 0;

		}
	}

	uint64_t hooks::hk_invalid_tracked_event_crash_patch(__m128* a1, float* a2, bool a3, int a4)
	{
		__try
		{
			return g_hooking->og_invalid_tracked_event_crash_patch.get_original<decltype(&hooks::hk_invalid_tracked_event_crash_patch)>()(a1, a2, a3, a4);
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
		{
			return 0;

		}
	}

	void hooks::hk_invalid_mods_crash_detour(int64_t a1, int64_t a2, int a3, char a4)
	{
		if (!*(int64_t*)(a1 + 0xD8))
			return;
		g_hooking->og_invalid_mods_crash_detour.get_original<decltype(&hooks::hk_invalid_mods_crash_detour)>()(a1, a2, a3, a4);
	}

	
	uint64_t hooks::hk_trailer_attach_crash_patch(uint64_t trailer, uint16_t flag)
	{
		uint64_t entity = *(uint64_t*)(trailer + 0x50);
		if (!is_valid_ptr(entity)) {
			return 0;
		}

		uint64_t draw_handler = *(uint64_t*)(entity + 0x48);
		if (!is_valid_ptr(draw_handler)) {
			return 0;
		}

		if ((*(uint32_t*)(draw_handler + 0x5C) & 0xF) >= 2) {
			uint64_t trailer_info = *(uint64_t*)draw_handler;
			if (!trailer_info) {
				return 0;
			}

			uint64_t table = *(uint64_t*)(trailer_info + 0xC48);
			if (!is_valid_ptr(table)) {
				return 0;
			}

			if (*(uint16_t*)(trailer_info + 0xC50)) {
				for (uint16_t i = 0; i < *(uint16_t*)(trailer_info + 0xC50); i++) {
					uint64_t address = *(uint64_t*)(table + (i * 8));
					if (!is_valid_ptr(address)) {
						return 0;
					}
				}
			}
		}
		return g_hooking->og_trailer_attach_crash_patch.get_original<decltype(&hooks::hk_trailer_attach_crash_patch)>()(trailer, flag);
	}
	uint64_t hooks::hk_trailer_attach_audio_crash_patch(uint64_t audio_entity, uint64_t a2)
	{
		if (!is_valid_ptr(audio_entity)) {
			return 0;
		}

		uint64_t entity = sub_140F14DF4(*(uint64_t*)(audio_entity + 0x6C8));
		if (is_valid_ptr(entity)) {
			uint64_t ptr = *(uint64_t*)(entity + 0x970);
			if (!is_valid_ptr(ptr)) {
				return 0;
			}
		}
		return g_hooking->og_trailer_attach_audio_crash_patch.get_original<decltype(&hooks::hk_trailer_attach_audio_crash_patch)>()(audio_entity, a2);
	}
	uint64_t hooks::hk_invalid_script_crash_patch(uint64_t a1, uint64_t a2)
	{
		if (!is_valid_ptr(a1)) {
			return 0;
		}
		if (*(uint64_t*)a1 != a2) {
			if (*(uint64_t*)(a1 + 8) != a2) {
				if (!is_valid_ptr(*(uint64_t*)(a2 + 0x18))) {
					return 0;
				}

				if (!is_valid_ptr(*(uint64_t*)(a2 + 0x20))) {
					return 0;
				}
			}
			else {
				if (!is_valid_ptr(*(uint64_t*)(a1 + 8))) {
					return 0;
				}
			}
		}
		return g_hooking->og_invalid_script_crash_patch.get_original<decltype(&hooks::hk_invalid_script_crash_patch)>()(a1, a2);
	}
	uint64_t hooks::hk_invalid_script_crash_patch2(uint64_t a1, uint16_t a2, uint32_t a3, bool a4)
	{
		uint64_t* v5; // rcx
		uint64_t i; // rbx

		if (!is_valid_ptr(a1)) {
			return false;
		}

		v5 = (uint64_t*)(a1 + 0x30);
		if (!is_valid_ptr(v5))
			return false;

		for (i = *v5; i && (*(uint16_t*)(i + 8) != a2 || *(uint32_t*)(i + 16) != a3); i = *(uint64_t*)(i + 24))
			;

		if (!is_valid_ptr(i))
			return false;

		return g_hooking->og_invalid_script_crash_patch2.get_original<decltype(&hooks::hk_invalid_script_crash_patch2)>()(a1, a2, a3, a4);
	}
	uint64_t hooks::hk_invalid_sub_crash_patch(uint64_t a1, int a2, uint32_t a3)
	{
		if (!is_valid_ptr(a1) || !is_valid_ptr(*(uint64_t*)(a1 + 0x100))) {
			return 0;
		}

		if (a2 == 2) {
			if ((*(uint16_t*)(a1 + 0x204) >> 8) == 0xFF && (*(uint16_t*)(a1 + 0x204) & 0xFF) != 0xFF) {
				return 0;
			}
		}
		return g_hooking->og_invalid_sub_crash_patch.get_original<decltype(&hooks::hk_invalid_sub_crash_patch)>()(a1, a2, a3);
	}
	uint64_t hooks::hk_invalid_attachment_crash_patch(uintptr_t a1)
	{
		if (!*reinterpret_cast<void**>(a1 + 0x38))
			return 0;

		return g_hooking->og_invalid_attachment_crash_patch.get_original<decltype(&hooks::hk_invalid_attachment_crash_patch)>()(a1);
	}
	void hooks::hk_invalid_player_crash_patch(uint64_t a1, uint64_t a2)//function that handles the player join
	{
		uint64_t v6;//rbx
		uint64_t* v8;//rax

		v6 = 0i64;

		v8 = *(uint64_t**)(a1 + 0x50);

		if (!is_valid_ptr(v8))
			return;

		if (*v8 == v6 || v8 == nullptr || !v8)
			return;


		return g_hooking->og_invalid_player_crash_patch.get_original<decltype(&hooks::hk_invalid_player_crash_patch)>()(a1, a2);
	}
	bool hooks::hk_invalid_melee_crash_patch(uint64_t a1, bool a2, bool a3, bool a4)
	{
		uint64_t v4;//rbx
		uint64_t v16;//r8

		v4 = *(QWORD*)(a1 + 0x408);

		v16 = *(int*)(v4 + 0xBD8);

		if (!v4) {
			return 0;
		}

		if (!v16) {
			return 0;
		}

		
		return g_hooking->og_invalid_melee_crash_patch.get_original<decltype(&hooks::hk_invalid_melee_crash_patch)>()(a1, a2, a3 ,a4);
	}

	bool hooks::hk_invalid_dynamic_entity_crash_patch(uint64_t a1, uint64_t a2, bool a3)
	{
		uint64_t v8;//rax
		uint64_t v9;//rdi
		uint64_t v10; // rax
		uint64_t v11; // rcx
		QWORD* v13; // rcx

		v8 = (*(uint64_t(__fastcall**)(uint64_t))(*(QWORD*)a1 + 0x60i64))(a1);
		v9 = v8;
		v10 = *(QWORD*)(v8 + 0x68);
		v11 = *(QWORD*)(v10 + 0x190);
		v13 = *(QWORD**)(*(QWORD*)(v9 + 0x78) + 0xF0i64);

		if (!is_valid_ptr(v8)) {
			return false;
		}
		if (!v8) {
			return false;
		}
		if (!is_valid_ptr(v9)) {
			return false;
		}
		if (!v9) {
			return false;
		}
		if (!is_valid_ptr(v10)) {
			return false;
		}
		if (!v10) {
			return false;
		}
		if (!is_valid_ptr(v11)) {
			return false;
		}
		if (!v11) {
			return false;
		}
		if (!is_valid_ptr(v13)) {
			return false;
		}
		if (!v13) {
			return false;
		}
		return g_hooking->og_invalid_dynamic_entity_crash_patch.get_original<decltype(&hooks::hk_invalid_dynamic_entity_crash_patch)>()(a1, a2, a3);
	}

	
}