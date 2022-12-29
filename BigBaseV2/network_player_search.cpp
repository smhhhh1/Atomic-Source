#include "common.hpp"
#include "gta_util.hpp"
#include "network_player_search.h"
#include "natives.hpp"
#include "pointers.hpp"
#include "script.hpp"
#include "../render.h"
#include "../abstract_submenu.h"
#include "../break_option.h"
#include "../toggle_option.h"
#include "../number.h"
#include "../option.h"
#include "../submenu_option.h"
#include "../simple_option.h"
#include "../simple_submenu.h"
#include "../bool_and_number.h"
#include "../submenu_option.h"
#include "../submenus.h"
#include "on_screen_ped.h"
#include "lists.h"
#include "fiber_pool.hpp"
#include "script_global.hpp"

#include "HTTPRequest.hpp"
#include <winsock2.h>
#pragma comment(lib,"WS2_32")



//TODO: fix this

namespace big::menu
{
	std::vector<std::string> findPlayer(std::string name)
	{
		std::vector<std::string> tmpVec;
		http::Request request("http://scui.rockstargames.com/api/friend/accountsearch");
		nlohmann::json body = { { "searchNickname", name } };
		if (auto scInfo = g_pointers->m_scinfo; auto scTicket = (*scInfo)->m_ticket) {
			auto response = request.send("POST", body.dump(), { "X-Requested-With: XMLHttpRequest", "Content-Type: application/json; charset=utf-8", "Authorization: SCAUTH val=\"" + std::string(scTicket) + "\"" }, 1s);
			auto parsedBody = nlohmann::json::parse(response.body.begin(), response.body.end());
			if (parsedBody["Status"].get<bool>() && name.size() <= 20)
				if (auto numAccs = parsedBody["Total"].get<int>(); numAccs > 0) {
					for (auto& acc : parsedBody["Accounts"])
						tmpVec.push_back({ acc["Nickname"].get<std::string>() });
					return tmpVec;
				}
				else
					LOG(INFO) << "invalid";
		}
		return tmpVec;
	}
}


namespace big::menu
{


	void network_player_search_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<sub>("Player Search", SubNetworkPlayerSearch, [](sub* core)
			{
				m_renderer.m_enable_player_info = false;

				//TODO: clean this shit up

				for (std::uint32_t i = 0; i < findPlayer("monkey").size(); ++i)
				{
					core->add_option<simple_option>(findPlayer("monkey").at(i).c_str(),
						nullptr, [=] {

					});
				}

			});
	}

	void network_player_search_menu::script_init() {}

	void network_player_search_menu::script_on_tick() {}

	void network_player_search_menu::script_func()
	{
		m_network_player_search_menu.script_init();
		while (true)
		{
			m_network_player_search_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}