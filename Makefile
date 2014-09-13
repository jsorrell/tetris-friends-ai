CC=g++-4.9
EXT=.cxx
CFLAGS=-Wl,--no-as-needed -Wall -Werror -std=c++11 -g -pthread
LDFLAGS=-lxdo -ltins
INC=-iquotesrc/include
DIRS=bin/ obj/
EXECDIR=bin
DIRSTAMPS := $(addsuffix .dirstamp,$(DIRS))
###MAIN EXEC####
SOURCES := $(wildcard src/*$(EXT))
OBJECTS := $(addprefix obj/,$(notdir $(SOURCES:$(EXT)=.o)))
###coretest###
CTSOURCES := tetCore.cxx tetCore.test.cxx
CTOBJECTS := $(addprefix obj/,$(notdir $(CTSOURCES:$(EXT)=.o)))
###aitest###
AITSOURCES := tetCore.cxx tetAi.cxx tetAi.test.cxx
AITOBJECTS := $(addprefix obj/,$(notdir $(AITSOURCES:$(EXT)=.o)))
###infotest###
INFTSOURCES := tetCore.cxx tetGameInfo.cxx tetCore.test.cxx
INFTOBJECTS := $(addprefix obj/,$(notdir $(INFTSOURCES:$(EXT)=.o)))
###keysendertest###
KSTSOURCES := tetKeySender.cxx tetKeySender.test.cxx
KSTOBJECTS := $(addprefix obj/,$(notdir $(KSTSOURCES:$(EXT)=.o)))

tetrisFriendsAi: $(OBJECTS)
	$(CC) $(CFLAGS) $(INC) -o $(EXECDIR)/$@ $^ $(LDFLAGS)

coretest: $(CTOBJECTS)
	$(CC) $(CFLAGS) $(INC) -o $(EXECDIR)/$@ $^ $(LDFLAGS)

aitest: $(AITOBJECTS)
	$(CC) $(CFLAGS) $(INC) -o $(EXECDIR)/$@ $^ $(LDFLAGS)

infotest: $(INFTOBJECTS)
	$(CC) $(CFLAGS) $(INC) -o $(EXECDIR)/$@ $^ $(LDFLAGS)

keysendertest: $(KSTOBJECTS)
	$(CC) $(CFLAGS) $(INC) -o $(EXECDIR)/$@ $^ $(LDFLAGS)

obj/%.o: src/%.cxx $(DIRSTAMPS)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<
obj/%.test.o: src/test/%.test.cxx $(DIRSTAMPS)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(DIRSTAMPS):
	mkdir -p $(@D)
	touch $@

clean:
	rm -rf $(DIRS)