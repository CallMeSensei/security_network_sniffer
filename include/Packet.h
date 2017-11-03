#ifndef PACKET_H_
# define PACKET_H_

# include <cstddef>

class Packet
{
protected:
    std::size_t     _size;
    void*           _raw_data;

public:
    Packet(void*, std::size_t);
    ~Packet();
};

#endif /* !PACKET_H_ */