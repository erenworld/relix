/* ------------------------------------------------------------------------------------ *
 *                                                                                      *
 * EREN TURKOGLU   - Wed, Jul, 2025                                                     *
 * Title           - relix                                                              *
 * Description     - server                                                             *
 *                                                                                      *
 * ------------------------------------------------------------------------------------ */

// stdlib
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
// system
#include <fcntl.h>
#include <poll.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/ip.h>
// C++
#include <vector>

static void msg(const char *msg)
{
    fprintf(stderr, "%s\n", errno, msg);
}

static void errno_msg(const char *msg)
{
    fprintf(stderr, "[errno:%d] %s\n", errno, msg);
}

static void die(const char *msg)
{
    fprintf(stderr, "[%d] %s\n", errno, msg);
    abort();
}

static void set_fd_nonblocking(int fd)
{
    errno = 0;
    int flags = fcntl(fd, F_GETFL, 0);
    
    if (errno) {
        die("fcntl error");
        return;
    }
    flags |= O_NONBLOCK;

    errno = 0;
    (void)fcntl(fd, F_SETFL, flags);
    if (errno) {
        die("fcntl error");
    }
}

