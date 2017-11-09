#ifndef PACKET_ETHERNET_H_
# define PACKET_ETHERNET_H_

# include <array>

# include "Packet.h"

class PacketEthernet: public Packet
{
private:
    std::array<uint8_t, 6>          _mac_destination;
    std::array<uint8_t, 6>          _mac_source;
    std::array<uint8_t, 2>          _type;

public:
    PacketEthernet(uint8_t *data, std::size_t len);
    ~PacketEthernet();

    std::array<uint8_t, 6>          get_mac_destination(void);
    std::array<uint8_t, 6>          get_mac_source(void);
    std::array<uint8_t, 2>          get_type(void);
};

std::ostream& operator<<(std::ostream &out, PacketEthernet packet);

#endif /* !PACKET_ETHERNET_H_ */