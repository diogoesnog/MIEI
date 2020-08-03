CFLAGS=-Wall -Wextra -pedantic -O2
FICHEIROS=cgi.h estado.c estado.h bestscores.h ficheiro.h jogo.c Makefile images

install: jogo
	sudo cp jogo /usr/lib/cgi-bin
	
	sudo mkdir -p /var/www/html/images
	sudo cp -r images /var/www/html
	
	sudo mkdir -p /var/www/html/files
	sudo chmod a+rw /var/www/html/files
	
	touch install

jogo: jogo.o estado.o 
	cc -o jogo jogo.o estado.o

zip: $(FICHEIROS)
	zip -9r projeto.zip $(FICHEIROS)

doc:
	doxygen -g
	doxygen

clean:
	rm -rf *.o jogo Doxyfile latex html install
	
	sudo rm -rf /var/www/html
	
	sudo rm -f /usr/lib/cgi-bin/jogo

estado.o: estado.c estado.h
jogo.o: jogo.c cgi.h estado.h
