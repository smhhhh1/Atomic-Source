#include "common.hpp"
#include "gta_util.hpp"
#include "network_selected_text.h"
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
#include "keyboard_option.h"

namespace big::menu
{

    void send_message()
    {
        MISC::DISPLAY_ONSCREEN_KEYBOARD(true, (char*)"Input", (char*)"", (char*)"", (char*)"", (char*)"", (char*)"", 20);
        while (MISC::UPDATE_ONSCREEN_KEYBOARD() == 0)
        {
            m_network_selected_text_menu.active = true;
            m_renderer.ResetInput();
            script::get_current()->yield();
        }
        m_network_selected_text_menu.active = false;
        if (!MISC::GET_ONSCREEN_KEYBOARD_RESULT())
            return;
        m_network_selected_text_menu.message = MISC::GET_ONSCREEN_KEYBOARD_RESULT();
    }

    void network_selected_text_menu::menu()
    {
        using namespace ui;
       
        
        m_renderer.new_sub<PlayerSubmenu>(&selected_player, SubSelectedText, [](PlayerSubmenu* core)
            {
                
                m_renderer.m_enable_player_info = true;

                core->add_option<keyboard>(std::move(keyboard()
                    .SetLeftText("Input Text Message: ").SetRightText(m_network_selected_text_menu.message)
                    .SetAction(send_message))
                );

                core->add_option<simple_option>(("Send Message"), nullptr, [=]
                    {
                        int handle[26];
                        NETWORK::NETWORK_HANDLE_FROM_PLAYER(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player), &handle[0], 13);
                        if (NETWORK::NETWORK_IS_HANDLE_VALID(&handle[0], 13)) {
                            NETWORK::NETWORK_SEND_TEXT_MESSAGE(m_network_selected_text_menu.message, &handle[0]);
                        }
                });
            });
    }

    void network_selected_text_menu::script_init() {}

    void network_selected_text_menu::script_on_tick()
    {
      
    }

    void network_selected_text_menu::script_func()
    {
        m_network_selected_text_menu.script_init();
        while (true)
        {


            m_network_selected_text_menu.script_on_tick();
            script::get_current()->yield();
        }
    }
}