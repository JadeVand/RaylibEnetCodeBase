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
    natpunched = false;
    natpacketid = 0;
    
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
    if(!natpunched&&natpeer != NULL){
        printf("packetid:%d\n",natpacketid);
        struct NatPunchPacket s = {0};
        s.p.signature = gamesignature;
        s.p.packettype = 5;
        s.extra = natpacketid;
            /* Create a reliable packet of size 7 containing "packet\0" */
            ENetPacket * packet = enet_packet_create (&s,
                                                      sizeof(s),
                                                      ENET_PACKET_FLAG_RELIABLE);
            enet_peer_send (natpeer, 0, packet);

    }

    int result = enet_host_service(client,&event,timeout);
    if(result > 0){
        if(event.type == ENET_EVENT_TYPE_RECEIVE){
            callback(event.packet -> data,event.packet -> dataLength, result);
            
            if(event.packet -> dataLength>=sizeof(struct PacketHeader)){
                struct PacketHeader* header = (struct PacketHeader*)event.packet -> data;
                if(header->packettype == kPeerId&&header->signature == natsignature){
                    
                    ENetAddress natpeeraddress = {0};
                    CustomENet remote = {0};
                    memcpy(&remote,event.packet -> data+sizeof(struct PacketHeader),sizeof(CustomENet));
                    memcpy(&natpeeraddress,&remote.host,sizeof(ENetAddress));
                    uint32_t remotehost = 0;
                    remotehost = natpeeraddress.host;
                    remotehost = ENET_NET_TO_HOST_32(remotehost);
                    natpeer  = enet_host_connect (client, &natpeeraddress, 2, 0);
                    assert(natpeer);
                    
                    
                }else if(header->signature == gamesignature && header->packettype == 5){
                    /*
                     Both peers will send their punch count (peerpunchcount)(the amount of time they've received a punch from the other
                     
                     if peerpunchcount exceeds 10 we stop sending; however, they still keep sending until
                     our punch count exceeds 10 on their side,
                     when both peers have received 10 punches we stop punching because that's just overkill
                     inducing mental and physical trauma to the machines
                     */
                    //peer sent nat message
                    struct NatPunchPacket* p = (struct NatPunchPacket*)event.packet -> data;
                    printf("nat:%d\n",p->extra);
                    natpacketid = 0xAD;
                    if(p->extra==0xAD){
                        natpunched = true;
                    }
                }
                
            }
            enet_packet_destroy (event.packet);
        }
    }

}
