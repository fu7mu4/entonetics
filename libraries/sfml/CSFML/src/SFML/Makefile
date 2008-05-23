export CC        = gcc
export CPP       = g++
export CFLAGS    = -W -Wall -pedantic -fPIC -Wno-unused -I../.. -I../../../include -DNDEBUG -DCSFML_EXPORTS -O2
export LDFLAGS   = -shared
export LIBPATH   = ../../../lib
export VERSION   = 1
export CP        = cp
export LN        = ln
export LNFLAGS   = -s -f

all: csfml-system csfml-window csfml-network csfml-graphics csfml-audio

csfml-system:
	@(cd ./System && $(MAKE))

csfml-window:
	@(cd ./Window && $(MAKE))

csfml-network:
	@(cd ./Network && $(MAKE))

csfml-graphics:
	@(cd ./Graphics && $(MAKE))

csfml-audio:
	@(cd ./Audio && $(MAKE))

.PHONY: clean mrproper

clean:
	@(cd ./System && $(MAKE) $@	&& cd ../Window && $(MAKE) $@ && cd ../Network && $(MAKE) $@ && cd ../Graphics && $(MAKE) $@ && cd ../Audio && $(MAKE) $@)

mrproper: clean
	@(cd ./System && $(MAKE) $@	&& cd ../Window && $(MAKE) $@ && cd ../Network && $(MAKE) $@ && cd ../Graphics && $(MAKE) $@ && cd ../Audio && $(MAKE) $@)

install:
	@(cd ./System && $(MAKE) $@	&& cd ../Window && $(MAKE) $@ && cd ../Network && $(MAKE) $@ && cd ../Graphics && $(MAKE) $@ && cd ../Audio && $(MAKE) $@ && $(CP) -r ../../../include/SFML/ /usr/include/)
