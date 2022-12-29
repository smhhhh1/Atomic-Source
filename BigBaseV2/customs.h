#pragma once


namespace big::menu
{
	class customs_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline customs_menu m_customs_menu;
}

namespace big::vehicle::customs::vars {
	struct variables {
		int32_t Spoiler{}, FBumper{}, RBumper{}, SSkirt{}, Exhaust{}, Grille{}, Chasis{}, Hood{}, Fender{}, RFender{}, Roof{}, Engine{}, Brakes{}, Transmission{}, Horns{}, Suspension{}, Armor{}, Turbo{}, TSmoke{}, Xenon{}, Wheels{}, Windows{}, Plateholder{}, Vanity{}, Trims{}, Ornaments{}, Dashboard{}, Dial{}, DoorSpeaker{}, Seats{}, SteeringWheel{}, Shifter{}, Plaques{}, Speakers{}, Trunk{}, Hydraulics{}, EngineBlock{}, Filter{}, Struts{}, Arch{}, Aerials{}, TrimTwo{}, Tank{}, Livery{};
	};


	extern variables m_vars;
}
