server: gameloop.o sockets.o grid.o dungeongen.o enemy.o itemgen.o input.o pkp.o player.o recieve.o shmutils.o cell_auto_mapgen.o
	gcc gameloop.o sockets.o grid.o dungeongen.o enemy.o itemgen.o input.o pkp.o player.o recieve.o shmutils.o  cell_auto_mapgen.o -o server
client: client.o sockets.o render.o grid.o clikey.o player.o enemy.o itemgen.o
	gcc client.o sockets.o render.o grid.o clikey.o player.o enemy.o itemgen.o -lSDL2 -lSDL2_ttf -o client
updategamestate.o: updategamestate.c
	gcc -c updategamestate.c
render.o: render.c
	gcc -c render.c
gameloop.o: gameloop.c
	gcc -c gameloop.c
sockets.o: fs/sockets.c
	gcc -c fs/sockets.c
grid.o: grid.c
	gcc -c grid.c
clikey.o: clikey.c
	gcc -c clikey.c
client.o: client.c
	gcc -c client.c
dungeongen.o: dungeongen.c
	gcc -c dungeongen.c
enemy.o: enemy.c
	gcc -c enemy.c
itemgen.o: itemgen.c
	gcc -c itemgen.c
input.o: input.c
	gcc -c input.c
pkp.o: pkp.c
	gcc -c pkp.c
player.o: player.c
	gcc -c player.c
recieve.o: recieve.c
	gcc -c recieve.c
shmutils.o: shmutils.c
	gcc -c shmutils.c
cell_auto_mapgen.o: cell_auto_mapgen.c
	gcc -c cell_auto_mapgen.c
run_server: server
	./server
run_client: client
	./client
clean:
	rm *~* \#*\# *.o *.out *.exe client server playarray wait enemyarray equarray
