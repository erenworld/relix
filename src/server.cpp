/* ------------------------------------------------------------------------------------ *
 *                                                                                      *
 * EREN TURKOGLU   - Wed, Jul, 2025                                                     *
 * Title           - relix                                                              *
 * Description     - server                                                             *
 *                                                                                      *
 * ------------------------------------------------------------------------------------ */

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <poll.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <iostream>

const size_t k_max_msg = 4096;

enum {
    STATE_REQ = 0,
    STATE_RES = 1,
    STATE_END = 2, // Mark the connection for deletion.
};

struct Connection {
    int fd = -1;
    uint32_t state = 0; // either STATE_REQ or STATE_RES
    // buffer for reading
    size_t r_bufsize = 0;
    uint8_t r_buf[4 + k_max_msg];
    // buffer for writing
    size_t w_bufsize = 0;
    size_t w_bufsent = 0;
    uint8_t w_buf[4 + k_max_msg];
};

