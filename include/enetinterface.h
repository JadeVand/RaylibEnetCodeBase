
#ifndef _netinterface_h
#define _netinterface_h

#include <assert.h>
#include <functional>
#include <string>
#include <memory>
#include <vector>
#include <cstring>
#include <chrono>
uint64_t getmstimeu64();
enum MMPid : uint16_t{
    kPidNone = 0,
    kPidBadHostName = 1,
    kPidHostName = 2,
    kPidMatched = 3,
    kPidPeerId = 4,
};
enum QueType : uint8_t{
    kQueHost = 1,
    kQueQue = 2,
    kQueJoin = 3,
};
enum GamePid : uint16_t{
    
  kNatReserved = 5,
};
typedef struct SPacketHeader{
    uint16_t signature;
    uint16_t packettype;
}PacketHeader;
typedef struct SNATPacket{
    PacketHeader ph;
    uint64_t handshake;
}NATPacket;
typedef struct SCustomENet{
    uint32_t host;
    uint16_t port;
}CustomENet;
typedef struct SPacketMatchmaking{
    PacketHeader ph;//4
    uint32_t peerid;//4
    CustomENet address;//6
    uint64_t extra;//8
}PacketMatchmaking;
class PacketObject{
public:
    uint8_t* data;
    size_t length;

    PacketObject(uint8_t* data, size_t length){
        this->data = new uint8_t[length];
        memcpy(this->data,data,length);
    }
    ~PacketObject(){
        delete[] data;
        length = 0;
    }
};
#define GAMESIGNATURE 0x4843
#define NATSIGNATURE 0x4E53
typedef struct SENetInterfaceContainer{
    bool natpunched;
}ENetInterfaceContainer;
class ENetInterface{
private:

    ENetInterfaceContainer* a;
public:
    ENetInterface();
    void quecompletion();
    bool dedicatedconnect(uint32_t hostname);
    bool dedicatedconnect(bool ishost);
    void quecompletion(std::function<void(uint8_t* data,size_t size)> callback,
                       std::function<void(void)> errorcallback,uint32_t timeout);
    void destroynet();
    void createnet();

    void donat(CustomENet* natpeeraddress);
    ~ENetInterface();
    uint16_t assignedport();
    
    void sendpacketnetwork(uint8_t* p,size_t length);
};
#endif
