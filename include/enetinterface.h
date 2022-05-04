
#ifndef _netinterface_h
#define _netinterface_h
#include <enet/enet.h>
#include <assert.h>
#include <functional>
class ENetInterface{
private:
    ENetHost* client;
    ENetPeer* dedicatedpeer;
    ENetPeer* natpeer;
    ENetEvent event;
public:
    ENetInterface();
    void quecompletion();
    bool dedicatedconnect(uint64_t hostname);
    bool dedicatedconnect(bool ishost);
    void quecompletion(std::function<void(uint8_t* data,size_t length,int result)> callback,uint32_t timeout);
};
#endif
