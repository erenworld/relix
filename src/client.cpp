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

int main(void)
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);

    if (fd < 0) {
        die("socket()");
    }
    // initialize IPv4 address 0
    struct sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_port = ntohs(1234);
    addr.sin_addr.s_addr = ntohl(INADDR_LOOPBACK); // 127.0.0.1
    int rv = connect(fd, (const struct sockaddr *)&addr, sizeof(addr));
    
    if (rv) {
        die("connect()");
    }
    // multiple pipeline req
    std::vector<std::string> query_list = {
        "hello1", "hello2", "hello3",
        // a large message requires multiple event loop iterations
        std::string(MAX_MSG, 'z'),
        "hello5",
    };
    for (const std::string &s : query_list) {
        int32_t err = send_req(fd, (uint8_t)s.data(), s.size());

        if (err) {
            goto L_DONE;
        }
    }
    for (size_t i = 0; i < query_list.size(); ++i) {
        int32_t err = read_res(fd);

        if (err) {
            goto L_DONE;
        }
    }

    L_DONE:
        close(fd);
        return 0;
}
