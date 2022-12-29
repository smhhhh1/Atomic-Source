#pragma once


namespace big::menu
{
	class spawner_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline spawner_menu m_spawner_menu;
}

namespace big::vehicle::spawner::vars
{
	struct variables {


		bool m_notification{ true };
		bool m_spawn_inside{ true };
		bool m_particleFX{ false };
		bool m_godmode{ true };
		bool m_spawned_max{ false };
		bool m_spawn_air_vehicles_in_air{ true };
		int m_spawn_height{ 100 };
	};
	extern variables m_vars;
}