
#include "PacketFactory.hh"

Packet          *PacketFactory::create(uint8_t *data, std::size_t len) {

    return new PacketEthernet(data, len);
}