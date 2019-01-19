server: gameloop.o sockets.o grid.o dungeongen.o enemy.o itemgen.o  pkp.o player.o shmutils.o cell_auto_mapgen.o clikey.o
	gcc gameloop.o sockets.o grid.o dungeongen.o enemy.o itemgen.o  pkp.o player.o shmutils.o  cell_auto_mapgen.o clikey.o -o server -g
client: client.o sockets.o render.o grid.o clikey.o player.o enemy.o itemgen.o
	gcc client.o sockets.o render.o grid.o clikey.o player.o enemy.o itemgen.o -lSDL2 -lSDL2_ttf -o client -g
render.o: render.c
	gcc -c render.c -g
gameloop.o: gameloop.c
	gcc -c gameloop.c -g
sockets.o: fs/sockets.c
	gcc -c fs/sockets.c -g
grid.o: grid.c
	gcc -c grid.c -g
clikey.o: clikey.c
	gcc -c clikey.c -g
client.o: client.c
	gcc -c client.c -g
dungeongen.o: dungeongen.c
	gcc -c dungeongen.c -g
enemy.o: enemy.c
	gcc -c enemy.c -g
itemgen.o: itemgen.c
	gcc -c itemgen.c -g
pkp.o: pkp.c
	gcc -c pkp.c -g
player.o: player.c
	gcc -c player.c -g
shmutils.o: shmutils.c
	gcc -c shmutils.c -g
cell_auto_mapgen.o: cell_auto_mapgen.c
	gcc -c cell_auto_mapgen.c -g
run_server: server
	./server
run_client: client
	./client
clean:
	rm *~* \#*\# *.o *.out *.exe client server playarray wait enemyarray equarray
