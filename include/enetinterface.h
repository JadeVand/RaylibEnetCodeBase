
#ifndef _netinterface_h
#define _netinterface_h
#include <enet/enet.h>
#include <assert.h>
#include <functional>

struct PacketHeader{
    uint16_t signature;
    uint16_t packettype;
};
enum Pid : uint16_t{
    kInvalidHost = 1,
    kHostname = 2,
    kPeerId = 3,
};
struct CustomENet{
    ENetAddress host;
};
struct NatPunchPacket{
    struct PacketHeader p;
    uint32_t extra;
};
class ENetInterface{
private:
    
    ENetHost* client;
    ENetPeer* dedicatedpeer;
    ENetPeer* natpeer;
    ENetEvent event;
    bool natpunched;
    uint32_t natpacketid;
    
public:
    ENetInterface();
    void quecompletion();
    bool dedicatedconnect(uint64_t hostname);
    bool dedicatedconnect(bool ishost);
    void quecompletion(std::function<void(uint8_t* data,size_t length,int result)> callback,uint32_t timeout);
    
    
    uint16_t gamesignature = 0x4843;
    uint16_t natsignature = 0x4E53;
};
#endif
