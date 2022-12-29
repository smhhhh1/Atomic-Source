#include "common.hpp"
#include "gta_util.hpp"
#include "gun_locker.h"
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
#include "scroll.h"
#include "util.h"


namespace big::menu
{

	std::map<signed int, std::string> Weapons{
   { 453432689, "No Weapon" },
   { 1198256469, "Unholy Hellbringer"},
   { -1716189206, "Knife" },
   { 1737195953, "Nightstick" },
   { 1317494643, "Hammer" },
   { -1786099057, "Bat" },
   { -2067956739, "Crowbar" },
   { 1141786504, "Golfclub" },
   { -102323637, "Bottle" },
   { -1834847097, "Dagger" },
   { -102973651, "Hatchet" },
   { -656458692, "Knuckle Duster" },
   { -581044007, "Machete" },
   { -1951375401, "Flashlight"},
   { -538741184, "Switch Blade"},
   { -1810795771, "Poolcue"},
   { 419712736, "Wrench"},
   { -853065399, "Battleaxe"},
   { 453432689, "Pistol"},
   { 3219281620, "Pistol Mk2"},
   { 1593441988, "Combat Pistol"},
   { -1716589765, "Pistol 50"},
   { -1076751822, "SNS Pistol"},
   { -771403250, "Heavy Pistol"},
   { 137902532, "Vintage Pistol"},
   { -598887786, "Marksman Pistol"},
   { -1045183535, "Revolver"},
   { 584646201, "AP Pistol"},
   { 911657153, "Stun Gun"},
   { 1198879012, "Flare Gun"},
   { 324215364, "Micro SMG"},
   { -619010992, "Machine Pistol"},
   { 736523883, "SMG"},
   { 2024373456, "SMG Mk2"},
   { -270015777, "Assault SMG"},
   { 171789620, "Combat PDW"},
   { -1660422300, "MG"},
   { 2144741730, "Combat MG"},
   { 3686625920, "Combat MGMk2"},
   { 1627465347, "Gusenberg"},
   { -1121678507, "Mini SMG"},
   { -1074790547, "Assault Rifle"},
   { 961495388, "Assault Rifle Mk2"},
   { -2084633992, "Carbine Rifle"},
   { 4208062921, "Carbine Rifle Mk2"},
   { -1357824103, "Advanced Rifle"},
   { -1063057011, "Special Carbine"},
   { 2132975508, "Bullpup Rifle"},
   { 1649403952, "Compact Rifle"},
   { 100416529, "Sniper Rifle"},
   { 205991906, "Heavy Sniper"},
   { 177293209, "Heavy Sniper Mk2"},
   { -952879014, "Marksman Rifle"},
   { 487013001, "Pump Shotgun"},
   { 2017895192, "Sawnoff Shotgun"},
   { -1654528753, "Bullpup Shotgun"},
   { -494615257, "Assault Shotgun"},
   { -1466123874, "Musket"},
   { 984333226, "Heavy Shotgun"},
   { -275439685, "Double Barrel Shotgun"},
   { 317205821, "Auto Shotgun"},
   { -1568386805, "Grenade Launcher"},
   { -1312131151, "RPG"},
   { 1119849093, "Minigun"},
   { 2138347493, "Firework"},
   { 1834241177, "Railgun"},
   { 1672152130, "Homing Launcher"},
   { 1305664598, "Grenade Launcher Smoke"},
   { 125959754, "Compact Launcher"},
   { -1813897027, "Grenade"},
   { 741814745, "Sticky Bomb"},
   { -1420407917, "Proximity Mine"},
   { -1600701090, "BZ Gas"},
   { 615608432, "Molotov"},
   { 101631238, "Fire Extinguisher"},
   { 883325847, "Petrol Can"},
   { 1233104067, "Flare"},
   { 600439132, "Ball"},
   { 126349499, "Snowball"},
   { -37975472, "Smoke Grenade"},
   { -1169823560, "Pipebomb"},
   { -72657034, "Parachute"}
	};
	Hash assault2 = $("weapon_assaultrifle_mk2");
	Hash carbine2 = $("weapon_carbinerifle_mk2");
	Hash combatmg2 = $("weapon_combatmg_mk2﻿");
	Hash heavysniper2 = $("weapon_heavysniper_mk2");
	Hash pistol2 = $("weapon_pistol_mk2");
	Hash smg2 = $("weapon_smg_mk2");
	Hash bullpup2 = $("WEAPON_BULLPUPRIFLE_MK2");
	Hash pumpgun2 = $("WEAPON_PUMPSHOTGUN_MK2");
	Hash marksman2 = $("WEAPON_MARKSMANRIFLE_MK2");
	Hash hell = 0x476BF155;
	Hash widow = 0xB62D1F67;
	Hash atom = 0xAF3696A1;
	Hash rail = 0x6D544C99;
	Hash hatch = 0x3813FC08;
	Hash knife = 2578778090;
	Hash nightstick = 0x678B81B1;
	Hash hammer = 0x4E875F73;
	Hash bat = 0x958A4A8F;
	Hash golf = 0x440E4788;
	Hash crowbar = 0x84BD7BFD;
	Hash pistol = 0x1B06D571;
	Hash combatpistol = 0x5EF9FEC4;
	Hash appistol = 0x22D8FE39;
	Hash pistolcal50 = 0x99AEEB3B;
	Hash microsmg = 0x13532244;
	Hash smg = 0x2BE6766B;
	Hash assaultsmg = 0xEFE7E2DF;
	Hash assaultrifle = 0xBFEFFF6D;
	Hash carbine = 0x83BF0278;
	Hash advancedrifle = 0xAF113F99;
	Hash mg = 0x9D07F764;
	Hash combatmg = 0x7FD62962;
	Hash pumphotgun = 0x1D073A89;
	Hash sawedoffshotgun = 0x7846A318;
	Hash assaultshotgun = 0xE284C527;
	Hash bullpupshotgun = 0x9D61E50F;
	Hash stungun = 0x3656C8C1;
	Hash sniper = 0x05FC3C11;
	Hash heavysniper = 0x0C472FE2;
	Hash grenadelauncher = 0xA284510B;
	Hash rpg = 0xB1CA77B1;
	Hash minigun = 0x42BF8A85;
	Hash grenade = 0x93E220BD;
	Hash stickybomb = 0x2C3731D9;
	Hash bzgas = 0xA0973D5E;
	Hash molotov = 0x24B17070;
	Hash fireex = 0x060EC506;
	Hash petrolcan = 0x34A67B97;
	Hash ball = 0x23C9F95C;
	Hash flare = 0x497FACC3;
	Hash gusenberg = 0x61012683;
	Hash specialcarbine = 0xC0A3098D;
	Hash heavypistol = 0xD205520E;
	Hash snspistol = 0xBFD21232;
	Hash bullpuprifle = 0x7F229F94;
	Hash dagger = 0x92A27487;
	Hash vintagepistol = 0x083839C4;
	Hash fireworklauncher = 0x7F7497E5;
	Hash musket = 0xA89CB99E;
	Hash heavyshotgun = 0x3AABBBAA;
	Hash marksmanrifle = 0xC734385A;
	Hash hominglauncher = 0x63AB0442;
	Hash proximitymine = 0xAB564B93;
	Hash snowball = 0x787F0BB;
	Hash flaregun = 0x47757124;
	Hash combatpdw = 0x0A3D4D34;
	Hash marksmanpistol = 0xDC4DB296;
	Hash brassknuckles = 0xD8DF3C3C;
	Hash gas = 0xFDBC8A50;
	Hash smokelauncher = 0x4DD2D;
	Hash bottle = 0xF9E6AA4B;

	void gun_locker_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<sub>("Gun Locker", SubGunLocker, [](sub* core)
			{
				core->add_option<simple_option>(("Give All Weapons"), nullptr, []
					{
						int Weapons[] = { 0x92A27487, 0x958A4A8F, 0xF9E6AA4B, 0x84BD7BFD, 0x8BB05FD7, 0x440E4788, 0x4E875F73, 0xF9DCBF2D, 0xD8DF3C3C, 0x99B507EA, 0xDD5DF8D9, 0xDFE37640, 0x678B81B1, 0x19044EE0, 0xCD274149, 0x94117305, 0x3813FC08, 0x1B06D571,  0xBFE256D4, 0x5EF9FEC4, 0x22D8FE39, 0x3656C8C1, 0x99AEEB3B, 0xBFD21232, 0x88374054 ,0xD205520E, 0x83839C4, 0x47757124, 0xDC4DB296, 0xC1B3C3D1, 0xCB96392F, 0x97EA20B8, 0xAF3696A1, 0x2B5EF5EC, 0x917F6C8C, 0x57A4368C, 0x45CD9CF3, 0x13532244, 0x2BE6766B, 0x78A97CD0, 0xEFE7E2DF, 0x0A3D4D34, 0xDB1AA450, 0xBD248B55, 0x476BF155, 0x1D073A89, 0x555AF99A, 0x7846A318, 0xE284C527, 0x9D61E50F, 0xA89CB99E, 0x3AABBBAA, 0xEF951FBB, 0x12E82D3D, 0x5A96BA4, 0xBFEFFF6D, 0x394F415C, 0x83BF0278, 0xFAD1F1C9, 0xAF113F99, 0xC0A3098D, 0x969C3D67, 0x7F229F94, 0x84D6FAFD, 0x624FE830, 0x9D1F17E6, 0xC78D71B4, 0x9D07F764, 0x7FD62962, 0xDBBD7280, 0x61012683, 0x05FC3C11, 0x0C472FE2, 0xA914799, 0xC734385A, 0x6A6C02E0, 0xB1CA77B1, 0xA284510B, 0x4DD2DC56, 0x42BF8A85, 0x7F7497E5, 0x6D544C99, 0x63AB0442, 0x0781FE4A, 0xB62D1F67, 0xDB26713A, 0x93E220BD, 0xA0973D5E, 0x24B17070, 0x2C3731D9, 0xAB564B93, 0x787F0BB, 0xBA45E8B8, 0x23C9F95C, 0xFDBC8A50, 0x497FACC3, 0x34A67B97, 0xFBAB5776, 0x060EC506, 0xBA536372, 0x184140A1 };
						for (int i = 0; i < (sizeof(Weapons) / 4); i++) {
							if (!WEAPON::HAS_PED_GOT_WEAPON(PLAYER::PLAYER_PED_ID(), Weapons[i], false))
								WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), Weapons[i], 9999, 1);

						}
						if (!WEAPON::HAS_PED_GOT_WEAPON(PLAYER::PLAYER_PED_ID(), rage::joaat("WEAPON_TACTICALRIFLE"), false))
							WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), rage::joaat("WEAPON_TACTICALRIFLE"), 9999, 1);
					});
				core->add_option<simple_option>(("Remove All Weapons"), nullptr, []
					{
						WEAPON::REMOVE_ALL_PED_WEAPONS(PLAYER::PLAYER_PED_ID(), 0);
					});
				core->add_option<simple_option>(("Give Mk2 Components"), nullptr, []
					{
						std::vector<Hash> pistolMk2{ 1329061674, 2396306288, 1140676955, 1709866683, 568543123, 2467084625 };
						std::vector<Hash> smgMk2{ 190476639, 2076495324, 2681951826, 3842157419, 1038927834, 1303784126, 2774849419, 966612367 };
						std::vector<Hash> assltRifleMk2{ 1675665560, 2640679034, 2076495324, 1108334355, 77277509, 3328927042, 2805810788, 1303784126, 1447477866, 3115408816 };
						std::vector<Hash> carbineRifleMk2{ 0x420FD713, 0x7BC4CDDC, 0x9D65907A, 0x837445AA, 0xE50C424D };
						std::vector<Hash> combatMgMk2{ 1475288264, 2640679034, 1108334355, 1060929921, 3328927042, 1303784126, 3051509595, 3607349581 };
						std::vector<Hash> heavySniperMk2{ 2313935527, 2193687427, 3159677559, 3061846192, 776198721, 2890063729, 1764221345, 277524638, 1815270123 };
						std::vector<Hash> WeaponHash{ 0xBFE256D4, 0x78A97CD0, 0xDBBD7280, 0x394F415C, 0xFAD1F1C9, 0xA914799 };
						//now lets give them
						for (Hash hash : pistolMk2)
							WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(PLAYER::PLAYER_PED_ID(), MISC::GET_HASH_KEY("WEAPON_PISTOL_MK2"), hash);

						for (Hash hash : smgMk2)
							WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(PLAYER::PLAYER_PED_ID(), MISC::GET_HASH_KEY("WEAPON_SMG_MK2"), hash);

						for (Hash hash : assltRifleMk2)
							WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(PLAYER::PLAYER_PED_ID(), MISC::GET_HASH_KEY("WEAPON_ASSAULTRIFLE_MK2"), hash);

						for (Hash hash : carbineRifleMk2)
							WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(PLAYER::PLAYER_PED_ID(), MISC::GET_HASH_KEY("WEAPON_CARBINERIFLE_MK2"), hash);

						for (Hash hash : combatMgMk2)
							WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(PLAYER::PLAYER_PED_ID(), MISC::GET_HASH_KEY("WEAPON_COMBATMG_MK2"), hash);

						for (Hash hash : heavySniperMk2)
							WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(PLAYER::PLAYER_PED_ID(), MISC::GET_HASH_KEY("WEAPON_HEAVYSNIPER_MK2"), hash);

						for (Hash hash : WeaponHash)
							WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), hash, 9999, 0);

					});
				core->add_option<break_option>(std::move(break_option()
					.SetRightText("Weapons")
				));
				core->add_option<submenu>(("Melee"), nullptr, SubMelee);
				core->add_option<submenu>(("Handguns"), nullptr, SubHandGuns);
				core->add_option<submenu>(("SMGs"), nullptr, SubSMGs);
				core->add_option<submenu>(("Shotguns"), nullptr, SubShotguns);
				core->add_option<submenu>(("Assault Rifles"), nullptr, SubAssaultRifles);
				core->add_option<submenu>(("Machine Guns"), nullptr, SubMachineGuns);
				core->add_option<submenu>(("Snipers"), nullptr, SubSnipers);
				core->add_option<submenu>(("Heavy"), nullptr, SubHeavy);
				core->add_option<submenu>(("Throwables"), nullptr, SubThrowables);
			});
		m_renderer.new_sub<sub>(("Throwables"), SubThrowables, [](sub* core)
			{
				core->add_option<simple_option>(("Grenade"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), grenade, 9999, 1);
					});
				core->add_option<simple_option>(("Sticky Bomb"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), stickybomb, 9999, 1);
					});
				core->add_option<simple_option>(("Molotov"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), molotov, 9999, 1);
					});
				core->add_option<simple_option>(("Proximity mine"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), proximitymine, 9999, 1);
					});
				core->add_option<simple_option>(("BZ Gas"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), bzgas, 9999, 1);
					});
				core->add_option<simple_option>(("Tear Gas"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), gas, 9999, 1);
					});
				core->add_option<simple_option>(("Snowball"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), snowball, 9999, 1);
					});
				core->add_option<simple_option>(("flare"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), flare, 9999, 1);
					});
			});
		m_renderer.new_sub<sub>(("Heavy"), SubHeavy, [](sub* core)
			{
				core->add_option<simple_option>(("Minigun"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), minigun, 9999, 1);
					});
				core->add_option<simple_option>(("Widowmaker"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), widow, 9999, 1);
					});
				core->add_option<simple_option>(("RPG"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), rpg, 9999, 1);
					});
				core->add_option<simple_option>(("Railgun"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), rail, 9999, 1);
					});
				core->add_option<simple_option>(("Grenade Launcher"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), grenadelauncher, 9999, 1);
					});
				core->add_option<simple_option>(("Smoke Launcher"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), smokelauncher, 9999, 1);
					});
			});
		m_renderer.new_sub<sub>(("Snipers"), SubSnipers, [](sub* core)
			{
				core->add_option<simple_option>(("Sniper"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), sniper, 9999, 1);
					});
				core->add_option<simple_option>(("Heavy Sniper"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), heavysniper, 9999, 1);
					});
				core->add_option<simple_option>(("MK2 Heavy Sniper"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), heavysniper2, 9999, 1);
					});
				core->add_option<simple_option>(("Marksman Rifle"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), marksmanrifle, 9999, 1);
					});
				core->add_option<simple_option>(("MK2 Marksman Rifle"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), marksman2, 9999, 1);
					});
			});
		m_renderer.new_sub<sub>(("MachineGuns"), SubMachineGuns, [](sub* core)
			{
				
				core->add_option<simple_option>(("Combat MG"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), combatmg, 9999, 1);
					});
				core->add_option<simple_option>(("MK2 Combat MG"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), combatmg2, 9999, 1);
					});
				core->add_option<simple_option>(("Somalia MG"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), mg, 9999, 1);
					});
				core->add_option<simple_option>(("Tommy Gun"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), gusenberg, 9999, 1);
					});
			});
		m_renderer.new_sub<sub>(("AssaultRifles"), SubAssaultRifles, [](sub* core)
			{
				
				core->add_option<simple_option>(("Carbine"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), carbine, 9999, 1);
					});
				core->add_option<simple_option>(("MK2 Carbine"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), carbine2, 9999, 1);
					});
				core->add_option<simple_option>(("Special Carbine"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), specialcarbine, 9999, 1);
					});
				core->add_option<simple_option>(("Assault Rifle"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), assaultrifle, 9999, 1);
					});
				core->add_option<simple_option>(("MK2 Assault Rifle"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), assault2, 9999, 1);
					});

			});
		m_renderer.new_sub<sub>(("Shotguns"), SubShotguns, [](sub* core)
			{
				core->add_option<simple_option>(("Pump shotgun"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), pumphotgun, 9999, 1);
					});
				core->add_option<simple_option>(("MK2 Pump shotgun"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), pumpgun2, 9999, 1);
					});
				core->add_option<simple_option>(("Sawed Off"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), sawedoffshotgun, 9999, 1);
					});
				core->add_option<simple_option>(("Bullpup"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), bullpupshotgun, 9999, 1);
					});
				core->add_option<simple_option>(("Heavy Shutgun"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), heavyshotgun, 9999, 1);
					});
				core->add_option<simple_option>(("Assault Shotgun"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), assaultshotgun, 9999, 1);
					});
				core->add_option<simple_option>(("Musket"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), musket, 9999, 1);
					});

			});
		m_renderer.new_sub<sub>(("SMGs"), SubSMGs, [](sub* core)
			{
				
				core->add_option<simple_option>(("Smg"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), smg, 9999, 1);
					});
				core->add_option<simple_option>(("MK2 Smg"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), smg2, 9999, 1);
					});
				core->add_option<simple_option>(("Micro Smg"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), microsmg, 9999, 1);
					});
				core->add_option<simple_option>(("Hellbringer"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), hell, 9999, 1);
					});
				core->add_option<simple_option>(("Combat Pdw"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), combatpdw, 9999, 1);
					});

			});
		m_renderer.new_sub<sub>(("HandGuns"), SubHandGuns, [](sub* core)
			{
				core->add_option<simple_option>(("Pistol"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), pistol, 9999, 1);
					});
				core->add_option<simple_option>(("MK2 Pistol"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), pistol2, 9999, 1);
					});
				core->add_option<simple_option>(("Combat Pistol"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), combatpistol, 9999, 1);
					});
				core->add_option<simple_option>(("AP Pistol"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), appistol, 9999, 1);
					});
				core->add_option<simple_option>(("Hand Cannon"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), pistolcal50, 9999, 1);
					});
				core->add_option<simple_option>(("Stun Gun"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), stungun, 9999, 1);
					});
				core->add_option<simple_option>(("Up-n-Atomizer"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), atom, 9999, 1);
					});
				core->add_option<simple_option>(("Heavy Pistol"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), heavypistol, 9999, 1);
					});
				core->add_option<simple_option>(("Sns Pistol"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), snspistol, 9999, 1);
					});
				core->add_option<simple_option>(("Vintage Pistol"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), vintagepistol, 9999, 1);
					});
			});
		m_renderer.new_sub<sub>(("Melee"), SubMelee, [](sub* core)
			{
				core->add_option<simple_option>(("Bottle"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), bottle, 9999, 1);
					});
				core->add_option<simple_option>(("Knife"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), knife, 9999, 1);
					});
				core->add_option<simple_option>(("Batton"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), nightstick, 9999, 1);
					});
				core->add_option<simple_option>(("Brass Knuckles"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), brassknuckles, 9999, 1);
					});
				core->add_option<simple_option>(("Hatchet"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), hatch, 9999, 1);
					});
				core->add_option<simple_option>(("Hammer"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), hammer, 9999, 1);
					});
				core->add_option<simple_option>(("Bat"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), bat, 9999, 1);
					});
				core->add_option<simple_option>(("Golf Club"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), golf, 9999, 1);
					});
				core->add_option<simple_option>(("Crowbar"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), crowbar, 9999, 1);
					});
				core->add_option<simple_option>(("Daggar"), nullptr, [=] {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), dagger, 9999, 1);
					});
			});
	}

	void gun_locker_menu::script_init() {}

	void gun_locker_menu::script_on_tick() {}

	void gun_locker_menu::script_func()
	{
		m_gun_locker_menu.script_init();
		while (true)
		{
			m_gun_locker_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}