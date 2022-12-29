#include "common.hpp"
#include "gta_util.hpp"
#include "network_selected_esp.h"
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
using namespace big::network::selected_player::esp::vars;


namespace big::network::selected_player::esp::vars
{
    variables m_vars;
}


namespace big::menu
{


    void network_selected_esp_menu::menu()
    {
        using namespace ui;

        m_renderer.new_sub<PlayerSubmenu>(&selected_player, SubSelectedESP, [](PlayerSubmenu* core)
            {
                m_renderer.m_enable_player_info = true;
                core->add_option<submenu>("Settings", nullptr, SubSelectedEspSettings);

                core->add_option<toggle_option<bool>>(("Name"), nullptr, &m_vars.name);
                core->add_option<toggle_option<bool>>(("Box"), nullptr, &m_vars.box);
                core->add_option<toggle_option<bool>>(("Line"), nullptr, &m_vars.line);
            });

		m_renderer.new_sub<PlayerSubmenu>(&selected_player, SubSelectedEspSettings, [](PlayerSubmenu* core)
			{
				m_renderer.m_enable_player_info = true;
				core->add_option<submenu>(("Box"), nullptr, EspSelectedBox);
				core->add_option<submenu>(("Line"), nullptr, EspSelectedLine);
				core->add_option<submenu>(("Name"), nullptr, EspSelectedName);
			});
		m_renderer.new_sub<PlayerSubmenu>(&selected_player, EspSelectedName, [](PlayerSubmenu* sub)
			{
				m_renderer.m_enable_player_info = true;
				

				sub->add_option<number_option<int>>(("[R]ed"), nullptr, &m_vars.name_red, 0, 255, 5, 1, false);
				sub->add_option<number_option<int>>(("[G]reen"), nullptr, &m_vars.name_green, 0, 255, 1, 1, false);
				sub->add_option<number_option<int>>(("[B]lue"), nullptr, &m_vars.name_blue, 0, 255, 1, 1, false);
			});
		m_renderer.new_sub<PlayerSubmenu>(&selected_player, EspSelectedBox, [](PlayerSubmenu* sub)
			{
				m_renderer.m_enable_player_info = true;
				

				sub->add_option<number_option<int>>(("[R]ed"), nullptr, &m_vars.box_red, 0, 255, 5, 1, false);
				sub->add_option<number_option<int>>(("[G]reen"), nullptr, &m_vars.box_green, 0, 255, 1, 1, false);
				sub->add_option<number_option<int>>(("[B]lue"), nullptr, &m_vars.box_blue, 0, 255, 1, 1, false);
			});
		m_renderer.new_sub<PlayerSubmenu>(&selected_player, EspSelectedLine, [](PlayerSubmenu* sub)
			{
				m_renderer.m_enable_player_info = true;

				sub->add_option<number_option<int>>(("[R]ed"), nullptr, &m_vars.line_red, 0, 255, 5, 1, false);
				sub->add_option<number_option<int>>(("[G]reen"), nullptr, &m_vars.line_green, 0, 255, 1, 1, false);
				sub->add_option<number_option<int>>(("[B]lue"), nullptr, &m_vars.line_blue, 0, 255, 1, 1, false);
			});
    }

    void network_selected_esp_menu::script_init() {}

    void network_selected_esp_menu::script_on_tick()
    {
		auto i = selected_player;
		if (ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i)) && !NETWORK::IS_PLAYER_IN_CUTSCENE(i))
		{
			Vector3 players = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), false);
			Vector3 me = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
			if (m_vars.name)
			{
				Vector3 pHCoords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), 0, 0, 0);

				float xPos;
				float yPos;

				BOOL screencoords = GRAPHICS::GET_SCREEN_COORD_FROM_WORLD_COORD(pHCoords.x, pHCoords.y, pHCoords.z, &xPos, &yPos);

				HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT((char*)"STRING");
				ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(PLAYER::PLAYER_PED_ID(), PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), 17) ? HUD::SET_TEXT_COLOUR(m_vars.name_red, m_vars.name_green, m_vars.name_blue, 255) : HUD::SET_TEXT_COLOUR(m_vars.name_red, m_vars.name_green, m_vars.name_blue, 255);
				HUD::SET_TEXT_FONT(4);
				HUD::SET_TEXT_SCALE(0.3f, 0.3f);
				HUD::SET_TEXT_CENTRE(true);
				HUD::SET_TEXT_DROP_SHADOW();

				std::string name = PLAYER::GET_PLAYER_NAME(i);

				HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(name.c_str());
				HUD::END_TEXT_COMMAND_DISPLAY_TEXT(xPos, yPos, 0);
			}
			if (m_vars.line)
			{
				Vector3 pHCoords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), 0, 0, 0);

				float xPos;
				float yPos;

				BOOL screencoords = GRAPHICS::GET_SCREEN_COORD_FROM_WORLD_COORD(pHCoords.x, pHCoords.y, pHCoords.z, &xPos, &yPos);

				Vector3 selfcoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 0);
				ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(PLAYER::PLAYER_PED_ID(), PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), 17) ? HUD::SET_TEXT_COLOUR(m_vars.line_red, m_vars.line_green, m_vars.line_blue, 255) : HUD::SET_TEXT_COLOUR(m_vars.line_red, m_vars.line_green, m_vars.line_blue, 255);
				GRAPHICS::DRAW_LINE(selfcoords.x, selfcoords.y, selfcoords.z, pHCoords.x, pHCoords.y, pHCoords.z, m_vars.line_red, m_vars.line_green, m_vars.line_blue, 255);
			}
			if (m_vars.box)
			{
				if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), 1))
				{
					Vector3 v0, v1;

					Vector3 coords0from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), -(v1.x + 0.3f), v1.y - 0.3f, -0.9f);
					Vector3 coords0to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), -(v1.x + 0.3f), v1.y + 0.3f, -0.9f);
					Vector3 coords1from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), +(v1.x + 0.3f), v1.y - 0.3f, -0.9f);
					Vector3 coords1to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), +(v1.x + 0.3f), v1.y + 0.3f, -0.9f);
					Vector3 coords2from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), v1.x + -0.3f, +(v1.y + 0.3f), -0.9f);
					Vector3 coords2to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), v1.x + 0.3f, +(v1.y + 0.3f), -0.9f);
					Vector3 coords3from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), v1.x + -0.3f, -(v1.y + 0.3f), -0.9f);
					Vector3 coords3to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), v1.x + 0.3f, -(v1.y + 0.3f), -0.9f);
					Vector3 coords4from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), -(v1.x + 0.3f), v1.y - 0.3f, 0.9f);
					Vector3 coords4to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), -(v1.x + 0.3f), v1.y + 0.3f, 0.9f);
					Vector3 coords5from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), +(v1.x + 0.3f), v1.y - 0.3f, 0.9f);
					Vector3 coords5to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), +(v1.x + 0.3f), v1.y + 0.3f, 0.9f);
					Vector3 coords6from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), v1.x + -0.3f, +(v1.y + 0.3f), 0.9f);
					Vector3 coords6to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), v1.x + 0.3f, +(v1.y + 0.3f), 0.9f);
					Vector3 coords7from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), v1.x + -0.3f, -(v1.y + 0.3f), 0.9f);
					Vector3 coords7to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), v1.x + 0.3f, -(v1.y + 0.3f), 0.9f);
					Vector3 coords8from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), v1.x + 0.3f, -(v1.y + 0.3f), -0.9f);
					Vector3 coords8to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), v1.x + 0.3f, -(v1.y + 0.3f), 0.9f);
					Vector3 coords9from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), v1.x + -0.3f, -(v1.y + -0.3f), -0.9f);
					Vector3 coords9to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), v1.x + -0.3f, -(v1.y + -0.3f), 0.9f);
					Vector3 coords10from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), v1.x + -0.3f, +(v1.y + -0.3f), -0.9f);
					Vector3 coords10to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), v1.x + -0.3f, +(v1.y + -0.3f), 0.9f);
					Vector3 coords11from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), v1.x + 0.3f, +(v1.y + 0.3f), -0.9f);
					Vector3 coords11to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), v1.x + 0.3f, +(v1.y + 0.3f), 0.9f);

					GRAPHICS::DRAW_LINE(coords0from.x, coords0from.y, coords0from.z, coords0to.x, coords0to.y, coords0to.z, m_vars.box_red, m_vars.box_green, m_vars.box_blue, 255);
					GRAPHICS::DRAW_LINE(coords1from.x, coords1from.y, coords1from.z, coords1to.x, coords1to.y, coords1to.z, m_vars.box_red, m_vars.box_green, m_vars.box_blue, 255);
					GRAPHICS::DRAW_LINE(coords2from.x, coords2from.y, coords2from.z, coords2to.x, coords2to.y, coords2to.z, m_vars.box_red, m_vars.box_green, m_vars.box_blue, 255);
					GRAPHICS::DRAW_LINE(coords3from.x, coords3from.y, coords3from.z, coords3to.x, coords3to.y, coords3to.z, m_vars.box_red, m_vars.box_green, m_vars.box_blue, 255);
					GRAPHICS::DRAW_LINE(coords4from.x, coords4from.y, coords4from.z, coords4to.x, coords4to.y, coords4to.z, m_vars.box_red, m_vars.box_green, m_vars.box_blue, 255);
					GRAPHICS::DRAW_LINE(coords5from.x, coords5from.y, coords5from.z, coords5to.x, coords5to.y, coords5to.z, m_vars.box_red, m_vars.box_green, m_vars.box_blue, 255);
					GRAPHICS::DRAW_LINE(coords6from.x, coords6from.y, coords6from.z, coords6to.x, coords6to.y, coords6to.z, m_vars.box_red, m_vars.box_green, m_vars.box_blue, 255);
					GRAPHICS::DRAW_LINE(coords7from.x, coords7from.y, coords7from.z, coords7to.x, coords7to.y, coords7to.z, m_vars.box_red, m_vars.box_green, m_vars.box_blue, 255);
					GRAPHICS::DRAW_LINE(coords8from.x, coords8from.y, coords8from.z, coords8to.x, coords8to.y, coords8to.z, m_vars.box_red, m_vars.box_green, m_vars.box_blue, 255);
					GRAPHICS::DRAW_LINE(coords9from.x, coords9from.y, coords9from.z, coords9to.x, coords9to.y, coords9to.z, m_vars.box_red, m_vars.box_green, m_vars.box_blue, 255);
					GRAPHICS::DRAW_LINE(coords10from.x, coords10from.y, coords10from.z, coords10to.x, coords10to.y, coords10to.z, m_vars.box_red, m_vars.box_green, m_vars.box_blue, 255);
					GRAPHICS::DRAW_LINE(coords11from.x, coords11from.y, coords11from.z, coords11to.x, coords11to.y, coords11to.z, m_vars.box_red, m_vars.box_green, m_vars.box_blue, 255);
				}
			}
		}
    }

    void network_selected_esp_menu::script_func()
    {
        m_network_selected_esp_menu.script_init();
        while (true)
        {


            m_network_selected_esp_menu.script_on_tick();
            script::get_current()->yield();
        }
    }
}