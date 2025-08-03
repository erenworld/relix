/* ------------------------------------------------------------------------------------ *
 *                                                                                      *
 * EREN TURKOGLU   - Wed, Jul, 2025                                                     *
 * Title           - relix                                                              *
 * Description     - client                                                             *
 *                                                                                      *
 * ------------------------------------------------------------------------------------ */

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <string>
#include <vector>

const size_t MAX_MSG = 32 << 20; // 32 * 2^20

static void msg(const char *msg)
{
    fprintf(stderr, "%s\n", msg);
}

static void die(const char *msg)
{
    int err = errno;
    fprintf(stderr, "[%d] %s\n", err, msg);
    abort();
}

static int32_t read_all_bytes(int fd, uint8_t *buffer, size_t total_bytes)
{
    while (total_bytes > 0) {
        ssize_t byte = read(fd, buffer, total_bytes);
        if (byte <= 0) {
            return -1; // error or unexpected EOF
        }
        assert((size_t)byte <= total_bytes);
        total_bytes -= (size_t)byte;
        buffer += byte;
    }
    return 0;
}

static int32_t write_all_bytes(int fd, const uint8_t *buffer, size_t total_bytes)
{
    while (total_bytes > 0) {
        ssize_t byte = write(fd, buffer, total_bytes);
        if (byte <= 0) {
            return -1; // error or unexpected EOF
        }
        assert((size_t)byte <= total_bytes);
        total_bytes -= (size_t)byte;
        buffer += byte;
    }
    return 0;
}

// append to the back
static void buffer_append(std::vector<uint8_t> &buf, const uint8_t *data, size_t len)
{
    buf.insert(buf.end(), data, data + len);
}

