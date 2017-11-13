
#include <ctime>
#include <sstream>

#include "FileCapture.hh"

FileCapture::FileCapture(std::string name, int dlt) {

    _ghdr.magic_number = 0xa1b2c3d4;
    _ghdr.version_major = 2;
    _ghdr.version_minor = 4;
    _ghdr.thiszone = 0;
    _ghdr.snaplen = 65535;
    _ghdr.sigfigs = 0;
    _ghdr.network = dlt;

    _file.open(name.c_str(), std::ios::binary);
    _file.write((const char*)&_ghdr, sizeof(_ghdr));
}

FileCapture::~FileCapture() {
    _file.close();
};

FileCapture             &FileCapture::operator<<(Packet& p) {

    struct timeval tv;
 
    localtime(&tv.tv_sec);

    _phdr.ts_sec = tv.tv_sec;
    _phdr.ts_usec = tv.tv_usec;
    _phdr.incl_len = p.get_size();
    _phdr.orig_len = p.get_size();
    _file.write((const char*)&_phdr, sizeof(_phdr));
    _file.write((char*)&(p.get_data()[0]), p.get_size());
    return *this;
}