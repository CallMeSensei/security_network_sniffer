#ifndef FILE_CAPTURE_H_
# define FILE_CAPTURE_H_

# include <stdint.h>

typedef struct	file_cap_global_hdr_s {
  uint32_t	magic_number;	/* magic number */
  uint16_t	version_major;  /* major version number */
  uint16_t	version_minor;  /* minor version number */
  int32_t	thiszone;       /* GMT to local correction */
  uint32_t	sigfigs;        /* accuracy of timestamps */
  uint32_t	snaplen;        /* max length of captured packets, in octets */
  uint32_t	network;        /* data link type */
}		file_cap_hdr_t;

typedef struct	file_cap_packet_hdr_s {
  uint32_t	ts_sec;         /* timestamp seconds */
  uint32_t	ts_usec;        /* timestamp microseconds */
  uint32_t	incl_len;       /* number of octets of packet saved in file */
  uint32_t	orig_len;       /* actual length of packet */
}		file_cap_packet_hdr_t;

#endif /* !FILE_CAPTURE_H_ */
