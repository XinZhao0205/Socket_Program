

all:client_zx edge_zx server_and_zx server_or_zx

client_zx: client.c
	gcc -o client client.c

edge_zx: edge.c
	gcc -o edge edge.c

server_and_zx:server_and.c
	gcc -o server_and server_and.c

server_or_zx: server_or.c
	gcc -o server_or server_or.c

.PHONY:clean edge server_and server_or

clean:
	rm -f client edge server_and sever_or

edge:
	./edge

server_and:
	./server_and

server_or:
	./server_or
