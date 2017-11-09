#include <cstring>
#include <iostream>
#include <iomanip>

#include "Packet.hh"

Packet::Packet(uint8_t *data, std::size_t len)
{
    _data.assign(data, data + len);
}

Packet::Packet()
{
}

Packet::~Packet()
{
}

std::size_t           Packet::get_size(void) const
{
    return _data.size();
}

std::vector<uint8_t>  Packet::get_data(void) const
{
    return _data;
}

std::ostream& operator<<(std::ostream &out, Packet packet)
{
    std::vector<uint8_t>::const_iterator    it;

    out << std::hex;
    for (auto &byte : packet.get_data())
    {
        out << std::setfill('0') << std::setw(2) << (unsigned int)byte;
    }
    out << std::dec;
    return out;
}
