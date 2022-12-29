#pragma once


namespace big::menu
{
	class weapon_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline weapon_menu m_weapon_menu;
}

namespace big::weapon::vars
{
	struct variables {
		bool m_infinite_ammo;
		bool m_rapid_fire;
		bool m_explosive_ammo;
		bool m_fire_ammo;
		bool m_water_ammo;
		bool m_instant_kill;
		bool m_laser_sight;	
		bool m_delete_gun;
		bool m_force_gun;
		bool m_teleport_gun;
		bool m_airstrike_gun;
		bool m_defibrillator_gun;
		bool m_shrink_gun;
		bool m_drive_gun;
		bool m_repair_gun;
		bool m_valkyrie_gun;
		bool m_no_recoil;
		bool m_no_spread;
		bool m_asteriod_gun;
		bool m_ped_gun;
		bool m_trigger_bot;
	};

	extern variables m_vars;
}