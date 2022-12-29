#include "node_list.hpp"
#include "enums.hpp"
#include "../pointers.hpp"

#pragma once

namespace rage
{
	class CPlayerSyncTree
	{
	public:
		char pad_0000[8]; //0x0000
		netObject* player_object; //0x0008
		char pad_0010[256]; //0x0010
	}; //Size: 0x0110

	class CPlayerAppearanceDataNode
	{
	public:
		char pad_0000[24]; //0x0000
		CPlayerSyncTree* sync_tree; //0x0018
		char pad_0020[992]; //0x0020
		uint32_t model; //0x0400
		char pad_0404[124]; //0x0404
	}; //Size: 0x0480

	class CNetworkSyncDataULBase
	{
	public:
		virtual ~CNetworkSyncDataULBase() = default;

		inline virtual void m_8() { }
		inline virtual void m_10() { }
		inline virtual void m_18() { }
		inline virtual void m_20() { }
		inline virtual void m_28() { }
		inline virtual void m_30() { }
		inline virtual void m_38() { }
		inline virtual void m_40() { }
		inline virtual void m_48() { }
		inline virtual void m_50() { }
		inline virtual void SetCloningFrequency(int player, int frequency) { }

	public:
		uint8_t pad_10h[49];
		uint8_t ownerId;
		uint8_t nextOwnerId;
		uint8_t isRemote;
		uint8_t wantsToDelete : 1; // netobj+76
		uint8_t unk1 : 1;
		uint8_t shouldNotBeDeleted : 1;
		uint8_t pad_4Dh[3];
		uint8_t pad_50h[32];
		uint32_t creationAckedPlayers; // netobj+112
		uint32_t m64;
		uint32_t m68;
		uint32_t m6C;

	public:
		inline bool IsCreationAckedByPlayer(int index)
		{
			return (creationAckedPlayers & (1 << index)) != 0;
		}
	};
#pragma pack(push, 8)
	class netSyncNodeBase
	{
	public:
		virtual ~netSyncNodeBase() = 0;
		virtual bool IsDataNode() = 0;
		virtual bool IsParentNode() = 0;

		netSyncNodeBase* m_next_sibling; //0x0000
		netSyncNodeBase* m_prev_sibling; //0x0008
		netSyncNodeBase* m_root; //0x0010
		netSyncNodeBase* m_parent; //0x0018

		uint32_t m_flags1; //0x0020
		uint32_t m_flags2; //0x0024
		uint32_t m_flags3; //0x0028

		uint32_t m_pad2; //0x002C

		netSyncNodeBase* m_first_child; //0x0030
	}; //Size: 0x0040
	static_assert(sizeof(netSyncNodeBase) == 0x40);
#pragma pack(pop)
#pragma pack(push,8)
	class netSyncTree
	{
	public:
		virtual ~netSyncTree();

		char pad_0008[8]; //0x0008
		netSyncNodeBase* m_sync_node; //0x0010
		char pad_0018[8]; //0x0018
		uint32_t m_child_node_count; //0x0020
		char pad_0024[12]; //0x0024
	}; //Size: 0x0030
	static_assert(sizeof(netSyncTree) == 0x30);
#pragma pack(pop)

	class netSyncTreeNode
	{
	public:
		char pad_0000[192]; //0x0000
		uint32_t m_player_model; //0x00C0
		uint32_t m_ped_model; //0x00C4
		uint32_t m_vehicle_model; //0x00C8
		char pad_00CC[84]; //0x00CC
		uint32_t m_pickup_model; //0x0120
		char pad_0124[44]; //0x0124
		uint32_t m_object_model; //0x0150
		char pad_0154[692]; //0x0154
	}; //Size: 0x0408

	
	class CNetGamePlayer;

	class netObjectMgrBase
	{
	public:
		class atDNetObjectNode : public atDNode<netObject*>
		{
		};

	public:
		virtual ~netObjectMgrBase() = default;

		virtual void Initialize() = 0;
		virtual void Shutdown() = 0;
		virtual void Update(bool) = 0;

		virtual void AddEntity(void*, void*) = 0;
		virtual void UnregisterNetworkObject_(void *unk, bool force) = 0;
		virtual void UnregisterNetworkObject(netObject *object, int reason, bool force1, bool force2) = 0;

		virtual void ChangeOwner(netObject *object, CNetGamePlayer *player, int migrationType) = 0;

		virtual void HandleJoiningPlayer(CNetGamePlayer *player) = 0;
		virtual void HandleLeavingPlayer(CNetGamePlayer *player) = 0;

		virtual void _0x50(CNetGamePlayer *player) = 0;
		virtual void _0x58() = 0;

		virtual void RegisterNetworkObject(netObject *object) = 0;

		virtual void PackCloneCreate(netObject *object, CNetGamePlayer *player, datBitBuffer *buffer) = 0;
		virtual bool PackCloneRemove(netObject *object, CNetGamePlayer *player, bool) = 0;

		virtual void _0x78(netObject *object, void*) = 0;
		virtual void _0x80() = 0;
		virtual void _0x88() = 0;
		virtual const char *_0x90(int) = 0;

		virtual bool HandleCloneCreate(CNetGamePlayer *source, CNetGamePlayer *target, eNetObjType object_type, std::uint16_t object_id, eNetObjectFlags object_flags, void*, std::uint32_t timestamp) = 0;
		virtual void HandleCloneCreateAck(CNetGamePlayer *source, CNetGamePlayer *target, std::uint16_t object_flags, eAckCode ack_code) = 0;

		virtual int HandleCloneSync(CNetGamePlayer *source, CNetGamePlayer *target, eNetObjType object_type, std::uint16_t object_id, void*, std::uint16_t, std::uint32_t timestamp) = 0;
		virtual void HandleCloneSyncAck(CNetGamePlayer *source, CNetGamePlayer *target, void *, std::uint16_t objectId, eAckCode ack_code) = 0;

		virtual void HandleCloneRemove(CNetGamePlayer *source, CNetGamePlayer *target, std::uint16_t object_id, int) = 0;
		virtual void HandleCloneRemoveAck(CNetGamePlayer *source, CNetGamePlayer *target, std::uint16_t object_id, eAckCode ack_code) = 0;

		virtual void _0xC8() = 0;
	public:
		atDList<atDNetObjectNode> m_objects_owned_by_player[32];
	};
}

class CNetworkObjectMgr : public rage::netObjectMgrBase
{
public:
	rage::netObject* find_object_by_id(std::uint16_t object_id, bool can_delete_be_pending)
	{
		return big::g_pointers->m_get_net_object(this, object_id, can_delete_be_pending);
	}
};