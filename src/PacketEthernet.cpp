#include <cstring>
#include <iostream>
#include <iomanip>

#include "PacketEthernet.h"

PacketEthernet::PacketEthernet(uint8_t *data, std::size_t len): Packet(data, len)
{
    std::copy(_data.begin(), _data.begin() + 6, _mac_destination.begin());
    std::copy(_data.begin() + 6, _data.begin() + 12, _mac_source.begin());
    std::copy(_data.begin() + 12, _data.begin() + 14, _type.begin());
}

PacketEthernet::~PacketEthernet()
{
}

std::array<uint8_t, 6>              PacketEthernet::get_mac_destination(void)
{
    return _mac_destination;
}

std::array<uint8_t, 6>              PacketEthernet::get_mac_source(void)
{
    return _mac_source;
}

std::array<uint8_t, 2>              PacketEthernet::get_type(void)
{
    return _type;
}

std::ostream& operator<<(std::ostream &out, PacketEthernet packet)
{
    std::vector<uint8_t>::const_iterator    it;

    // MAC Destination
    out << "MAC Destination: [" << std::hex;
    for (auto &byte : packet.get_mac_destination())
    {
        out << std::setfill('0') << std::setw(2) << (unsigned int)byte;
    }
    out << std::dec << "]" << std::endl;

    // MAC Source
    out << "MAC Source: [" << std::hex;
    for (auto &byte : packet.get_mac_source())
    {
        out << std::setfill('0') << std::setw(2) << (unsigned int)byte;
    }
    out << std::dec << "]" << std::endl;

    // Ethertype
    out << "Ethertype: [" << std::hex;
    for (auto &byte : packet.get_type())
    {
        out << std::setfill('0') << std::setw(2) << (unsigned int)byte;
    }
    out << std::dec << "]" << std::endl;
    return out;
}