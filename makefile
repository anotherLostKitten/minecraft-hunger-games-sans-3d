all: input.o gameloop.o updategamestate.o render.o
	gcc -o ./game gameloop.o input.o updategamestate.o render.o
input.o: input.c
	gcc -c input.c
updategamestate.o: updategamestate.c
	gcc -c updategamestate.c
render.o: render.c
	gcc -c render.c
gameloop.o: gameloop.c
	gcc -c gameloop.c
bazinga:
	ls -cflLACFQRUIOPLKJHGFDSAZXCVBNMqwertyuiopasdfghjklzxcvbnm --color=auto
