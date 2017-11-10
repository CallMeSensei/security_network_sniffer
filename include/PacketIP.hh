#ifndef PACKET_IP_HH_
# define PACKET_IP_HH_

# include <array>

# include <linux/ip.h>

# include "PacketEthernet.hh"

class PacketIP: public PacketEthernet
{
private:
    std::array<uint8_t, 1>          _version;

public:
    PacketIP(uint8_t *data, std::size_t len);
    virtual ~PacketIP();

    std::array<uint8_t, 1>          get_version(void);

    virtual void                    print(void) const;
};

std::ostream& operator<<(std::ostream &out, PacketIP packet);

#endif /* !PACKET_IP_HH_ */
