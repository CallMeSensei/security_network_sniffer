#ifndef FILE_CAPTURE_HH_
# define FILE_CAPTURE_HH_

# include <fstream>
# include <string>
# include <stdint.h>

# include "DataLinkType.hh"
# include "Packet.hh"

typedef struct  fcap_global_hdr_s {
  uint32_t      magic_number;	/* magic number */
  uint16_t      version_major;  /* major version number */
  uint16_t      version_minor;  /* minor version number */
  int32_t       thiszone;       /* GMT to local correction */
  uint32_t      sigfigs;        /* accuracy of timestamps */
  uint32_t      snaplen;        /* max length of captured packets, in octets */
  uint32_t      network;        /* data link type */
}               fcap_global_hdr_t;


typedef struct  fcap_packet_hdr_s {
  uint32_t      ts_sec;         /* timestamp seconds */
  uint32_t      ts_usec;        /* timestamp microseconds */
  uint32_t      incl_len;       /* number of octets of packet saved in file */
  uint32_t      orig_len;       /* actual length of packet */
}               fcap_packet_hdr_t;

class FileCapture {

private:
  fcap_global_hdr_t   _ghdr;
  fcap_packet_hdr_t   _phdr;
  std::ofstream       _file;

public:
  FileCapture(std::string name, int dlt);
  ~FileCapture();

  FileCapture         &operator<<(Packet&);
};

#endif /* !FILE_CAPTURE_HH_ */
