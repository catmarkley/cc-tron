
CMP = g++
MAIN = project
CLASS1 = board
CLASS2 = snake
CLASS3 = gfx
EXEC = playit

$(EXEC): $(MAIN).o $(CLASS1).o $(CLASS2).o $(CLASS3).o
	$(CMP) $(MAIN).o $(CLASS1).o $(CLASS2).o $(CLASS3).o -lX11 -o $(EXEC)

$(MAIN).o: $(CLASS3).h $(MAIN).cpp
	$(CMP) -c $(MAIN).cpp

$(CLASS1).o: $(CLASS1).h $(CLASS1).cpp
	$(CMP) -c $(CLASS1).cpp

$(CLASS2).o: $(CLASS1).h $(CLASS2).h $(CLASS2).cpp
	$(CMP) -c $(CLASS2).cpp

clean:
	rm $(CLASS1).o
	rm $(CLASS2).o
	rm $(MAIN).o
	rm $(EXEC)

