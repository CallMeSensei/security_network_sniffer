#include <cstring>
#include <iostream>
#include <iomanip>

#include "PacketEthernet.hh"
#include "PacketARP.hh"

PacketARP::PacketARP(uint8_t *data, std::size_t len): PacketEthernet(data, len)
{
    std::copy(_data.begin() + 14, _data.begin() + 16, _htype.begin());
}

PacketARP::~PacketARP()
{
}

std::array<uint8_t, 2>              PacketARP::get_htype(void)
{
    return _htype;
}


std::ostream& operator<<(std::ostream &out, PacketARP packet)
{
    std::vector<uint8_t>::const_iterator    it;

    // Hardware Type
    out << "Hardware Type: [" << std::hex;
    for (auto &byte : packet.get_htype())
    {
        out << std::setfill('0') << std::setw(2) << (unsigned int)byte;
    }
    out << std::dec << "]" << std::endl;

    return out;
}
