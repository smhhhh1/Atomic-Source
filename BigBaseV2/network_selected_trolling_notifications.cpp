#include "common.hpp"
#include "gta_util.hpp"
#include "network_selected_trolling_notifications.h"
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
#include "player_submenu.h"
#include "../submenus.h"
#include "on_screen_ped.h"
#include "lists.h"
#include "fiber_pool.hpp"
#include "gta/enums.hpp"
namespace big::menu
{


    void network_selected_trolling_notifications_menu::menu()
    {
        using namespace ui;

        m_renderer.new_sub<PlayerSubmenu>(&selected_player, SubSelectedTrollingNotifications, [](PlayerSubmenu* core)
            {
                m_renderer.m_enable_player_info = true;
                core->add_option<simple_option>(("Money Banked"), nullptr, [=]
                    {
                        int64_t args[2] = { -849958015, PLAYER::PLAYER_ID() };
                        g_pointers->m_trigger_script_event(1, args, 2, 1 << selected_player);
                    });
                core->add_option<simple_option>(("Money Removed"), nullptr, [=]
                    {
                        int64_t args[2] = { -290070531, PLAYER::PLAYER_ID() };
                        g_pointers->m_trigger_script_event(1, args, 2, 1 << selected_player);
                    });
                core->add_option<simple_option>(("Money Stolen"), nullptr, [=]
                    {
                        int64_t args[2] = { -1640162684, PLAYER::PLAYER_ID() };
                        g_pointers->m_trigger_script_event(1, args, 2, 1 << selected_player);
                    });
            });
    }

    void network_selected_trolling_notifications_menu::script_init() {}

    void network_selected_trolling_notifications_menu::script_on_tick()
    {
       
    }

    void network_selected_trolling_notifications_menu::script_func()
    {
        m_network_selected_trolling_notifications_menu.script_init();
        while (true)
        {


            m_network_selected_trolling_notifications_menu.script_on_tick();
            script::get_current()->yield();
        }
    }
}