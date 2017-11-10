
#include <iostream>

#include "PacketFactory.hh"

Packet          *PacketFactory::create(uint8_t *data, std::size_t len) {

    Packet      *p;

    p = new PacketEthernet(data, len);

    if (static_cast<PacketEthernet*>(p)->get_type() ==
        std::array<uint8_t, 2>{0x08, 0x00}) {

        delete p;
        p = new PacketIP(data, len);
        std::cout << "New PacketIP" << std::endl;
    }
    else if (static_cast<PacketEthernet*>(p)->get_type() ==
        std::array<uint8_t, 2>{0x08, 0x06}) {

        delete p;
        p = new PacketARP(data, len);
        std::cout << "New PacketARP" << std::endl;
    }
    return p;
}