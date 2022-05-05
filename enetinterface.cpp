#include <enetinterface.h>

ENetInterface::ENetInterface(){
    natpeer = NULL;
    client = NULL;
    dedicatedpeer = NULL;
    createnet();
    
}
void ENetInterface::destroynet(){
    enet_host_destroy(client);
    if(dedicatedpeer){
        enet_peer_reset(dedicatedpeer);
        dedicatedpeer = NULL;
    }
    if(natpeer){
        enet_peer_reset(natpeer);
        natpeer = NULL;
    }
    enet_deinitialize();
    
}
void ENetInterface::createnet(){
    assert(enet_initialize ()==0);
    client = enet_host_create (NULL /* create a client host */,
                               5 /* only allow 1 outgoing connection */,
                               2 /* allow up 2 channels to be used, 0 and 1 */,
                               0 /* assume any amount of incoming bandwidth */,
                               0 /* assume any amount of outgoing bandwidth */
                               );
    assert(client);
}
bool ENetInterface::dedicatedconnect(uint64_t hn){
    
    uint64_t p = hn;
    
    ENetAddress dedicatedaddress;
    enet_address_set_host (& dedicatedaddress, "18.168.115.193");
    dedicatedaddress.port = 8011;
    dedicatedpeer = enet_host_connect (client, & dedicatedaddress, 2, 0);

    
    if (enet_host_service(client, &event, 1000) > 0 &&
        event.type == ENET_EVENT_TYPE_CONNECT) {
        
        ENetPacket * packet = enet_packet_create (&p,
                                                  sizeof(p),
                                                  ENET_PACKET_FLAG_RELIABLE);
        
        enet_peer_send (dedicatedpeer, 0, packet);
        enet_host_flush (client);
        
        return true;
        
    } else {
        enet_peer_reset(dedicatedpeer);
        dedicatedpeer = NULL;
        return false;
    }
    
    return false;
}

bool ENetInterface::dedicatedconnect(bool ishost){
    ENetAddress dedicatedaddress;
    enet_address_set_host (& dedicatedaddress, "18.168.115.193");
    dedicatedaddress.port = 8011;
    dedicatedpeer = enet_host_connect (client, & dedicatedaddress, 2, 0);

    if (enet_host_service(client, &event, 1000) > 0 &&
        event.type == ENET_EVENT_TYPE_CONNECT) {
        uint8_t p = 0;
        if(ishost){
            p = 1;//premade host
        }else{
            p = 2;//joining queue
        }
        ENetPacket * packet = enet_packet_create (&p,
                                                  sizeof(p),
                                                  ENET_PACKET_FLAG_RELIABLE);
        
        enet_peer_send (dedicatedpeer, 0, packet);
        enet_host_flush (client);
        
        return true;
        
    } else {
        enet_peer_reset(dedicatedpeer);
        dedicatedpeer = NULL;
        return false;
    }
    
    return false;
}
void ENetInterface::donat(ENetAddress* natpeeraddress){
    natpeer = enet_host_connect (client, natpeeraddress, 2, 0);
    assert(natpeer);
    int count = 20;
    while(count >= 0){
        --count ;
        PacketHeader s = {0};
        s.signature = GAMESIGNATURE;
        s.packettype = kNatReserved;

            ENetPacket * packet = enet_packet_create (&s,
                                                      sizeof(s),
                                                      ENET_PACKET_FLAG_RELIABLE);
            enet_peer_send (natpeer, 0, packet);
       // enet_host_flush (client);//host)
        ENetEvent ev ;

        int r = enet_host_service (client, & ev, 1000);
        if(r>0){
            if (ev.type == ENET_EVENT_TYPE_RECEIVE){
                PacketHeader* header = (PacketHeader*)event.packet -> data;
                if(header->signature == GAMESIGNATURE && header->packettype ==kNatReserved){
                    
                }
                enet_packet_destroy(ev.packet);
            }
        }
    }
}
void ENetInterface::quecompletion(std::function<void(std::unique_ptr<PacketObject>)> callback,
                                  std::function<void(void)> errorcallback,uint32_t timeout){
    
    int result = enet_host_service(client,&event,timeout);
    if(result > 0){
        if(event.type == ENET_EVENT_TYPE_RECEIVE){
            
            std::unique_ptr<PacketObject> packet = std::make_unique<PacketObject>(event.packet -> data,event.packet -> dataLength);
            callback(std::move(packet));
             
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
/*
 

 */
