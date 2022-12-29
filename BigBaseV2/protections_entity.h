#pragma once


namespace big::menu
{
	class protections_entity_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline protections_entity_menu m_protections_entity_menu;
}

namespace big::protections::entity::vars
{
	struct variables {
		bool m_disable_text_messages{ false };
		bool m_disable_chat_messages{ false };
		bool m_car{ false };
		bool m_bike{ false };
		bool m_boat{ false };
		bool m_door{ false };
		bool m_heli{ false };
		bool m_object{ false };
		bool m_ped{ false };
		bool m_pickup{ false };
		bool m_pickup_placement{ false };
		bool m_plane{ false };
		bool m_sub{ false };
		bool m_player{ false };
		bool m_train{ false };
		bool m_trailer{ false };

		bool m_sync_car{ false };
		bool m_sync_bike{ false };
		bool m_sync_boat{ false };
		bool m_sync_door{ false };
		bool m_sync_heli{ false };
		bool m_sync_object{ false };
		bool m_sync_ped{ false };
		bool m_sync_pickup{ false };
		bool m_sync_pickup_placement{ false };
		bool m_sync_plane{ false };
		bool m_sync_sub{ false };
		bool m_sync_player{ false };
		bool m_sync_train{ false };
		bool m_sync_trailer{ false };
	};

	extern variables m_vars;
}