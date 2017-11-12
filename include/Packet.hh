#ifndef PACKET_HH_
# define PACKET_HH_

# include <cstddef>
# include <cstdint>
# include <string>
# include <vector>

class Packet
{
protected:
    std::vector<uint8_t>        _data;
    std::vector<uint8_t>        _payload;

public:
    Packet(uint8_t* data, std::size_t len);
    Packet();
    virtual ~Packet();

    std::size_t                     get_size(void) const;
    std::vector<uint8_t>            get_data(void) const;

    std::size_t                     get_payload_size(void) const;
    std::vector<uint8_t>            get_payload(void) const;

    virtual void                    print(void) const;
};

std::ostream& operator<<(std::ostream &out, Packet packet);

#endif /* !PACKET_HH_ */
