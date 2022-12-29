#pragma once
#pragma pack(push, 4)

#include "common.hpp"
#include "fwddec.hpp"

namespace rage {


	class phArchetype
	{
	public:
		char pad_0000[32]; //0x0000
		class phBound* m_bound; //0x0020
		char pad_0028[16]; //0x0028
	}; //Size: 0x0038
	static_assert(sizeof(phArchetype) == 0x38);

	class phArchetypePhys : public phArchetype
	{
	public:
		char pad_0038[28]; //0x0028
		float m_water_collision; //0x0054
		char pad_0058[40]; //0x0058
	}; //Size: 0x0080
	static_assert(sizeof(phArchetypePhys) == 0x80);

	class phArchetypeDamp : public phArchetypePhys
	{
	public:
		char pad_0080[96]; //0x0080
	}; //Size: 0x00E0
	static_assert(sizeof(phArchetypeDamp) == 0xE0);
	class phBoundBase : public pgBase
	{
	};

	enum class eBoundType : uint8_t
	{
		SPHERE,
		CAPSULE,
		BOX = 3,
		GEOMETRY,
		BVH = 8,
		COMPOSITE = 10,
		DISC = 12,
		CYLINDER,
		PLANE = 15
	};

#pragma pack(push,4)
	class phBound : public phBoundBase {
	public:
		eBoundType m_type; //0x0010
		uint8_t m_flags; //0x0011
		uint16_t m_part_index; //0x0012
		float m_radius_around_centroid; //0x0014
		char pad_0018[8]; //0x0018
		fvector4 m_bounding_box_max_xyz_margin_w; //0x0020
		fvector4 m_bounding_box_min_xyz_ref_count_w; //0x0030
		fvector4 m_centroid_offset_xyz_material_id_0_w; //0x0040
		fvector4 m_cg_offset_xyz_material_id_1_w; //0x0050
		fvector4 m_volume_distribution; //0x0060
	}; //Size: 0x0070
	static_assert(sizeof(phBound) == 0x70);
#pragma pack(pop)

#pragma pack(push,1)
	class phBoundCapsule : public phBound
	{
	public:
		float m_capsule_half_height;
		uint64_t unk_0074;
		uint32_t unk_007C;
	}; //Size: 0x0080
	static_assert(sizeof(phBoundCapsule) == 0x80);
#pragma pack(pop)
	template<typename T>
	union matrix34
	{
		T data[3][4];
		struct { struct { T x, y, z, w; } rows[3]; };
	};
	typedef matrix34<float> fmatrix34;
#pragma pack(push,8)
	class phBoundComposite : public phBound
	{
	public:
		class phBound** m_bounds; //0x0070
		fmatrix34* m_current_matrices; //0x0078
		fmatrix34* m_last_matrices; //0x0080
		fvector3* unk_0088; //0x0088
		uint32_t* m_type_and_include_flags; //0x0090
		uint32_t* m_owned_type_and_include_flags; //0x0098
		uint16_t m_max_num_bounds; //0x00A0
		uint16_t m_num_bounds; //0x00A2
		char pad_00A4[4]; //0x00A4
		void* unk_00A8; //0x00A8
	}; //Size: 0x00B0
	static_assert(sizeof(phBoundComposite) == 0xB0);
#pragma pack(pop)
}
#pragma pack(push, 1)
class CNavigation
{
public:
	char pad_0000[16]; //0x0000
	class rage::phArchetypeDamp* m_damp; //0x0010
	char pad_0018[8]; //0x0018
	rage::fvector3 m_right; //0x0020
	char pad_002C[4]; //0x002C
	rage::fvector3 m_forward; //0x0030
	char pad_003C[4]; //0x003C
	rage::fvector3 m_up; //0x0040
	char pad_004C[4]; //0x004C
	rage::fvector3 m_position; //0x0050
}; //Size: 0x0060
static_assert(sizeof(CNavigation) == 0x5C);
#pragma pack(pop)


namespace rage
{
	class fwDrawData
	{
	public:
		char pad_0000[904]; //0x0000
		uint8_t m_primary_color; //0x0388
		char pad_0389[3]; //0x0389
		uint8_t m_pearlescent; //0x038C
		char pad_038D[3]; //0x038D
		uint8_t m_secondary_color; //0x0390
		char pad_0391[15]; //0x0391
		uint8_t m_neon_blue; //0x03A0
		uint8_t m_neon_green; //0x03A1
		uint8_t m_neon_red; //0x03A2
		char pad_03A3[15]; //0x03A3
		uint8_t m_spoiler; //0x03B2
		uint8_t m_bumper_front; //0x03B3
		uint8_t m_bumper_rear; //0x03B4
		uint8_t m_sideskirts; //0x03B5
		uint8_t m_exhaust; //0x03B6
		uint8_t m_frame; //0x03B7
		uint8_t m_grille; //0x03B8
		uint8_t m_hood; //0x03B9
		uint8_t m_fenders; //0x03BA
		uint8_t m_bullbars; //0x03BB
		uint8_t m_roof; //0x03BC
		char pad_03BD[3]; //0x03BD
		uint8_t m_ornaments; //0x03C0
		char pad_03C1[1]; //0x03C1
		uint8_t m_dail_design; //0x03C2
		uint8_t m_sunstrips; //0x03C3
		uint8_t m_seats; //0x03C4
		uint8_t m_steering_wheel; //0x03C5
		uint8_t m_column_shifter_levers; //0x03C6
		char pad_03C7[2]; //0x03C7
		uint8_t m_truck_beds; //0x03C9
		char pad_03CA[4]; //0x03CA
		uint8_t m_roll_cages; //0x03CE
		uint8_t m_skid_plate; //0x03CF
		uint8_t m_secondary_light_surrounds; //0x03D0
		uint8_t m_hood_accessories; //0x03D1
		uint8_t m_doors; //0x03D2
		uint8_t m_snorkel; //0x03D3
		uint8_t m_livery; //0x03D4
		char pad_03D5[1]; //0x03D5
		uint8_t m_engine; //0x03D6
		uint8_t m_brakes; //0x03D7
		uint8_t m_transmission; //0x03D8
		uint8_t m_horn; //0x03D9
		uint8_t m_suspension; //0x03DA
		uint8_t m_armor; //0x03DB
		char pad_03DC[1]; //0x03DC
		uint8_t m_turbo; //0x03DD
		char pad_03DE[3]; //0x03DE
		uint8_t m_xenon; //0x03E1
		uint8_t m_tire_design; //0x03E2
		char pad_03E3[16]; //0x03E3
		uint8_t m_truck_bed; //0x03F3
		char pad_03F4[5]; //0x03F4
		uint8_t m_wheel_color; //0x03F9
		char pad_03FA[5]; //0x03FA
		uint8_t m_window; //0x03FF
		char pad_0400[2]; //0x0400
		uint8_t m_neon_left; //0x0402
		uint8_t m_neon_right; //0x0403
		uint8_t m_neon_front; //0x0404
		uint8_t m_neon_rear; //0x0405
	}; //Size: 0x0406
	static_assert(sizeof(fwDrawData) == 0x406);
#pragma pack(push, 1)
	class fwEntity : public fwExtensibleBase
	{
	public:
		class CBaseModelInfo* m_model_info;
		char gap28;
		uint8_t m_entity_type;
		char gap2A[2];
		uint8_t m_invisible; //0x002C
		char gap2D[3]; //0x002D
		class CNavigation* m_navigation; //0x0030
		char gap38[16]; //0x0038
		class rage::fwDrawData* m_draw_data; //0x0048
		char gap50[16]; //0x0050
		rage::fvector3 m_right; //0x0060
		char gap6C[4]; //0x006C
		rage::fvector3 m_forward; //0x0070
		char gap7C[4]; //0x007C
		rage::fvector3 m_up; //0x0080
		char gap8C[4]; //0x008C
		rage::fvector3 m_position; //0x0090
		char gap9C[4]; // 0x009C
		uint64_t qwordA0;
		uint32_t dwordA8;
		uint32_t dwordAC;
		uint32_t dwordB0;
		char gapB4[4];
		std::uint8_t byteB8;

		inline Vector3 GetPosition()
		{
			return { m_position.x, m_position.y, m_position.z };
		}
	};
	static_assert(sizeof(fwEntity) == 0xB9);
#pragma pack(pop)
	class Matrix4x4
	{
	public:
		union
		{
			rage::fvector4 m_Vectors[4] = {}; // Use your own vec4 class
			float m_Float[4 * 4];
		};
	};
	static_assert(sizeof(Matrix4x4) == sizeof(float) * (4 * 4));


	class CVehicle : public fwEntity
	{
	public:
		char pad_018C[2716]; //0x018C
		//class CPed* m_driver; //0x0C28
		//class CPed* m_occupants[8]; //0x0C30
	}; //Size: 0x018C

	

	class CPed : public fwEntity
	{
	public:
		char pad_018C[2972]; //0x018C
		class CVehicle* m_last_vehicle; //0x0D28
		char pad_0D30[908]; //0x0D30
		int8_t m_decal_index; //0x10BC
		int8_t m_decal_info; //0x10BD
		char pad_10BE[10]; //0x10BE
		class CPlayerInfo* m_player_info; //0x10C8
	};

	class CPlayerInfo
	{
	public:
		char pad_0000[52]; //0x0000
		uint32_t m_internal_ip; //0x0034
		uint16_t m_internal_port; //0x0038
		char pad_003A[2]; //0x003A
		uint32_t m_relay_ip; //0x003C
		uint16_t m_relay_port; //0x0040
		char pad_0042[2]; //0x0042
		uint32_t m_external_ip; //0x0044
		uint16_t m_external_port; //0x0048
		char pad_004A[30]; //0x004A
		uint64_t m_rockstar_id; //0x0068
		char pad_0070[12]; //0x0070
		char m_name[20]; //0x007C
		char pad_0090[184]; //0x0090
		float m_swim_speed; //0x0148
		float m_run_speed; //0x014C
		char pad_0150[81]; //0x0150
		bool m_is_rockstar_dev; //0x01A1
		char pad_01A2[1]; //0x01A2
		bool m_is_cheater; //0x01A3
		char pad_01A4[11]; //0x01A4
		bool m_is_online; //0x01AF
		char pad_01B0[24]; //0x01B0
		class CPed* m_ped; //0x01C8
		char pad_01D0[40]; //0x01D0
		uint32_t m_frame_flags; //0x01F8
		char pad_01FC[28]; //0x01FC
		uint32_t m_player_controls; //0x0218
		char pad_021C[1524]; //0x021C
		bool m_is_wanted; //0x0810
		char pad_0811[3]; //0x0811
		int32_t m_wanted_level_display; //0x0814
		int32_t m_wanted_level; //0x0818
	}; //Size: 0x081C

	class CObject : public fwEntity
	{
	public:
	}; //Size: 0x018C

	class CBaseModelInfo
	{
	public:
		char pad_0000[24]; //0x0000
		uint32_t m_model; //0x0018
	}; //Size: 0x001C

	class CPedFactory
	{
	public:
		virtual ~CPedFactory() = default;
		class CPed* m_local_ped; //0x0008
	}; //Size: 0x0010

	class CObjectHandle
	{
	public:
		class CObject* m_object; //0x0000
		int32_t m_handle; //0x0008
		char pad_000C[4]; //0x000C
	}; //Size: 0x0010
	static_assert(sizeof(CObjectHandle) == 0x10, "CObjectHandle is not properly sized");

	class CObjectList
	{
	public:
		class CObjectHandle m_objects[2300]; //0x0000
	}; //Size: 0x8FC0

	class CObjectInterface
	{
	public:
		char pad_0000[344]; //0x0000
		class CObjectList* m_object_list; //0x0158
		int32_t m_max_objects; //0x0160
		char pad_0164[4]; //0x0164
		int32_t m_cur_objects; //0x0168

		rage::CObject* get_object(const int& index)
		{
			if (index < m_max_objects)
				return m_object_list->m_objects[index].m_object;
			return nullptr;
		}
	}; //Size: 0x016C

	class CPedHandle
	{
	public:
		class CPed* m_ped; //0x0000
		int32_t m_handle; //0x0008
		char pad_000C[4]; //0x000C
	}; //Size: 0x0010
	static_assert(sizeof(CPedHandle) == 0x10, "CPedHandle is not properly sized");

	class CPedList
	{
	public:
		class CPedHandle m_peds[256]; //0x0000
	}; //Size: 0x1000

	class CPedInterface
	{
	public:
		char pad_0000[256]; //0x0000
		class CPedList* m_ped_list; //0x0100
		int32_t m_max_peds; //0x0108
		char pad_010C[4]; //0x010C
		int32_t m_cur_peds; //0x0110

		CPed* get_ped(const int& index)
		{
			if (index < m_max_peds)
				return m_ped_list->m_peds[index].m_ped;
			return nullptr;
		}
	}; //Size: 0x0114

	class CVehicleHandle
	{
	public:
		class CVehicle* m_vehicle; //0x0000
		int32_t m_handle; //0x0008
		char pad_000C[4]; //0x000C
	}; //Size: 0x0010
	static_assert(sizeof(CVehicleHandle) == 0x10, "CVehicleHandle is not properly sized");

	class CVehicleList
	{
	public:
		class CVehicleHandle m_vehicles[300]; //0x0000
	}; //Size: 0x12C0

	class CVehicleInterface
	{
	public:
		char pad_0000[384]; //0x0000
		class CVehicleList* m_vehicle_list; //0x0180
		int32_t m_max_vehicles; //0x0188
		char pad_018C[4]; //0x018C
		int32_t m_cur_vehicles; //0x0190

		CVehicle* get_vehicle(const int& index)
		{
			if (index < m_max_vehicles)
				return m_vehicle_list->m_vehicles[index].m_vehicle;
			return nullptr;
		}
	}; //Size: 0x0194


	class CReplayInterface
	{
	public:
		char pad_0000[16]; //0x0000
		class CVehicleInterface* m_vehicle_interface; //0x0010
		class CPedInterface* m_ped_interface; //0x0018
		char pad_0020[8]; //0x0020
		class CObjectInterface* m_object_interface; //0x0028
	}; //Size: 0x0030
}
#pragma pack(pop)