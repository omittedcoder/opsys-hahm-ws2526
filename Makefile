all: listdir helloworld

listdir: listdir.c
	cc listdir.c -o listdir

helloworld: helloworld.c
	cc helloworld.c -o helloworld

clean:
	rm listdir helloworld
