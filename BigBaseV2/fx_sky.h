#pragma once


namespace big::menu
{
	class game_fx_sky_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline game_fx_sky_menu m_game_fx_sky_menu;
}

namespace big::game_fx::sky::vars
{
	struct variables {
		float m_azimuth_east_red;
		float m_azimuth_east_green;
		float m_azimuth_east_blue;
		float m_azimuth_east_intensity = 1.0f;
		bool m_azimuth_east_rainbow = false;

		float m_azimuth_west_red;
		float m_azimuth_west_green;
		float m_azimuth_west_blue;
		float m_azimuth_west_intensity = 1.0f;
		bool m_azimuth_west_rainbow = false;

		float m_azimuth_transition_red;
		float m_azimuth_transition_green;
		float m_azimuth_transition_blue;
		float m_azimuth_transition_intensity = 1.0f;
		bool m_azimuth_transition_rainbow = false;

		float m_zenith_red;
		float m_zenith_green;
		float m_zenith_blue;
		float m_zenith_intensity = 1.0f;
		bool m_zenith_rainbow = false;

		float m_zenith_transition_red;
		float m_zenith_transition_green;
		float m_zenith_transition_blue;
		float m_zenith_transition_intensity = 1.0f;
		bool m_zenith_transition_rainbow = false;

		float m_cloud_mid_red;
		float m_cloud_mid_green;
		float m_cloud_mid_blue;
		float m_cloud_mid_intensity = 1.0f;
		bool m_cloud_mid_rainbow = false;

		float m_cloud_base_red;
		float m_cloud_base_green;
		float m_cloud_base_blue;
		float m_cloud_base_intensity = 1.0f;
		bool m_cloud_base_rainbow = false;
	};

	extern variables m_vars;
}