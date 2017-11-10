#include <cstring>
#include <iostream>
#include <iomanip>

#include "PacketIP.hh"

PacketIP::PacketIP(uint8_t *data, std::size_t len): PacketEthernet(data, len)
{
    std::copy(_payload.begin(),
        _payload.begin() + 1,
        _version.begin());
    *_version.data() = *_version.data() >> 4;

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

std::array<uint8_t, 1>              PacketIP::get_protocol(void)
{
    return _protocol;
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
