
#ifndef _netinterface_h
#define _netinterface_h
#include <enet/enet.h>
#include <assert.h>

class ENetInterface{
private:
    ENetHost* client;
    ENetPeer* dedicatedpeer;
    ENetPeer* natpeer;
public:
    ENetInterface();
    void quecompletion();
};
#endif
