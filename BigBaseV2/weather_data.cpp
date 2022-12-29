#include "hooking.hpp"
#include "CObject.h"
#include "netObject.hpp"
#include "gta/player.hpp"
#include "generic_types.h"
#include "gta/net_object_mgr.hpp"
#include "node_types.h"
#include "notify.h"
#include "node_helpers.h"
#include "weather.h"
namespace big
{

	void hooks::hk_weather_data(CWeatherData* data)
	{

		if (world::weather::vars::m_vars.m_wind_speed == 100000.f) {
			world::weather::vars::m_vars.m_wind_speed = data->m_wind_speed;
		}

		data->m_wind = world::weather::vars::m_vars.m_wind_speed * 12.f;
		data->m_wind_speed = world::weather::vars::m_vars.m_wind_speed;
		
		return g_hooking->og_weather_data.get_original<decltype(&hooks::hk_weather_data)>()(data);
	}
}