#ifndef PACKETFACTORY_HH_
# define PACKETFACTORY_HH_

# include "Packet.hh"
# include "PacketEthernet.hh"
# include "PacketIP.hh"
# include "PacketARP.hh"

class PacketFactory {

public:
    static Packet          *create(uint8_t *data, std::size_t len);
};

#endif /* !PACKETFACTORY_HH_ */