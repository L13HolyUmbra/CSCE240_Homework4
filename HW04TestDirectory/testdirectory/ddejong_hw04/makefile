GPP = g++ -O3 -Wall

UTILS = ../../Utilities

A = Main.o
G = GamePlay.o
D = Domino.o
S = Scanner.o
SL = ScanLine.o
U = Utils.o

Aprog: $A $G $D $S $(SL) $U
	$(GPP) -o Aprog $A $G $D $S $(SL) $U

Main.o: Main.h Main.cpp
	$(GPP) -c Main.cpp

GamePlay.o: GamePlay.h GamePlay.cpp
	$(GPP) -c GamePlay.cpp

Domino.o: Domino.h Domino.cpp
	$(GPP) -c Domino.cpp

Scanner.o: $(UTILS)/Scanner.h $(UTILS)/Scanner.cpp
	$(GPP) -c $(UTILS)/Scanner.cpp

ScanLine.o: $(UTILS)/ScanLine.h $(UTILS)/ScanLine.cpp
	$(GPP) -c $(UTILS)/ScanLine.cpp

Utils.o: $(UTILS)/Utils.h $(UTILS)/Utils.cpp
	$(GPP) -c $(UTILS)/Utils.cpp
