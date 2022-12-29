#pragma once



#include <cstdint>
#include "gta/replay.hpp"
namespace rage
{
    class CEntity : public rage::fwEntity
    {
    public:
        char gapB9[7];
        uint32_t dwordC0;
        uint32_t dwordC4;
        uint32_t dwordC8;
        uint32_t dwordCC;
    };
    static_assert(sizeof(CEntity) == 0xD0);
    class CDynamicEntity : public CEntity
    {
    public:
        class rage::netObject* m_net_object; //0x00D0
        char gapD8[16];
        uint64_t qwordE8;
    };
    static_assert(sizeof(CDynamicEntity) == 0xF0);

#pragma pack(push, 1)
    class CPhysical : public CDynamicEntity
    {
    public:
        char gapF0[144];
        uint64_t qword180;
        uint32_t m_damage_bits; //0x0188
        uint8_t m_hostility; //0x018C
        char gap18D[3];
        uint8_t byte190;
        char gap191[3];
        uint32_t dword194;
        char gap198[232];
        float m_health; //0x0280
        float m_maxhealth; //0x02A0
        uint64_t qword2A8;
        char gap2B0[72];
        uint64_t qword2F8;
        uint64_t qword300;
        uint32_t dword308;
    };
    static_assert(sizeof(CPhysical) == 0x2EC);
#pragma pack(pop)
}