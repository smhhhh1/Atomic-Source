#pragma once

#include <cstdint>
#include "gta/player.hpp"
#pragma pack(push,4)
class CPlayerGameStateDataNode
{
public:
	char pad_0000[192]; //0x0000
	uint32_t m_player_state; //0x00C0
	bool m_controls_disabled_by_script; //0x00C4
	bool m_is_max_armor_and_health_default; //0x00C5
	bool unk_000C6; //0x00C6
	bool m_is_spectating; //0x00C7
	bool m_is_antagonistic_to_another_player; //0x00C8
	bool m_never_target; //0x00C9
	bool m_use_kinematic_physics; //0x00CA
	bool unk_000CB; //0x00CB
	bool unk_00CC; //0x00CC
	bool unk_00CD; //0x00CD
	bool unk_00CE; //0x00CE
	bool unk_00CF; //0x00CF
	bool unk_00D0; //0x00D0
	bool unk_00D1; //0x00D1
	bool m_random_peds_flee; //0x00D2
	bool m_every_ped_back_away; //0x00D3
	bool unk_00D4; //0x00D4
	bool m_is_invincible; //0x00D5
	bool unk_00D6; //0x00D6
	bool unk_00D7; //0x00D7
	bool unk_00D8; //0x00D8
	bool unk_00D9; //0x00D9
	bool m_bullet_proof; //0x00DA
	bool m_fire_proof; //0x00DB
	bool m_explosion_proof; //0x00DC
	bool m_collision_proof; //0x00DD
	bool m_melee_proof; //0x00DE
	bool m_water_proof; //0x00DF
	bool m_steam_proof; //0x00E0
	bool unk_00E1; //0x00E1
	bool unk_00E2; //0x00E2
	bool unk_00E3; //0x00E3
	bool unk_00E4; //0x00E4
	bool unk_00E5; //0x00E5
	bool unk_00E6; //0x00E6
	bool unk_00E7; //0x00E7
	bool unk_00E8; //0x00E8
	bool unk_00E9; //0x00E9
	bool unk_00EA; //0x00EA
	bool unk_00EB; //0x00EB
	bool unk_00EC; //0x00EC
	bool unk_00ED; //0x00ED
	bool unk_00EE; //0x00EE
	bool unk_00EF; //0x00EF
	bool unk_00F0; //0x00F0
	bool unk_00F1; //0x00F1
	bool unk_00F2; //0x00F2
	bool unk_00F3; //0x00F3
	bool unk_00F4; //0x00F4
	bool unk_00F5; //0x00F5
	bool unk_00F6; //0x00F6
	bool unk_00F7; //0x00F7
	bool unk_00F8; //0x00F8
	bool unk_00F9; //0x00F9
	bool unk_00FA; //0x00FA
	bool unk_00FB; //0x00FB
	uint32_t unk_00FC; //0x00FC
	uint32_t m_mobile_ring_state; //0x0100
	int32_t m_player_team; //0x0104
	float m_air_drag_multiplier; //0x0108
	uint32_t m_max_health; //0x010C
	uint32_t m_max_armor; //0x0110
	uint32_t unk_0114; //0x0114
	uint16_t unk_0118; //0x0118
	uint32_t m_override_receive_chat; //0x011C
	uint32_t m_override_send_chat; //0x0120
	bool unk_0124; //0x0124
	bool unk_0125; //0x0125
	bool unk_0126; //0x0126
	bool unk_0127; //0x0127
	uint16_t m_spectating_net_id; //0x0128
	uint8_t m_antagonistic_to_player_id; //0x012C
	uint8_t m_tutorial_index; //0x012B
	uint8_t m_tutorial_instance_id; //0x012C
	char pad_012D[2]; //0x012D
	uint32_t unk_0130; //0x0130
	uint32_t unk_0134; //0x0134
	bool m_is_overriding_voice_proximity; //0x0138
	char pad_0139[7]; //0x0139
	float m_voice_proximity_x; //0x0140
	float m_voice_proximity_y; //0x0144
	float m_voice_proximity_z; //0x0148
	float m_voice_proximity_radius_maybe; //0x014C
	uint32_t unk_0150; //0x0150
	uint32_t unk_0154; //0x0154
	bool unk_0158; //0x0158
	uint32_t m_decor_count; //0x015C
	uint32_t m_decor_type[3]; // 0x0160
	uint32_t m_decor_value[3]; // 0x016C
	uint32_t m_decor_name_hash[3]; // 0x0178
	bool m_friendly_fire_allowed; //0x0184
	bool unk_0185; //0x0185
	uint8_t m_current_garage_instance_index; //0x0186
	uint8_t m_current_property_id; //0x0187
	uint8_t unk_0188; //0x0188
	uint8_t unk_0189; //0x0189
	bool unk_018A; //0x018A
	bool unk_018B; //0x018B
	float m_weapon_defence_modifier; //0x018C
	float m_weapon_defence_modifier_2; //0x0190
	bool m_is_overriding_population_control_sphere; //0x0194
	char pad_0195[11]; //0x0195
	float m_population_control_sphere_x; //0x01A0
	float m_population_control_sphere_y; //0x01A4
	float m_population_control_sphere_z; //0x01A8
	uint16_t unk_01AC; //0x01AC
	uint16_t unk_01AE; //0x01AE
	uint16_t unk_01B0; //0x01B0
	bool pad_01B2; //0x01B2
	bool unk_01B3; //0x01B3
	bool m_no_collision; //0x01B4
	bool unk_01B5; //0x01B5
	bool unk_01B6; //0x01B6
	bool m_super_jump; //0x01B7
	bool unk_01B8; //0x01B8
	bool unk_01B9; //0x01B9
	uint16_t unk_01BA; //0x01BA
	uint32_t unk_01BC; //0x01BC
	float unk_01C0; //0x01C0
	float m_weapon_damage_modifier;  //0x01C4 Divisor: 0x3F800000
	float m_melee_weapon_damage_modifier;  //0x01C8 Divisor: 0x3F800000
	float unk_01CC; //0x01CC
	bool unk_01D0; //0x01D0
	char pad_01D1[15]; //0x01D1
	float unk_01E0; //0x01E0
	float unk_01E4; //0x01E4
	float unk_01E8; //0x01E8
	uint32_t unk_01EC; //0x01EC
	uint8_t unk_01F0; //0x01F0
	uint8_t unk_01F1; //0x01F1
	bool unk_01F2; //0x01F2
	uint8_t unk_01F3; //0x01F3
}; //Size: 0x01F4
static_assert(sizeof(CPlayerGameStateDataNode) == 0x1F4);
#pragma pack(pop)


#pragma pack(push, 1)
class CPlayerGamerDataNode
{
public:
	char pad_0000[192]; //0x0000
	ClanData m_clan_data; //0x00C0
	bool m_need_crew_rank_sysflags; //0x0178
	bool m_need_crew_rank_title; //0x0179
	char m_crew_rank_title[25]; //0x017A
	bool m_has_started_transition; //0x0193
	bool m_has_transition_info; //0x0194
	char m_transition_info_buffer[125]; //0x0195
	bool m_is_rockstar_dev; //0x0212
	bool m_is_rockstar_qa; //0x0213
	bool m_is_cheater; //0x0214
	char pad_0215[3]; //0x0215
	uint32_t m_matchmaking_group; //0x0218
	bool m_need_mute_data; //0x021C
	char pad_021D[3]; //0x021D
	int32_t m_mute_count; //0x0220
	int32_t m_mute_talkers_count; //0x0224
	uint32_t unk_0228; //0x0228
	bool m_has_communication_privilege; //0x022C
	char pad_022D[3]; //0x022D
	int32_t unk_0230; //0x0230
	char pad_0234[620]; //0x0234
}; //Size: 0x04A0
static_assert(sizeof(CPlayerGamerDataNode) == 0x4A0);
#pragma pack(pop)


class CVehicleControlDataNode
{
public:
	char pad_0000[281]; //0x0000
	bool m_unk; //0x0119
	char pad_011A[38]; //0x011A
}; //Size: 0x0140

#pragma pack(push,4)
class CPhysicalAttachDataNode
{
public:
	char pad_0000[192]; //0x0000
	bool m_attached; //0x00C0
	bool unk_00C1; //0x00C1
	uint16_t m_attached_to; //0x00C2
	char pad_00C4[12]; //0x00C4
	rage::fvector3 m_offset; //0x00D0
	char pad_00DC[4]; //0x00DC
	rage::fvector4 m_orientation; //0x00E0
	rage::fvector3 m_parent_offset; //0x00F0
	char pad_00FC[4]; //0x00FC
	uint16_t m_other_attach_bone; //0x0100
	uint16_t m_attach_bone; //0x0102
	uint32_t m_attach_flags; //0x0104
	bool m_allow_initial_separation; //0x0108
	char pad_00109[3]; //0x0109
	float unk_010C; //0x010C
	float unk_0110; //0x0110
	bool unk_0114; //0x0114
	bool unk_0115; //0x0115
	bool m_is_cargo_vehicle; //0x0116
}; //Size: 0x0118
static_assert(sizeof(CPhysicalAttachDataNode) == 0x118);
#pragma pack(pop)

#pragma pack(push,4)
class CPedAttachDataNode
{
public:
	char pad_0000[192]; //0x0000
	rage::fvector3 m_offset; //0x00C0
	char pad_00CC[4]; //0x00CC
	rage::fvector4 m_orientation; //0x00D0
	uint16_t m_attached_to; //0x00E0
	uint16_t m_attachment_bone; //0x00E2
	uint32_t m_attachment_flags; //0x00E4
	float m_heading_1; //0x00E8
	float m_heading_2; //0x00EC
	bool m_attached; //0x00F0
	bool unk_00F1; //0x00F1
};
static_assert(sizeof(CPedAttachDataNode) == 0xF4);
#pragma pack(pop)


#pragma pack(push, 4)
class CDoorCreationDataNode
{
public:
	char pad_0000[192]; //0x0000
	uint32_t m_model; //0x00C0
	char pad_00C4[12]; //0x00C4
	rage::fvector3 m_pos; //0x00D0
	char pad_00DC[12]; //0x00DC
	bool m_is_script_door; //0x00E8
	bool m_player_wants_control; //0x00E9
}; //Size: 0x00EC
static_assert(sizeof(CDoorCreationDataNode) == 0xEC);
#pragma pack(pop)



#pragma pack(push, 8)
class CPickupCreationDataNode
{
public:
	char pad_0000[192]; //0x0000
	bool m_has_placement; //0x00C0
	char pad_00C1[7]; //0x00C1
	uint64_t* unk_struct_00C8; //0x00C8
	uint32_t unk_00D0; //0x00D0
	uint16_t unk_00D4; //0x00D4
	char pad_00D6[66]; //0x00D6
	uint32_t m_pickup_hash; //0x0118
	uint32_t m_amount; //0x011C
	uint32_t m_custom_model; //0x0120
	uint32_t m_life_time; //0x0124
	uint32_t m_weapon_component[11]; //0x0128
	uint32_t m_num_weapon_components; //0x0154
	uint32_t m_tint_index; //0x0158
	bool m_player_gift; //0x015C
	bool unk_015D; //0x015D
	char pad_015E[6]; //0x015E
	uint32_t unk_0164; //0x0164
	bool unk_0168; //0x0168
}; //Size: 0x0170
static_assert(sizeof(CPickupCreationDataNode) == 0x170);
#pragma pack(pop)

#pragma pack(push,4)
class CPedCreationDataNode
{
public:
	char pad_0000[192]; //0x0000
	uint32_t m_pop_type;  //0x00C0
	uint32_t m_model; //0x00C4
	uint32_t m_random_seed; //0x00C8
	uint32_t m_max_health; //0x00CC
	bool m_in_vehicle; //0x00D0
	char pad_0xD1[1]; //0x00D1
	uint16_t m_vehicle_id; //0x00D2
	uint32_t m_vehicle_seat; //0x00D4
	bool m_has_prop; //0x00D8
	char pad_0xD9[3];  //0x00D9
	uint32_t m_prop_model; //0x00DC
	bool m_is_standing; //0x00E0
	bool m_is_respawn_object_id; //0x00E1
	bool m_is_respawn_flagged_for_removal; //0x00E2
	bool m_has_attr_damage_to_player; //0x00E3
	uint8_t m_attribute_damage_to_player; //0x00E4
	uint32_t m_voice_hash; //0x00E8
}; //Size: 0x00EC
static_assert(sizeof(CPedCreationDataNode) == 0xEC);
#pragma pack(pop)


#pragma pack(push,4)
class CVehicleCreationDataNode
{
public:
	char pad_0000[192]; //0x00B0
	uint32_t m_pop_type; //0x00C0
	uint32_t m_random_seed; //0x00C4
	uint32_t m_model; //0x00C8
	uint32_t m_vehicle_status; //0x00CC
	uint32_t m_max_health; //0x00D0
	uint32_t m_creation_token; //0x00D4
	bool m_car_budget; //0x00D8
	bool m_needs_to_be_hotwired; //0x00D9
	bool m_tires_dont_burst; //0x00DA
	char pad_00DB[165]; //0x00DB
}; //Size: 0x0180
static_assert(sizeof(CVehicleCreationDataNode) == 0x180);
#pragma pack(pop)

#pragma pack(push,8)
class CObjectCreationDataNode
{
public:
	char pad_0000[192]; //0x0000
	uint16_t unk_00C0; //0x00C0
	char pad_0xC2[14]; //0x00C2
	rage::fvector4 m_object_orientation; //0x00D0
	char pad_00E0[30]; //0x00E0
	rage::fvector3 m_object_position; //0x0100
	char pad_010C[4]; //0x010C
	rage::fvector3 m_dummy_position; //0x010E
	char pad_011A[20]; //0x011C
	rage::fvector3 m_script_grab_position; //0x0130
	char pad_013C[12]; //0x013C
	float m_script_grab_radius; //0x0148
	uint32_t m_created_by; //0x014C
	uint32_t m_model; //0x0150
	uint32_t m_frag_group_index; //0x0154
	uint32_t m_ownership_token; //0x0158
	uint32_t unk_015C; //0x015C
	bool m_no_reassign; //0x0160
	bool unk_0161; //0x0161
	bool m_player_wants_control; //0x0162
	bool m_has_init_physics; //0x0163
	bool m_script_grabbed_from_world; //0x0164
	bool m_has_frag_group; //0x0165
	bool m_is_broken; //0x0166
	bool m_has_exploded; //0x0167
	bool m_keep_registered; //0x0168
	bool unk_0169; //0x0169
	bool unk_016A; //0x016A
	bool unk_016B; //0x016B
}; //Size: 0x016C
static_assert(sizeof(CObjectCreationDataNode) == 0x16C);
#pragma pack(pop)

#pragma pack(push, 4)
class CPedComponents
{
public:
	uint32_t m_component_bitset; //0x0
	char pad_0x4[4]; //0x4
	uint32_t unk_0x8[12]; //0x8
	uint32_t m_drawables[12]; //0x38
	uint32_t m_textures[12]; //0x68
	uint32_t m_palettes[12]; //0x98

	inline uint32_t get_drawable(int index)
	{
		if (m_component_bitset & (1 << index))
		{
			return m_drawables[index];
		}

		return 0;
	}

	inline uint32_t get_texture(int index)
	{
		if (m_component_bitset & (1 << index))
		{
			return m_textures[index];
		}

		return 0;
	}

	inline uint32_t get_palette(int index)
	{
		if (m_component_bitset & (1 << index))
		{
			return m_palettes[index];
		}

		return 0;
	}
};
static_assert(sizeof(CPedComponents) == 0xC8);
#pragma pack(pop)


#pragma pack(push, 4)
class CPlayerAppearanceDataNode
{
public:
	char pad_0x0[192]; //0xB0
	uint32_t unk_0xC0[56]; //0xC0
	class CPedComponents components; //0x1A0
	char pad_0x268[8]; //0x268
	uint32_t unk_0x270[6]; //0x270
	uint32_t unk_0x288[6]; //0x288
	char pad_0x2A0[8]; //0x2A0
	float unk_0x2A8; //0x2A8
	uint8_t unk_0x2AC; //0x2AC
	uint8_t unk_0x2AD; //0x2AD
	char pad_0x2AE[26]; //0x2AE
	float m_shape_mix; //0x2C8
	float m_skin_mix; //0x2CC
	float m_third_mix; //0x2D0
	float unk_0x2D4; //0x2D4
	float unk_0x2D8[13]; //0x2D8
	float unk_0x30C[13]; //0x30C
	float unk_0x340[20]; //0x340
	uint8_t unk_0x390[13]; //0x390
	uint8_t unk_0x39D[13]; //0x39D
	uint8_t unk_0x3AA[13]; //0x3AA
	uint8_t m_shape_first; //0x3B7
	uint8_t m_shape_second; //0x3B8
	uint8_t m_shape_third; //0x3B9
	uint8_t m_skin_first; //0x3BA
	uint8_t m_skin_second; //0x3BB
	uint8_t m_skin_third; //0x3BC
	uint8_t unk_0x3BD[13]; //0x3BD
	uint8_t unk_0x3CA[11]; //0x3CA
	int16_t unk_0x3D6; //0x3D6
	uint8_t unk_0x3D8; //0x3D8
	uint8_t unk_0x3D9; //0x3D9
	char pad_0x3DA[1]; //0x3DA
	bool unk_0x3DB; //0x3DB
	bool unk_0x3DC; //0x3DC
	char pad_0x3DD[3]; //0x3DD
	uint32_t unk_0x3E0; //0x3E0
	uint32_t unk_0x3E4; //0x3E4
	uint32_t unk_0x3E8; //0x3E8
	uint32_t unk_0x3EC; //0x3EC
	uint32_t unk_0x3F0; //0x3F0
	float unk_0x3F4; //0x3F4
	float unk_0x3F8; //0x3F8
	float unk_0x3FC; //0x3FC
	uint32_t unk_0x400; //0x400
	uint32_t unk_0x404; //0x404
	uint32_t unk_0x408; //0x408
	uint32_t unk_0x40C; //0x40C
	uint32_t unk_0x410; //0x410
	bool unk_0x414; //0x414
	bool unk_0x415; //0x415
	bool unk_0x416; //0x416
	bool unk_0x417; //0x417
	bool unk_0x418; //0x418
	bool unk_0x419; //0x419
	uint32_t unk_0x41C; //0x41C
	uint32_t m_model_hash; //0x420
	uint32_t m_voice_hash; //0x424
	uint32_t m_phone_mode; //0x428
	uint32_t unk_0x42C; //0x42C
	uint8_t m_parachute_tint_index; //0x430
	uint8_t m_parachute_pack_tint_index; //0x431
	uint16_t m_respawn_object; //0x432
	bool m_has_head_blend_data; //0x434
	bool unk_0x435; //0x435
	bool m_has_respawn_object; //0x436
	char pad_0x437; //0x437
	uint32_t unk_0x438_clip_maybe; //0x438
	uint32_t unk_0x43C; //0x43C
	uint32_t unk_0x440; //0x440
	bool unk_0x444; //0x444
	bool unk_0x445; //0x445
	bool unk_0x446; //0x446
	uint8_t unk_0x447; //0x447
	uint16_t unk_0x448; //0x448
	uint16_t unk_0x44A; //0x44A
	uint16_t unk_0x44C; //0x44C
	bool unk_0x44E; //0x44E
	bool unk_0x44F; //0x44F
	bool unk_0x450; //0x450
	uint8_t unk_0x451; //0x451
	uint32_t unk_0x452; //0x452
	uint32_t unk_0x456; //0x456
};
static_assert(sizeof(CPlayerAppearanceDataNode) == 0x45C);
#pragma pack(pop)


#pragma pack(push, 2)
class CSectorDataNode
{
public:
	char pad_0x0[192]; //0x0
	uint16_t m_pos_x; //0xC0
	uint16_t m_pos_y; //0xC2
	uint16_t m_pos_z; //0xC4
};
static_assert(sizeof(CSectorDataNode) == 0xC6);
#pragma pack(pop)

struct CPedMovementDataNode
{
	BYTE gap0[192];
	BYTE m_is_walking;
	BYTE m_is_running;
	float m_flag_01;
	float m_flag_02;
	float m_walk_speed;//not sure if correct
	float m_run_speed;//not sure if correct
};

enum eVehicleGadgetType : uint32_t
{
	FORKS,
	SEARCH_LIGHT,
	PICK_UP_ROPE_WITH_HOOK,
	PICK_UP_ROPE_WITH_MAGNET,
	DIGGER_ARM,
	HANDLER_FRAME,
	BOMB_BAY,
};

#pragma pack(push,4)
class CVehicleGadgetData
{
public:
	eVehicleGadgetType m_gadget_type; //0x0000
	uint8_t m_data[94]; //0x0004
}; //Size: 0x64
static_assert(sizeof(CVehicleGadgetData) == 0x64);

class CVehicleGadgetDataNode
{
public:
	char pad_0000[192]; //0x0000
	bool m_has_parent_offset; //0x00C0
	char pad_00C1[15]; //0x00C1
	uint32_t m_parent_offset_x; //0x00D0
	uint32_t m_parent_offset_y; //0x00D4
	uint32_t m_parent_offset_z; //0x00D8
	uint32_t m_parent_offset_w; //0x00DC
	uint32_t m_gadget_count; //0x00E0
	CVehicleGadgetData m_gadget_data[2]; //0x00E4
}; //Size: 0x01AC
static_assert(sizeof(CVehicleGadgetDataNode) == 0x1AC);
#pragma pack(pop)


#pragma pack(push, 4)
struct CDecorator
{
	uint32_t m_type;
	uint32_t m_value;
	uint32_t m_name_hash;
};

class CDynamicEntityGameStateDataNode
{
public:
	char pad_0000[192]; // 0x0000
	uint32_t m_interior_index; // 0x00C0
	bool unk_00C4; // 0x00C4
	bool unk_00C5; // 0x00C5
	uint32_t m_decor_count; // 0x00C8
	CDecorator m_decors[12]; // 0x00CC
}; //Size: 0x15C
static_assert(sizeof(CDynamicEntityGameStateDataNode) == 0x15C);
#pragma pack(pop)



struct CPedInventoryDataNode
{
	char pad_0000[5232];
	uint32_t m_items[105];
	uint32_t m_num_items;
	uint32_t m_ammos[65];
	uint32_t m_ammo_quantities[65];
	uint32_t m_num_ammos;
	uint8_t unk_1680[105];
	uint8_t unk_16E9[105];
	char pad_1680[1260];
	bool m_infinite_ammos[65];
	bool m_ammo_all_infinite;
};



#pragma pack(push,4)
class CTrainGameStateDataNode
{
public:
	char pad_0000[192]; //0x0000
	bool m_is_engine; //0x00C0
	bool m_is_caboose; //0x00C1
	bool m_is_mission_train; //0x00C2
	bool m_direction; //0x00C3
	bool m_has_passenger_carriages; //0x00C4
	bool m_render_derailed; //0x00C5
	bool unk_00C6; //0x00C6
	bool unk_00C7; //0x00C7
	uint16_t m_engine_id; //0x00C8
	int8_t m_train_config_index; //0x00CA
	int8_t m_carriage_config_index; //0x00CB
	int8_t m_track_id; //0x00CC
	char pad_00CD[3]; //0x00CD
	float m_distance_from_engine; //0x00D0
	float m_cruise_speed; //0x00D4
	uint16_t m_linked_to_backward_id; //0x00D8
	uint16_t m_linked_to_forward_id; //0x00DA
	uint32_t m_train_state; //0x0DC
	bool unk_00E0; //0x00E0
	bool m_force_doors_open; //0x0E1
}; //Size: 0x00E4
static_assert(sizeof(CTrainGameStateDataNode) == 0xE4);
#pragma pack(pop)

#pragma pack(push,4)
class CPlayerCreationDataNode
{
public:
	char pad_0000[192]; //0x0000
	uint32_t m_model; //0x00C0
	uint32_t m_num_scars; //0x00C4
	char unk_struct_0xC8[192]; //0x00C8
	uint32_t unk_0188; //0x0188
	char pad_018C[4]; //0x018C
	char m_scar_struct[176]; //0x0190
	bool unk_0240; //0x0240
	char pad_0241[19]; //0x0241
}; //Size: 0x0254
static_assert(sizeof(CPlayerCreationDataNode) == 0x254);
#pragma pack(pop)

#pragma pack(push, 1)
class ClonedTakeOffPedVariationInfo
{
public:
	char pad_0000[112]; //0x0000
	uint32_t m_parachute_override_model_hash; //0x0070
	char pad_0074[20]; //0x0074
}; //Size: 0x0088
static_assert(sizeof(ClonedTakeOffPedVariationInfo) == 0x88);
#pragma pack(pop)