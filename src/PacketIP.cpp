#include <cstring>
#include <iostream>
#include <sstream>
#include <iomanip>

#include "PacketIP.hh"

PacketIP::PacketIP(uint8_t *data, std::size_t len): PacketEthernet(data, len)
{
    std::copy(_payload.begin(),
        _payload.begin() + 1,
        _version.begin());
    *_version.data() = *_version.data() >> 4;

    std::copy(_payload.begin() + offsetof(struct iphdr, tos),
        _payload.begin() + offsetof(struct iphdr, tos) + 1,
        _protocol.begin());

    std::copy(_payload.begin() + offsetof(struct iphdr, id),
        _payload.begin() + offsetof(struct iphdr, id) + 2,
        _protocol.begin());

    std::copy(_payload.begin() + offsetof(struct iphdr, protocol),
        _payload.begin() + offsetof(struct iphdr, protocol) + 1,
        _protocol.begin());

    _payload.assign(_payload.begin() + sizeof(struct ether_header),
        _payload.end());
}

PacketIP::~PacketIP()
{
}

std::array<uint8_t, 1>              PacketIP::get_version(void)
{
    return _version;
}

std::array<uint8_t, 1>              PacketIP::get_tos(void)
{
    return _tos;
}

std::array<uint8_t, 2>              PacketIP::get_tot_len(void)
{
    return _tot_len;
}

std::array<uint8_t, 2>              PacketIP::get_id(void)
{
    return _id;
}

std::array<uint8_t, 1>              PacketIP::get_protocol(void)
{
    return _protocol;
}

std::string                         PacketIP::to_string(void) {

    std::stringstream   ss;

    ss << PacketEthernet::to_string();
    ss << "[IP]";
    // Version
    ss << "Version=" << std::hex;
    for (auto &byte : _version)
    {
        ss << std::setfill('0') << std::setw(2) << (unsigned int)byte;
    }
    ss << std::dec << ",";

    // TOS
    ss << "TOS=" << std::hex;
    for (auto &byte : _tos)
    {
        ss << std::setfill('0') << std::setw(2) << (unsigned int)byte;
    }
    ss << std::dec << ",";

    // TOT LEN
    ss << "TOT_len=" << std::hex;
    for (auto &byte : _tot_len)
    {
        ss << std::setfill('0') << std::setw(2) << (unsigned int)byte;
    }
    ss << std::dec << ",";

    // ID
    ss << "ID=" << std::hex;
    for (auto &byte : _id)
    {
        ss << std::setfill('0') << std::setw(2) << (unsigned int)byte;
    }
    ss << std::dec << ",";

    // Protocol
    ss << "Protocol=" << std::hex;
    for (auto &byte : _protocol)
    {
        ss << std::setfill('0') << std::setw(2) << (unsigned int)byte;
    }
    ss << std::dec;

    return ss.str();
}

void                                PacketIP::print(void) const {
    
    this->PacketEthernet::print();

    // IP Version
    std::cout << "IP Version: [" << std::hex;
    for (auto &byte : _version)
    {
        std::cout << std::setfill('0') << std::setw(2) << (unsigned int)byte;
    }
    std::cout << std::dec << "]" << std::endl;

    // IP Protocol
    std::cout << "IP Protocol: [" << std::hex;
    for (auto &byte : _protocol)
    {
        std::cout << std::setfill('0') << std::setw(2) << (unsigned int)byte;
    }
    std::cout << std::dec << "]" << std::endl;
}

std::ostream& operator<<(std::ostream &out, PacketIP packet)
{
    (void)packet;
    return out;
}
