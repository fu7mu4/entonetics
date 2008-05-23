LIB = libcsfml-graphics.so
SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

all: $(LIB)

libcsfml-graphics.so: $(OBJ)
	$(CPP) $(LDFLAGS) -Wl,-soname,$(LIB).$(VERSION) -o $(LIBPATH)/$@.$(VERSION) $(OBJ) -lsfml-graphics -lsfml-window -lsfml-system

$(OBJ): %.o: %.cpp
	$(CPP) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	@rm -rf $(OBJ)

mrproper: clean
	@rm -rf $(LIBPATH)/$(LIB)

install:
	@($(CP) $(LIBPATH)/$(LIB).$(VERSION) /usr/lib && $(LN) $(LNFLAGS) /usr/lib/$(LIB).$(VERSION) /usr/lib/$(LIB))