# AF_INET 
The AF_INET is for IPv4, use AF_INET6 for IPv6 or dual-stack socket.

# SOCK_STREAM 
The SOCK_STREAM is for TCP.

# file descriptor

# socket()

# setsockopt()
The setsockopt() call is used to configure various aspects of a socket. This particular call
enables the SO_REUSEADDR option. Without this option, the server won’t able to bind to the
same address if restarted.
It tells the operating system that you want to allow your program to bind a socket to an address (IP + port) that is in a certain state where it normally wouldn’t be allowed. Avoid "Address already in use" errors after restart. When you close a TCP server socket, the port you were using can remain "occupied" for a short period in a state called TIME_WAIT (to ensure all packets are handled correctly).
Allow multiple sockets to bind to the same port.

# 3 ways to deal with concurrent connections in server-side network programming
- forking (Forking creates new processes for each client connection to achieve concurrency.)
- multi-threading (Multi-threading uses threads instead of processes.)
- event loops (uses polling and nonblocking IO and usually runs on a single thread.)
