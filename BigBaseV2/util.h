#pragma once

#pragma once
#include "natives.hpp"
#include "script.hpp"
#include "pointers.hpp"
#include "gta/joaat.hpp"
#include <chrono>
#include <random>
#include <imgui.h>
namespace big {

	inline Vector3 rot_to_direction(Vector3 rot) {
		float radiansZ = rot.z * 0.0174532924f;
		float radiansX = rot.x * 0.0174532924f;
		float num = abs((float)cos((double)radiansX));
		Vector3 dir;
		dir.x = (float)((double)((float)(-(float)sin((double)radiansZ))) * (double)num);
		dir.y = (float)((double)((float)cos((double)radiansZ)) * (double)num);
		dir.z = (float)sin((double)radiansX);
		return dir;
	}
	inline bool raycast(Entity* ent)
	{
		BOOL hit;
		Vector3 endCoords;
		Vector3 surfaceNormal;

		Vector3 camCoords = CAM::GET_GAMEPLAY_CAM_COORD();
		Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(2);
		Vector3 dir = rot_to_direction(rot);
		Vector3 farCoords;

		farCoords.x = camCoords.x + dir.x * 1000;
		farCoords.y = camCoords.y + dir.y * 1000;
		farCoords.z = camCoords.z + dir.z * 1000;

		int ray = SHAPETEST::_START_SHAPE_TEST_RAY(camCoords.x, camCoords.y, camCoords.z, farCoords.x, farCoords.y, farCoords.z, -1, 0, 7);
		SHAPETEST::GET_SHAPE_TEST_RESULT(ray, &hit, &endCoords, &surfaceNormal, ent);

		return (bool)hit;
	}
	inline bool take_control_of(Entity ent)
	{
		if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(ent)) return true;
		for (uint8_t i = 0; !NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(ent) && i < 10; i++)
		{
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(ent);

			script::get_current()->yield();
		}
		if (!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(ent)) return false;

		int netHandle = NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(ent);
		NETWORK::SET_NETWORK_ID_CAN_MIGRATE(netHandle, true);

		return true;
	}
	inline Vector3 add(Vector3 vectorA, Vector3 vectorB) {
		Vector3 result;
		result.x = vectorA.x;
		result.y = vectorA.y;
		result.z = vectorA.z;
		result.x += vectorB.x;
		result.y += vectorB.y;
		result.z += vectorB.z;
		return result;
	}

	inline Vector3 multiply(Vector3 vector, float x) {
		Vector3 result;
		result.x = vector.x;
		result.y = vector.y;
		result.z = vector.z;
		result.x *= x;
		result.y *= x;
		result.z *= x;
		return result;
	}

	inline float get_distance(Vector3* pointA, Vector3* pointB) {
		float a_x = pointA->x;
		float a_y = pointA->y;
		float a_z = pointA->z;
		float b_x = pointB->x;
		float b_y = pointB->y;
		float b_z = pointB->z;
		double x_ba = (double)(b_x - a_x);
		double y_ba = (double)(b_y - a_y);
		double z_ba = (double)(b_z - a_z);
		double y_2 = y_ba * y_ba;
		double x_2 = x_ba * x_ba;
		double sum_2 = y_2 + x_2;
		return(float)sqrt(sum_2 + z_ba);
	}

	inline float get_vector_length(Vector3* vector) {
		double x = (double)vector->x;
		double y = (double)vector->y;
		double z = (double)vector->z;
		return(float)sqrt(x * x + y * y + z * z);
	}
	inline float degToRad(float degs) {
		return degs * 3.141592653589793f / 180.f;
	}

	inline Hash $(std::string str) {
		return rage::joaat(str);
	}
	inline float must_Distance(Vector3 pointA, Vector3 pointB) {
		float a_x = pointA.x;
		float a_y = pointA.y;
		float a_z = pointA.z;
		float b_x = pointB.x;
		float b_y = pointB.y;
		float b_z = pointB.z;
		double x_ba = (double)(b_x - a_x);
		double y_ba = (double)(b_y - a_y);
		double z_ba = (double)(b_z - a_z);
		double y_2 = y_ba * y_ba;
		double x_2 = x_ba * x_ba;
		double sum_2 = y_2 + x_2;
		return(float)sqrt(sum_2 + z_ba);
	}
	inline float dist(Vector3 p1, Vector3 p2)
	{
		float x = p1.x - p2.x;
		float y = p1.y - p2.y;
		float z = p1.z - p2.z;
		return SYSTEM::SQRT(x * x + y * y + z * z);
	}
	inline bool __shooting(Ped ped) {
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(ped, 1);
		return PED::IS_PED_SHOOTING_IN_AREA(ped, coords.x, coords.y, coords.z, coords.x, coords.y, coords.z, true, true);
	}
	inline float GravityGunGoto(float aimX, float entityX)
	{
		static float GravityGunVeloPos;

		if (aimX > 0 && entityX > 0) GravityGunVeloPos = aimX - (entityX);

		if (aimX < 0 && entityX < 0) GravityGunVeloPos = aimX - (entityX);

		if (aimX > 0 && entityX < 0) GravityGunVeloPos = aimX + (entityX);

		if (aimX < 0 && entityX > 0) GravityGunVeloPos = aimX + (entityX);

		return GravityGunVeloPos;
	}
	inline double DegreeToRadian(float deg) {
		double radian = (3.14159265359 / 180) * deg;
		return (float)radian;
	}
	inline Vector3 RotationToDirection(Vector3 rotation) {
		float x = DegreeToRadian(rotation.x);
		float z = DegreeToRadian(rotation.z);

		float num = abs(cos(x));

		return Vector3
		{
			-sin(z) * num,
			cos(z) * num,
			sin(x)
		};
	}
	inline Vector3 coordsOf(Entity entity) {
		return ENTITY::GET_ENTITY_COORDS(entity, 1);
	}
	inline float get_distance(Vector3 pointA, Vector3 pointB) {
		float a_x = pointA.x;
		float a_y = pointA.y;
		float a_z = pointA.z;
		float b_x = pointB.x;
		float b_y = pointB.y;
		float b_z = pointB.z;
		double x_ba = (double)(b_x - a_x);
		double y_ba = (double)(b_y - a_y);
		double z_ba = (double)(b_z - a_z);
		double y_2 = y_ba * y_ba;
		double x_2 = x_ba * x_ba;
		double sum_2 = y_2 + x_2;
		return(float)sqrt(sum_2 + z_ba);
	}
	inline Vector3 multiplyVector(Vector3 vector, float inc) {
		vector.x *= inc;
		vector.y *= inc;
		vector.z *= inc;
		vector.x *= inc;
		vector.y *= inc;
		vector.z *= inc;
		return vector;
	}
	inline Vector3 addVector(Vector3 vector, Vector3 vector2) {
		vector.x += vector2.x;
		vector.y += vector2.y;
		vector.z += vector2.z;
		vector.x += vector2.x;
		vector.y += vector2.y;
		vector.z += vector2.z;
		return vector;
	}
	inline float distanceBetween(Vector3 A, Vector3 B) {
		return MISC::GET_DISTANCE_BETWEEN_COORDS(A.x, A.y, A.z, B.x, B.y, B.z, 1);
	}

	inline double distance_between_vectors(Vector3 a, Vector3 b)
	{
		return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2) + pow((a.z - b.z), 2));
	}
	inline int rndInt(int start, int end) {
		return MISC::GET_RANDOM_INT_IN_RANGE(start, end);
	}
	inline float pythag(ImVec2 src, ImVec2 dst)
	{
		return sqrtf(pow(src.x - dst.x, 2) + pow(src.y - dst.y, 2));
	}

	inline float pythagVec3(Vector3 src, Vector3 dst)
	{
		return sqrtf(pow(src.x - dst.x, 2) + pow(src.y - dst.y, 2) + pow(src.z - dst.z, 2));
	}
	inline void tpToDestination(Entity e, Vector3 coords)
	{
		ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), coords.x, coords.y, coords.z + 1.0f, FALSE, FALSE, FALSE, TRUE);
	}
	inline Vector3 get_blip_marker()
	{
		static Vector3 zero;
		Vector3 coords;

		bool blipFound = false;
		// search for marker blip
		int blipIterator = HUD::_GET_WAYPOINT_BLIP_SPRITE();
		for (Blip i = HUD::GET_FIRST_BLIP_INFO_ID(blipIterator); HUD::DOES_BLIP_EXIST(i) != 0; i = HUD::GET_NEXT_BLIP_INFO_ID(blipIterator))
		{
			if (HUD::GET_BLIP_INFO_ID_TYPE(i) == 4)
			{
				coords = HUD::GET_BLIP_INFO_ID_COORD(i);
				blipFound = true;
				break;
			}
		}
		if (blipFound)
		{
			return coords;
		}
		return zero;
	}
	inline bool load_ground_at_3dcoord(Vector3& location)
	{
		float groundZ;
		const uint8_t attempts = 10;

		for (uint8_t i = 0; i < attempts; i++)
		{
			// Only request a collision after the first try failed because the location might already be loaded on first attempt.
			for (uint16_t z = 0; i && z < 1000; z += 100)
			{
				STREAMING::REQUEST_COLLISION_AT_COORD(location.x, location.y, (float)z);

				script::get_current()->yield();
			}

			if (MISC::GET_GROUND_Z_FOR_3D_COORD(location.x, location.y, 1000.f, &groundZ, false, false))
			{
				location.z = groundZ + 1.f;

				return true;
			}

			script::get_current()->yield();
		}

		location.z = 1000.f;

		return false;
	}
	inline void tpToMarker()
	{
		Vector3 coords = get_blip_marker();

		if (coords.x == 0 && coords.y == 0)
		{
			return;
		}

		// get entity to teleport
		Entity entity = PLAYER::PLAYER_PED_ID();
		if (PED::IS_PED_IN_ANY_VEHICLE(entity, 0))
		{
			entity = PED::GET_VEHICLE_PED_IS_USING(entity);
		}
		bool worldLevel = false;
		static float groundCheckHeight[] =
		{ 100.0, 150.0, 50.0, 0.0, 200.0, 250.0, 300.0, 350.0, 400.0, 450.0, 500.0, 550.0, 600.0, 650.0, 700.0, 750.0, 800.0 };
		for (int i = 0; i < 800 / sizeof(float); i++)
		{
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(entity, coords.x, coords.y, groundCheckHeight[i], 0, 0, 1);
			script::get_current()->yield();
			if (MISC::GET_GROUND_Z_FOR_3D_COORD(coords.x, coords.y, groundCheckHeight[i], &coords.z, 0, 0))
			{
				worldLevel = true;
				coords.z += 3.0;
				break;
			}
		}
		if (!worldLevel)
		{
			coords.z = 1000.0;
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xFBAB5776, 1, 0);
		}

		tpToDestination(entity, coords);
	}

}