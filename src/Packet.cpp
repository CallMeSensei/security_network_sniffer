#include <cstring>
#include <iostream>
#include <sstream>
#include <iomanip>

#include "Packet.hh"

Packet::Packet(uint8_t *data, std::size_t len)
{
    _data.assign(data, data + len);
    _payload.assign(data, data + len);
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

std::size_t                         Packet::get_payload_size(void) const {
    
    return _payload.size();
}
    
std::vector<uint8_t>                Packet::get_payload(void) const {

    return _payload;
}

std::string                         Packet::to_string(void) {

    std::stringstream   ss;

    ss << std::hex;
    for (auto &byte : _data)
    {
        ss << std::setfill('0') << std::setw(2) << (unsigned int)byte;
    }
    ss << std::dec;
    return ss.str();
}

void                    Packet::print(void) const {

    std::cout << std::hex;
    for (auto &byte : this->get_data())
    {
        std::cout << std::setfill('0') << std::setw(2) << (unsigned int)byte;
    }
    std::cout << std::dec << std::endl;
}

std::ostream& operator<<(std::ostream &out, Packet packet)
{
    out << std::hex;
    for (auto &byte : packet.get_data())
    {
        out << std::setfill('0') << std::setw(2) << (unsigned int)byte;
    }
    out << std::dec;
    return out;
}
