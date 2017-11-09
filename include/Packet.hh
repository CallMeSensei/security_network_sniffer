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

public:
    Packet(uint8_t* data, std::size_t len);
    Packet();
    ~Packet();

    std::size_t           get_size(void) const;
    std::vector<uint8_t>  get_data(void) const;
};

std::ostream& operator<<(std::ostream &out, Packet packet);

#endif /* !PACKET_HH_ */
