#ifndef PACKET_ARP_HH_
# define PACKET_ARP_HH_

# include <array>

# include "PacketEthernet.hh"

class PacketARP: public PacketEthernet
{
private:
    std::array<uint8_t, 2>          _htype;
    std::array<uint8_t, 2>          _ptype;
    std::array<uint8_t, 1>          _hlen;
    std::array<uint8_t, 1>          _plen;
    std::array<uint8_t, 2>          _op;

public:
    PacketARP(uint8_t *data, std::size_t len);
    ~PacketARP();

    std::array<uint8_t, 2>          get_htype(void);
    std::array<uint8_t, 2>          get_ptype(void);
    std::array<uint8_t, 1>          get_hlen(void);
    std::array<uint8_t, 1>          get_plen(void);
    std::array<uint8_t, 2>          get_op(void);
};

std::ostream& operator<<(std::ostream &out, PacketARP packet);

#endif /* !PACKET_ARP_HH_ */
