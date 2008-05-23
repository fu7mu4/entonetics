export CC       = g++
export CFLAGS   = -W -Wall -ansi -I../../include -DNDEBUG -O2
export LDFLAGS  = 
export EXECPATH = ../bin

all: opengl-sample pong-sample post-fx-sample qt-sample sockets-sample sound-sample sound_capture-sample voip-sample window-sample wxwidgets-sample X11-sample

opengl-sample:
	@(cd ./opengl && $(MAKE))

pong-sample:
	@(cd ./pong && $(MAKE))

post-fx-sample:
	@(cd ./post-fx && $(MAKE))

qt-sample:
	@(cd ./qt && $(MAKE))

sockets-sample:
	@(cd ./sockets && $(MAKE))

sound-sample:
	@(cd ./sound && $(MAKE))

sound_capture-sample:
	@(cd ./sound_capture && $(MAKE))

voip-sample:
	@(cd ./voip && $(MAKE))

window-sample:
	@(cd ./window && $(MAKE))

wxwidgets-sample:
	@(cd ./wxwidgets && $(MAKE))

X11-sample:
	@(cd ./X11 && $(MAKE))

.PHONY: clean mrproper

clean:
	@(cd  ./opengl        && $(MAKE) $@ && \
	  cd ../pong          && $(MAKE) $@ && \
	  cd ../post-fx       && $(MAKE) $@ && \
	  cd ../qt            && $(MAKE) $@ && \
	  cd ../sockets       && $(MAKE) $@ && \
	  cd ../sound         && $(MAKE) $@ && \
	  cd ../sound_capture && $(MAKE) $@ && \
	  cd ../voip          && $(MAKE) $@ && \
	  cd ../window        && $(MAKE) $@ && \
	  cd ../wxwidgets     && $(MAKE) $@ && \
	  cd ../X11           && $(MAKE) $@)

mrproper: clean
	@(cd  ./opengl        && $(MAKE) $@ && \
	  cd ../pong          && $(MAKE) $@ && \
	  cd ../post-fx       && $(MAKE) $@ && \
	  cd ../qt            && $(MAKE) $@ && \
	  cd ../sockets       && $(MAKE) $@ && \
	  cd ../sound         && $(MAKE) $@ && \
	  cd ../sound_capture && $(MAKE) $@ && \
	  cd ../voip          && $(MAKE) $@ && \
	  cd ../window        && $(MAKE) $@ && \
	  cd ../wxwidgets     && $(MAKE) $@ && \
	  cd ../X11           && $(MAKE) $@)
