SOURCE = ./
BINARY = ../bin/
OBJECT = ../obj/

TARGET = $(BINARY)proofOfConcept.exe
OBJ = $(OBJECT)proofOfConcept.o $(OBJECT)classOpenAi.o $(OBJECT)classTranslator.o



COMPILER = g++
CFLAGS = -w -g
LIBS = -lcurl -ljsoncpp



$(TARGET): $(OBJ) $(HEADER)
	$(COMPILER) $(CFLAGS) -o $(TARGET) $(LFLAGS) $(OBJ) $(LIBS)


$(OBJECT)proofOfConcept.o: $(SOURCE)proofOfConcept.cpp \
$(SOURCE)classOpenAi.h \
$(SOURCE)classTranslator.h
	$(COMPILER) $(CFLAGS) -c $(SOURCE)proofOfConcept.cpp
	mv -f $(@F) $@ 

$(OBJECT)classOpenAi.o: $(SOURCE)classOpenAi.cpp \
$(SOURCE)classOpenAi.h
	$(COMPILER) $(CFLAGS) -c $(SOURCE)classOpenAi.cpp
	mv -f $(@F) $@ 

$(OBJECT)classTranslator.o: $(SOURCE)classTranslator.cpp \
$(SOURCE)classTranslator.h
	$(COMPILER) $(CFLAGS) -c $(SOURCE)classTranslator.cpp
	mv -f $(@F) $@ 

