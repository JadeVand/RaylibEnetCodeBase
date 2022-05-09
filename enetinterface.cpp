#include <enetinterface.h>
#include <enet/enet.h>
typedef struct SENetInterfaceContainerExtended : ENetInterfaceContainer{
    ENetHost* client;
    ENetPeer* dedicatedpeer;
    ENetPeer* natpeer;
}ENetInterfaceContainerExtended;
ENetInterface::ENetInterface(){
    a = new ENetInterfaceContainerExtended;
    memset(a,0,sizeof(ENetInterfaceContainerExtended));
}
ENetInterface::~ENetInterface(){
    delete a;
}
void ENetInterface::destroynet(){
    ENetInterfaceContainerExtended* c = (ENetInterfaceContainerExtended*)a;
    if(c->dedicatedpeer){
        enet_peer_reset(c->dedicatedpeer);
        c->dedicatedpeer = NULL;
    }
    if(c->natpeer){
        enet_peer_reset(c->natpeer);
        c->natpeer = NULL;
    }
    enet_host_destroy(c->client);
    c->client = NULL;
    enet_deinitialize();
    
}
void ENetInterface::createnet(){
    ENetInterfaceContainerExtended* c = (ENetInterfaceContainerExtended*)a;
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    WSADATA data = {0};
    WSAStartup(MAKEWORD(2,2),&data);
#endif
    ENetAddress lanaddr = {0};
    /*
     lanaddr.host = ENET_HOST_ANY;
     lanaddr.port = 0;
     */
    assert(enet_initialize ()==0);
    c->client = enet_host_create (NULL /* create a client host */,
                                  5 /* only allow 1 outgoing connection */,
                                  2 /* allow up 2 channels to be used, 0 and 1 */,
                                  0 /* assume any amount of incoming bandwidth */,
                                  0 /* assume any amount of outgoing bandwidth */
                                  );
    assert(c->client);
}
/*this function can get called repeatidly in case they type the wrong id
 *So we need to make sure whenever it gets called
 *in case a previous state is active we destroy it
 *then generate a new state to connect with
 */
bool ENetInterface::dedicatedconnect(uint64_t hn){
    ENetInterfaceContainerExtended* c = (ENetInterfaceContainerExtended*)a;
    ENetAddress dedicatedaddress;
    enet_address_set_host (& dedicatedaddress, "18.168.115.193");
    dedicatedaddress.port = 8011;
    c->dedicatedpeer = enet_host_connect (c->client, & dedicatedaddress, 2, 0);
    if(!c->dedicatedpeer){
        
        return false;
    }
    ENetEvent event;
    bool ret = true;
    int result = enet_host_service(c->client, &event, 1000) ;
    if(result > 0){
        if(event.type == ENET_EVENT_TYPE_CONNECT){
            uint64_t p = hn;
            ENetPacket * packet = enet_packet_create (&p,
                                                      sizeof(p),
                                                      ENET_PACKET_FLAG_RELIABLE);
            
            int sr = enet_peer_send (c->dedicatedpeer, 0, packet);
            if(sr != 0){
                ret = false;
            }
        }
    }else{
        enet_peer_reset(c->dedicatedpeer);
        c->dedicatedpeer = NULL;
        ret = false;
    }
    return ret;
}

bool ENetInterface::dedicatedconnect(bool ishost){
    
    ENetInterfaceContainerExtended* c = (ENetInterfaceContainerExtended*)a;
    ENetAddress dedicatedaddress;
    enet_address_set_host (& dedicatedaddress, "18.168.115.193");
    dedicatedaddress.port = 8011;
    c->dedicatedpeer = enet_host_connect (c->client, & dedicatedaddress, 2, 0);
    if(!c->dedicatedpeer){
        return false;
    }
    ENetEvent event;
    bool ret = true;
    int result = enet_host_service(c->client, &event, 1000) ;
    if(result > 0){
        if(event.type == ENET_EVENT_TYPE_CONNECT){
            uint8_t p = 0;
            if(ishost){
                p = 1;//premade host
            }else{
                p = 2;//joining queue

            }
            ENetPacket * packet = enet_packet_create (&p,
                                                      sizeof(p),
                                                      ENET_PACKET_FLAG_RELIABLE);
            
            int sr = enet_peer_send (c->dedicatedpeer, 0, packet);
            if(sr != 0){
                ret = false;
            }
        }
    }else{
        enet_peer_reset(c->dedicatedpeer);
        c->dedicatedpeer = NULL;
        ret = false;
    }
    return ret;
}
void ENetInterface::donat(CustomENet* natpeeraddr){
    ENetInterfaceContainerExtended* c = (ENetInterfaceContainerExtended*)a;
    ENetAddress* natpeeraddress = (ENetAddress*)natpeeraddr;
    c->natpeer = enet_host_connect (c->client, natpeeraddress, 2, 0);
    assert(c->natpeer);
    bool punched = false;
    uint64_t p = 0;
    while(!punched){
        NATPacket s = {0};
        s.ph.signature = GAMESIGNATURE;
        s.ph.packettype = kNatReserved;
        s.handshake = p;
        ENetPacket * packet = enet_packet_create (&s,
                                                  sizeof(s),
                                                  ENET_PACKET_FLAG_RELIABLE);
        enet_peer_send (c->natpeer, 0, packet);
        ENetEvent ev ;
        
        int r = enet_host_service (c->client, & ev, 1);
        if(r>0){
            if (ev.type == ENET_EVENT_TYPE_RECEIVE){
                if(ev.packet -> dataLength>=sizeof(PacketHeader)){
                    PacketHeader* header = (PacketHeader*)ev.packet -> data;
                    if(header->signature == GAMESIGNATURE && header->packettype == kNatReserved){
                        NATPacket* natp = (NATPacket*)ev.packet -> data;
                        if(p==0){
                            p = 0xAD;
                        }
                        
                        if(natp->handshake == 0xAD){
                            p = 0xBC;
                        }else if(natp->handshake == 0xBC){
                            punched = true;
                        }
                    }
                }
                
                enet_packet_destroy(ev.packet);
            }
        }
    }
}
void ENetInterface::quecompletion(std::function<void(uint8_t* data,size_t size)> callback,
                                                     std::function<void(void)> errorcallback,uint32_t timeout){
    ENetInterfaceContainerExtended* c = (ENetInterfaceContainerExtended*)a;
    ENetEvent event;
    int result = enet_host_service(c->client,&event,timeout);
    
    if(result > 0){
        if(event.type == ENET_EVENT_TYPE_RECEIVE){

            callback(event.packet -> data, event.packet -> dataLength);
            
            enet_packet_destroy (event.packet);
        }else if(event.type == ENET_EVENT_TYPE_DISCONNECT){
            //Ive been disconnected
            //Maybe have gamelogic handle this too
        }else if(event.type == ENET_EVENT_TYPE_NONE){
            //nothing
        }
    }else if(result < 0){
        errorcallback();
    }else{
        //do nothing
    }
    
}
void ENetInterface::sendpacketnetwork(uint8_t* p,size_t length){
    ENetInterfaceContainerExtended* c = (ENetInterfaceContainerExtended*)a;
    ENetPacket * packet = enet_packet_create (p,
                                              length,
                                              ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send (c->natpeer, 0, packet);
}

