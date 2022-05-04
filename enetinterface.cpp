#include <enetinterface.h>

ENetInterface::ENetInterface(){
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
    
    if(result>0&&ENET_EVENT_TYPE_RECEIVE){
        callback(event.packet -> data,event.packet -> dataLength, result);
        enet_packet_destroy (event.packet);
    }
}
