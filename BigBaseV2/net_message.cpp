#include "hooking.hpp"
#include "player_service.hpp"
#include "natives.hpp"
#include "gta_util.hpp"
#include "Network.hpp"
#include "gta/script_id.hpp"
#include "network_toolkit.h"
#include "notify.h"
#include "network_notifications.h"
namespace big
{
	bool get_msg_type(rage::eNetMessage& msgType, rage::datBitBuffer& buffer)
	{
		uint32_t pos;
		uint32_t magic;
		uint32_t length;
		uint32_t extended{};
		if ((buffer.m_flagBits & 2) != 0 || (buffer.m_flagBits & 1) == 0 ? (pos = buffer.m_curBit) : (pos = buffer.m_maxBit),
			buffer.m_bitsRead + 15 > pos || !buffer.ReadDword(&magic, 14) || magic != 0x3246 || !buffer.ReadDword(&extended, 1)) {
			msgType = rage::eNetMessage::MsgInvalid;
			return false;
		}
		length = extended ? 16 : 8;
		if ((buffer.m_flagBits & 1) == 0 ? (pos = buffer.m_curBit) : (pos = buffer.m_maxBit), length + buffer.m_bitsRead <= pos && buffer.ReadDword((uint32_t*)&msgType, length))
			return true;
		else
			return false;
	}

	void gamer_handle_deserialize(rage::rlGamerHandle& hnd, rage::datBitBuffer& buf)
	{
		constexpr int PC_PLATFORM = 3;
		if ((hnd.m_platform = buf.Read<uint8_t>(8)) != PC_PLATFORM)
			return;

		buf.ReadInt64((int64_t*)&hnd.m_rockstar_id, 64);
		hnd.unk_0009 = buf.Read<uint8_t>(8);
	}
	static void script_id_deserialize(CGameScriptId& id, rage::datBitBuffer& buffer)
	{
		id.m_hash = buffer.Read<uint32_t>(32);
		id.m_timestamp = buffer.Read<uint32_t>(32);

		if (buffer.Read<bool>(1))
			id.m_position_hash = buffer.Read<uint32_t>(32);

		if (buffer.Read<bool>(1))
			id.m_instance_id = buffer.Read<int32_t>(8);
	}

	bool hooks::hk_net_message(void* netConnectionManager, void* a2, rage::netConnection::InFrame* frame)
	{
		
		return g_hooking->og_net_message.get_original<decltype(&hooks::hk_net_message)>()(netConnectionManager, a2, frame);
	}
}
