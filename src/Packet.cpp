#include <cstdlib>
#include <cstring>

#include "Packet.h"

Packet::Packet(void *raw_data, std::size_t size)
{
    _size = size;
    _raw_data = std::malloc(_size);
    std::memcpy(_raw_data, raw_data, _size);
}

Packet::~Packet()
{
    std::free(_raw_data);
}