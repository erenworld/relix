# Relix

Relix is an example of the server/client system. Multiple clients connect to a single server,
and the server receives requests from TCP connections and sends responses back.

The nstr is the number of strings and the len is the length of the following string. Both
are 32-bit integers.

The “command” in our design is a list of strings, like set key val. We’ll encode the
“command” with the following scheme.
+------+-----+------+-----+------+-----+-----+------+
| nstr | len | str1 | len | str2 | ... | len | strn |
+------+-----+------+-----+------+-----+-----+------+

The response is a 32-bit status code followed by the response string.

+-----+---------+
| res | data... |
+-----+---------+

# Resources
- https://github.com/dragonflydb/dragonfly
- https://github.com/valkey-io/valkey
- https://docs.keydb.dev/

