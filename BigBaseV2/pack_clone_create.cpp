#include "hooking.hpp"
#include "network_selected_crashes.h"
#include "lists.h"
#include "CObject.h"
namespace big
{
	enum eNetObjectTypes : uint16_t {
		NetObjectAutomobile,
		NetObjectBike,
		NetObjectBoat,
		NetObjectDoor,
		NetObjectHeli,
		NetObjectObject,
		NetObjectPed,
		NetObjectPickup,
		NetObjectPickupPlacement,
		NetObjectPlane,
		NetObjectSubmarine,
		NetObjectPlayer,
		NetObjectTrailer,
		NetObjectTrain,
		INVALID
	};
	void hooks::hk_pack_clone_create(CNetworkObjectMgr* mgr, rage::netObject* netObject, CNetGamePlayer* src, rage::datBitBuffer* buffer)
	{
		if (netObject)
		{
			if (netObject->m_object_type > NetObjectAutomobile && netObject->m_object_type < INVALID) {
				return;
			}
			if (!is_valid_ptr(netObject)) {
				return;
			}
			if (src->m_player_id >= 0 && src->m_player_id < 34)
			{
				return;
			}

		}
		
		return g_hooking->og_pack_clone_create.get_original<decltype(&hk_pack_clone_create)>()(mgr, netObject, src, buffer);;
	}
}