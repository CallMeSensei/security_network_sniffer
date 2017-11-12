
#include "FileCapture.hh"

FileCapture::FileCapture(std::string name, int dlt) {

    (void)dlt;
    _file.open(name.c_str(), std::ios::binary);
    //_file.write
}

FileCapture::~FileCapture() {
    _file.close();
};

FileCapture             &FileCapture::operator<<(Packet& p) {

    (void)p;
    return *this;
}