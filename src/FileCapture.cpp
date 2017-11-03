#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

#include "file_capture.h"

int			file_capture_create(int fd, int dlt) {

  fcap_global_hdr_t	hdr;

  hdr.magic_number = 0xa1b2c3d4;
  hdr.version_major = 2;
  hdr.version_minor = 4;
  hdr.thiszone = 0;
  hdr.sigfigs = 0;
  hdr.snaplen = 65535;
  hdr.network = dlt;
  if (write(fd, &hdr, sizeof(fcap_global_hdr_t)) !=
      sizeof(fcap_global_hdr_t)) {
    close(fd);
    return -1;
  }
  return fd;
}

int                 file_capture_read_packet(int fd, void *data) {

  fcap_packet_hdr_t hdr;
  int               rb;

  if (read(fd, &hdr, sizeof(fcap_packet_hdr_t)) < 0 ||
      (rb = read(fd, data, hdr.incl_len)) < 0) {
    return rb;
  }
  return rb;
}

int                 file_capture_write_packet(int fd, void *data, size_t len) {

  fcap_packet_hdr_t	hdr;

  hdr.ts_sec = time(NULL);
  hdr.ts_usec = 0;
  hdr.incl_len = len;
  hdr.orig_len = len;
  if (write(fd, &hdr, sizeof(fcap_packet_hdr_t)) !=
      sizeof(fcap_packet_hdr_t) ||
      (size_t)write(fd, data, len) != len) {
    close(fd);
    return -1;
  }
  return fd;
}

