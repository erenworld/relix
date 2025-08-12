```python
    all_fds = [...]
    while True:
        active_fds = poll(all_fds)  # système d’attente qui retourne la liste des sockets prêtes
        for each fd in active_fds:
            do_something_with(fd)
    
    def do_something_with(fd):
        if fd is a listening socket: # server
            add_new_client(fd)
        elif fd is a client connection:
            while work_not_done(fd):
                do_something_to_client(fd)
    
    def do_something_to_client(fd):
        if should_read_from(fd):
            data = read_until_EAGAIN(fd)
            process_incoming_data(data)
    while should_write_to(fd):
        write_until_EAGAIN(fd)
    if should_close(fd):
        destroy_client(fd)
```


In blocking mode, read blocks the caller when there are no data in the kernel, write blocks when the write buffer is full, and accept blocks when there are no new connections in the kernel queue.

# Mode bloquant vs mode non bloquant
Mode bloquant (blocking) :
- Quand tu appelles read(), si il n'y a pas de données disponibles, la fonction bloque (attend) jusqu'à ce que des données arrivent.
- Quand tu appelles write(), si le buffer d'écriture est plein, write() bloque (attend que ça se vide).
- Quand tu appelles accept(), si aucune nouvelle connexion n'est prête, accept() bloque (attend qu'une connexion arrive).

Mode non bloquant (nonblocking) :
- Les appels read(), write(), accept() ne bloquent jamais.
- S'ils ne peuvent pas faire leur travail immédiatement (pas de données à lire, buffer plein, pas de connexion prête), ils renvoient une erreur spéciale EAGAIN, qui signifie "pas prêt, réessaye plus tard".


### Mais comment savoir quand “plus tard” ?
Grâce à poll() (ou select(), epoll()), qui va attendre (bloquer) que le fichier (socket) soit prêt à être lu ou écrit.

Dans un serveur événementiel (event loop), le seul appel bloquant autorisé est poll().

poll() attend que quelque chose soit prêt (données à lire, place à écrire, nouvelle connexion).

Tout le reste (lecture, écriture, accept) est en mode non bloquant et doit toujours être retravaillé jusqu’à ce que EAGAIN apparaisse.

- Les timers doivent être gérés dans la boucle d’événements
- Les opérations non non-blocking (DNS, disque) doivent être faites dans des threads séparés.


# Story of poll
On Linux, besides the poll syscall, there are also **select** and **epoll**. The ancient select syscall is basically the same as the poll, except that the maximum fd number is limited to a small number, which makes it obsolete in modern applications. The epoll API consists
of 3 syscalls: epoll_create, epoll_wait, and epoll_ctl. The epoll API is stateful, instead
of supplying a set of fds as a syscall argument, epoll_ctl was used to manipulate an fd set created by epoll_create, which the epoll_wait is operating on.

> , the epoll API is preferable in real-world projects since the argument for the poll can become too large as the number of fds increases
