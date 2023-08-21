all : bin/mainTexte bin/mainTest bin/mainSdl

qwixx_debug : bin/mainTest

qwixx_txt : bin/mainTexte

qwixx_sdl : bin/mainSdl

bin/mainTest : obj/mainTest.o obj/fiche.o obj/ligne.o obj/des.o obj/jeu.o 
				g++ -g -Wall obj/mainTest.o obj/fiche.o obj/ligne.o obj/des.o obj/jeu.o -o bin/mainTest

bin/mainTexte : obj/mainTexte.o obj/jeu.o obj/fiche.o obj/ligne.o obj/des.o obj/txtJeu.o obj/winTxt.o
				g++ -g -Wall obj/mainTexte.o obj/jeu.o obj/fiche.o obj/ligne.o obj/des.o obj/txtJeu.o obj/winTxt.o -o bin/mainTexte

bin/mainSdl : obj/mainSdl.o obj/jeu.o obj/fiche.o obj/ligne.o obj/des.o obj/sdlJeu.o obj/image.o
				g++ -g -Wall obj/mainSdl.o obj/jeu.o obj/fiche.o obj/ligne.o obj/des.o obj/sdlJeu.o obj/image.o -o bin/mainSdl -lSDL2 -lSDL2_image -lSDL2_ttf

obj/mainTest.o : src/mainTest.cpp src/jeu.h
			g++ -g -Wall -c src/mainTest.cpp -o obj/mainTest.o

obj/mainTexte.o : src/txt/mainTexte.cpp src/jeu.h
				g++ -g -Wall -c src/txt/mainTexte.cpp -o obj/mainTexte.o

obj/mainSdl.o : src/sdl2/mainSdl.cpp src/sdl2/sdlJeu.h
				g++ -g -Wall -c src/sdl2/mainSdl.cpp -o obj/mainSdl.o

obj/jeu.o : src/jeu.cpp src/jeu.h src/fiche.h src/ligne.h src/des.h
			g++ -g -Wall -c src/jeu.cpp -o obj/jeu.o

obj/fiche.o: src/fiche.cpp src/fiche.h src/ligne.h
			g++ -g -Wall -c src/fiche.cpp -o obj/fiche.o

obj/ligne.o : src/ligne.cpp src/ligne.h
			g++ -g -Wall -c src/ligne.cpp -o obj/ligne.o

obj/des.o : src/des.cpp src/des.h
			g++ -g -Wall -c src/des.cpp -o obj/des.o

obj/txtJeu.o: src/txt/txtJeu.cpp src/txt/txtJeu.h src/txt/winTxt.h
			g++ -g -Wall -c src/txt/txtJeu.cpp -o obj/txtJeu.o

obj/winTxt.o: src/txt/winTxt.cpp src/txt/winTxt.h
			g++ -g -Wall -c src/txt/winTxt.cpp -o obj/winTxt.o

obj/sdlJeu.o: src/sdl2/sdlJeu.cpp src/sdl2/sdlJeu.h src/jeu.h src/sdl2/image.h
			g++ -g -Wall -c src/sdl2/sdlJeu.cpp -o obj/sdlJeu.o

obj/image.o: src/sdl2/image.cpp src/sdl2/image.h
			g++ -g -Wall -c src/sdl2/image.cpp -o obj/image.o

clean:
	rm obj/*

veryclean: clean
	rm bin/*
