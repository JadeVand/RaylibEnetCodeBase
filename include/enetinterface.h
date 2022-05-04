
#ifndef _netinterface_h
#define _netinterface_h
#include <enet/enet.h>
#include <assert.h>

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
};
#endif
