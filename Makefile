CC=g++
EXT=.cxx
CFLAGS=-Wall -Werror
LDFLAGS=-lcrafter -lboost_regex
INC=
DIRS=bin/ obj/
DIRSTAMPS := $(addsuffix .dirstamp,$(DIRS))
SOURCES := $(wildcard src/*$(EXT))
OBJECTS := $(addprefix obj/,$(notdir $(SOURCES:$(EXT)=.o)))
EXECUTABLE=bin/tcp

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

obj/%.o: src/%.cxx $(DIRSTAMPS)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(DIRSTAMPS):
	mkdir -p $(@D)
	touch $@

clean:
	rm -rf obj bin