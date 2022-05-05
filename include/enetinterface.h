
#ifndef _netinterface_h
#define _netinterface_h
#include <enet/enet.h>
#include <assert.h>
#include <functional>
#include <string>
struct PacketHeader{
    uint16_t signature;
    uint16_t packettype;
};
enum Pid : uint16_t{
    kInvalidHost = 1,
    kHostname = 2,
    kPeerId = 3,
};
enum GamePid : uint16_t{
    
  kNatReserved = 5,
};
struct CustomENet{
    ENetAddress host;
};

class PacketObject{
public:
    uint8_t* data;
    size_t length;

    PacketObject(uint8_t* data, size_t length){
        data = new uint8_t[length];
        memcpy(this->data,data,length);
    }
    ~PacketObject(){
        delete[] data;
        length = 0;
    }
};
#define GAMESIGNATURE 0x4843
#define NATSIGNATURE 0x4E53
class ENetInterface{
private:
    
    ENetHost* client;
    ENetPeer* dedicatedpeer;
    ENetPeer* natpeer;
    ENetEvent event;
    bool natpunched ;
public:
    ENetInterface();
    void quecompletion();
    bool dedicatedconnect(uint64_t hostname);
    bool dedicatedconnect(bool ishost);
    void quecompletion(std::function<void(uint8_t* data,size_t length,int result)> callback,uint32_t timeout);

};
#endif
