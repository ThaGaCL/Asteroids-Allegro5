PROGS = asteroids
CC = gcc
CFLAGS = -Wall -g
ALLEGRO = -lallegro -lallegro_primitives -lallegro_image -lallegro_font -lallegro_audio -lallegro_acodec
objects = main.o asteroidsLib.o allegroDisplay.o allegroUtil.o allegroKeyboard.o allegroSprites.o allegroFx.o allegroAudio.o

asteroids: $(objects)
	$(CC) $(CFLAGS) $(objects) $(ALLEGRO) -o $(PROGS)

main.o: main.c allegroUtil.h asteroidsLib.h allegroDisplay.h allegroKeyboard.h allegroSprites.h allegroFx.h allegroAudio.h
	$(CC) $(CFLAGS) -c main.c

allegroDisplay.o: allegroDisplay.c allegroDisplay.h
	$(CC) $(CFLAGS) -c allegroDisplay.c allegroDisplay.h

asteroidsLib.o: asteroidsLib.c asteroidsLib.h allegroUtil.h
	$(CC) $(CFLAGS) -c asteroidsLib.c

allegroKeyboard.o: allegroKeyboard.c allegroKeyboard.h
	$(CC) $(CFLAGS) -c allegroKeyboard.c

allegroSprites.o: allegroSprites.c allegroSprites.h
	$(CC) $(CFLAGS) -c allegroSprites.c
	
allegroAudio.o: allegroAudio.c allegroAudio.h
	$(CC) $(CFLAGS) -c allegroAudio.c
	
allegroFx.o: allegroFx.c allegroFx.h
	$(CC) $(CFLAGS) -c allegroFx.c
	
allegroUtil.o: allegroUtil.c allegroUtil.h
	$(CC) $(CFLAGS) -c allegroUtil.c

clean:
	-rm -f *~ *.o

purge: clean
	-rm -f $(PROGS)