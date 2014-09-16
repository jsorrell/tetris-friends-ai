#change to depend on inclded files
CXX=g++-4.9
HEXT=.hpp
EXT=.cxx
#compile flags
CXXFLAGS=-Wl,--no-as-needed -Wall -Werror -std=c++11 -g -pthread
#link flags
CXXLFLAGS=-Wall -Werror -std=c++11 -pthread
CXXFLAGS+=-MMD
LDFLAGS=-lX11 -ltins -lXtst
INC=-iquotesrc/include
DIRS=bin/ obj/
EXECDIR=bin
DIRSTAMPS := $(addsuffix .dirstamp,$(DIRS))
###MAIN EXEC####
SOURCES := $(wildcard src/*$(EXT))
OBJECTS := $(addprefix obj/,$(notdir $(SOURCES:$(EXT)=.o)))
###coretest###
CTSOURCES := tetConstants.cxx tetCore.cxx tetCore.test.cxx
###aitest###
AITSOURCES := tetConstants.cxx tetCore.cxx tetAi.cxx tetAi.test.cxx
###infotest###
INFTSOURCES := tetConstants.cxx tetCore.cxx tetGameInfo.cxx tetGameInfo.test.cxx
###keysendertest###
KSTSOURCES := tetConstants.cxx tetKeySender.cxx tetKeySender.test.cxx
###playertest###
PTSOURCES := tetConstants.cxx tetKeySender.cxx tetCore.cxx tetGameInfo.cxx tetAi.cxx tetPlayer.cxx tetPlayer.test.cxx

$(EXECDIR)/tetrisFriendsAi: $(OBJECTS)
	$(CXX) $(CXXLFLAGS) -o $@ $^ $(LDFLAGS)

$(EXECDIR)/coretest: $(addprefix obj/,$(notdir $(CTSOURCES:$(EXT)=.o)))
	$(CXX) $(CXXLFLAGS) -o $@ $^ $(LDFLAGS)

$(EXECDIR)/aitest: $(addprefix obj/,$(notdir $(AITSOURCES:$(EXT)=.o)))
	$(CXX) $(CXXLFLAGS) -o $@ $^ $(LDFLAGS)

$(EXECDIR)/infotest: $(addprefix obj/,$(notdir $(INFTSOURCES:$(EXT)=.o)))
	$(CXX) $(CXXLFLAGS) -o $@ $^ $(LDFLAGS)

$(EXECDIR)/keysendertest: $(addprefix obj/,$(notdir $(KSTSOURCES:$(EXT)=.o)))
	$(CXX) $(CXXLFLAGS) -o $@ $^ $(LDFLAGS)

$(EXECDIR)/playertest: $(addprefix obj/,$(notdir $(PTSOURCES:$(EXT)=.o)))
	$(CXX) $(CXXLFLAGS) -o $@ $^ $(LDFLAGS)

obj/%.o: src/%.cxx $(DIRSTAMPS)
	$(CXX) $(CXXFLAGS) $(INC) -c -o $@ $<
obj/%.test.o: src/test/%.test.cxx $(DIRSTAMPS)
	$(CXX) $(CXXFLAGS) $(INC) -c -o $@ $<

$(DIRSTAMPS):
	mkdir -p $(@D)
	touch $@

-include $(wildcard obj/*.d)

clean:
	rm -rf $(DIRS)