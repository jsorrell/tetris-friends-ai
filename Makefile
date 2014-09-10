CC=g++
EXT=.cxx
CFLAGS=-Wall -Werror -std=c++11 -g
LDFLAGS=-lcrafter -lboost_regex
INC=
DIRS=bin/ obj/
DIRSTAMPS := $(addsuffix .dirstamp,$(DIRS))
SOURCES := $(wildcard src/*$(EXT))
OBJECTS := $(addprefix obj/,$(notdir $(SOURCES:$(EXT)=.o)))
EXECDIR=bin
EXECUTABLE=tcp

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(EXECDIR)/$@ $^ $(LDFLAGS)

obj/%.o: src/%.cxx $(DIRSTAMPS)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

coretest: src/tetCore.cxx src/tetCore.test.cxx
	$(CC) $(CFLAGS) -o $(EXECDIR)/$@ $^ $(LDFLAGS)

aitest: src/tetCore.cxx src/tetAi.cxx src/tetAi.test.cxx
	$(CC) $(CFLAGS) -o $(EXECDIR)/$@ $^ $(LDFLAGS)

$(DIRSTAMPS):
	mkdir -p $(@D)
	touch $@

clean:
	rm -rf obj bin
