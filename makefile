OBJECTS= KLalgorithm.o 
	CC = g++ 
	CCFLAGS = -g 
	LDFLAGS = -lm 
	EXE = KLalgorithm 
$(EXE): $(OBJECTS)
		$(CC) $(OBJECTS) -o $(EXE) $(LDFLAGS) 
KLalgorithm.o: KLalgorithm.cpp
		$(CC) -c $(CCFLAGS) $*.cpp 
 
