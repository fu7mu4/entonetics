SRC     = $(wildcard *.cpp)
SRCGLEW = $(wildcard ./GLEW/*.c)
SRCJPEG = $(wildcard ./libjpeg/*.c)
SRCPNG  = $(wildcard ./libpng/*.c)
SRCSOIL = $(wildcard ./SOIL/*.c)
SRCZLIB = $(wildcard ./zlib/*.c)
OBJ     = $(SRC:.cpp=.o)
OBJGLEW = $(SRCGLEW:.c=.o)
OBJJPEG = $(SRCJPEG:.c=.o)
OBJPNG  = $(SRCPNG:.c=.o)
OBJSOIL = $(SRCSOIL:.c=.o)
OBJZLIB = $(SRCZLIB:.c=.o)

ifeq ($(static), yes)
    LIB     = libsfml-graphics-s.a
    LIBNAME = $(LIBPATH)/$(LIB)
    INSTALL = 
else
    LIB     = libsfml-graphics.so
    LIBNAME = $(LIBPATH)/$(LIB).$(VERSION)
    INSTALL = && $(LN) $(LNFLAGS) /usr/lib/$(LIB).$(VERSION) /usr/lib/$(LIB)
endif

all: $(LIB)

libsfml-graphics-s.a: $(OBJ) $(OBJGLEW) $(OBJJPEG) $(OBJPNG) $(OBJSOIL) $(OBJZLIB)
	$(AR) $(ARFLAGS) $(LIBNAME) $(OBJ) $(OBJGLEW) $(OBJJPEG) $(OBJPNG) $(OBJSOIL) $(OBJZLIB)

libsfml-graphics.so: $(OBJ) $(OBJGLEW) $(OBJJPEG) $(OBJPNG) $(OBJSOIL) $(OBJZLIB)
	$(CPP) $(LDFLAGS) -Wl,-soname,$(LIB).$(VERSION) -o $(LIBNAME) $(OBJ) $(OBJGLEW) $(OBJJPEG) $(OBJPNG) $(OBJSOIL) $(OBJZLIB) -lfreetype

$(OBJ): %.o: %.cpp
	$(CPP) -o $@ -c $< $(CFLAGS) -I/usr/include/freetype2

$(OBJGLEW) $(OBJJPEG) $(OBJPNG) $(OBJSOIL) $(OBJZLIB): %.o: %.c
	$(CC) -o $@ -c $< $(CFLAGSEXT)

.PHONY: clean mrproper

clean:
	@rm -rf $(OBJ) $(OBJGLEW) $(OBJJPEG) $(OBJPNG) $(OBJSOIL) $(OBJZLIB)

mrproper: clean
	@rm -rf $(LIBNAME)

install:
	@($(CP) $(LIBNAME) /usr/lib $(INSTALL))
