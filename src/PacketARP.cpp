#include <cstring>
#include <iostream>
#include <iomanip>

#include "PacketARP.hh"

PacketARP::PacketARP(uint8_t *data, std::size_t len): PacketEthernet(data, len)
{
    std::copy(_payload.begin() + offsetof(struct arphdr, ar_hrd),
        _payload.begin() + offsetof(struct arphdr, ar_hrd) + 2,
        _htype.begin());
    std::copy(_payload.begin() + offsetof(struct arphdr, ar_pro),
        _payload.begin() + offsetof(struct arphdr, ar_pro) + 2,
        _ptype.begin());

    _payload.assign(_payload.begin() + sizeof(struct ether_header),
        _payload.end());
}

PacketARP::~PacketARP()
{
}

std::array<uint8_t, 2>              PacketARP::get_htype(void)
{
    return _htype;
}

void                                PacketARP::print(void) const {
    
    this->PacketEthernet::print();

    // Hardware Type
    std::cout << "Hardware Type: [" << std::hex;
    for (auto &byte : _htype)
    {
        std::cout << std::setfill('0') << std::setw(2) << (unsigned int)byte;
    }
    std::cout << std::dec << "]" << std::endl;
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
