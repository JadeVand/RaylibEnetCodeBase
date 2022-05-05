#include <enetinterface.h>

ENetInterface::ENetInterface(){
    natpeer = NULL;
    client = NULL;
    dedicatedpeer = NULL;
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
    
    assert(dedicatedpeer);
    
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
        return false;
    }
    
    return false;
}

bool ENetInterface::dedicatedconnect(bool ishost){
    ENetAddress dedicatedaddress;
    enet_address_set_host (& dedicatedaddress, "18.168.115.193");
    dedicatedaddress.port = 8011;
    dedicatedpeer = enet_host_connect (client, & dedicatedaddress, 2, 0);
    
    assert(dedicatedpeer);
    
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
        return false;
    }
    
    return false;
}

void ENetInterface::quecompletion(std::function<void(uint8_t* data,size_t length,int result)> callback,uint32_t timeout){
    
    int result = enet_host_service(client,&event,timeout);
    if(result > 0){
        if(event.type == ENET_EVENT_TYPE_RECEIVE){
            callback(event.packet -> data,event.packet -> dataLength, result);
            
            if(event.packet -> dataLength>=sizeof(struct PacketHeader)){
                struct PacketHeader* header = (struct PacketHeader*)event.packet -> data;
                if(header->packettype == kPeerId&&header->signature == NATSIGNATURE){
                    printf("peer id was sent\n");
                    ENetAddress natpeeraddress = {0};
                    CustomENet remote = {0};
                    memcpy(&remote,event.packet -> data+sizeof(struct PacketHeader),sizeof(CustomENet));
                    memcpy(&natpeeraddress,&remote.host,sizeof(ENetAddress));
                    uint32_t remotehost = 0;
                    remotehost = natpeeraddress.host;
                    remotehost = ENET_NET_TO_HOST_32(remotehost);
                    natpeer = natpeer  = enet_host_connect (client, &natpeeraddress, 2, 0);
                    assert(natpeer);
                    int count = 20;
                    while(count >= 0){
                        --count ;
                        struct PacketHeader s = {0};
                        s.signature = GAMESIGNATURE;
                        s.packettype = kNatReserved;
                            /* Create a reliable packet of size 7 containing "packet\0" */
                            ENetPacket * packet = enet_packet_create (&s,
                                                                      sizeof(s),
                                                                      ENET_PACKET_FLAG_RELIABLE);
                            enet_peer_send (natpeer, 0, packet);
                       // enet_host_flush (client);//host)
                        ENetEvent ev ;
                        /*
                         With a 1000 delay and 10 packets being asent
                         assume after 10 packets the nat has been punched
                         since right now we have no real way of verifying..
                         
                         */
                        int r = enet_host_service (client, & ev, 1000);
                        if(r>0){
                            if (ev.type == ENET_EVENT_TYPE_RECEIVE){
                                printf("received packet\n");
                                struct PacketHeader* header = (struct PacketHeader*)event.packet -> data;
                                if(header->signature == GAMESIGNATURE && header->packettype ==kNatReserved){

                                }
                                //printf("nat punched\n");
                                enet_packet_destroy (ev.packet);
                              //  break;
                            }
                        }
                    }
                    
                }else if(header->signature == GAMESIGNATURE && header->packettype ==kNatReserved){
                    
                }else if(header->signature == NATSIGNATURE && header->packettype == kHostname){
                    printf("hostname was sent\n");
                }
                
            }
            enet_packet_destroy (event.packet);
        }
    }

}
