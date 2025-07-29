# Server

## socket()
The **socket()** syscall returns an fd. Here is a rough explanation of “fd” if you are unfamiliar
with Unix systems: An fd is an integer that refers to something in the Linux kernel, like a
TCP connection, a disk file, a listening port, or some other resources, etc.

## bind() and listen()
The bind() and listen() syscall: the bind() associates an address to a socket fd, and the
listen() enables us to accept connections to that address.

## accept()
The accept() takes a listening fd, when a client makes a connection to the listening address,
the accept() returns an fd that represents the connection socket.

```cpp
fd = socket()
bind(fd, address)
listen(fd)

while True:
    conn_fd = accept(fd)
    do_something_with(conn_fd)
    close(conn_fd)
```

## read, write, close
The read() syscall receives data from a TCP connection. The write() syscall sends data.
The close() syscall destroys the resource referred by the fd and recycles the fd number.

# Client
```cpp
fd = socket()
connect(fd, address)
do_something(fd)
close(fd)
```


