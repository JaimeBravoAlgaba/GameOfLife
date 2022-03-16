gameOfLife.exe: obj/gameOfLife.o
	g++ -o gameOfLife obj/gameOfLife.o -lOpenGL32 -lglut32 -lglui32 -lGlAux -lGlU32 -lFreeImage

obj/gameOfLife.o: src/gameOfLife.cpp
	g++ -c src/gameOfLife.cpp -o obj/gameOfLife.o

clean:
	del bin/gameOfLife.exe obj/gameOfLife.o