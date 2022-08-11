#include <RenderPacket.h>

bool RenderPacket::compare(RenderPacket const &p1,RenderPacket const &p2){
    if(p1.priority != p2.priority){
        return p1.priority>p2.priority;
    if(p1.vbuff!=p2.vbuff)
        return p1.vbuff<p2.vbuff;
    return p1.first_texture<p2.first_texture;
    }
}
bool operator<(RenderPacket const &p1,RenderPacket const &p2){
    return RenderPacket::compare(p1,p2);
}