CC          =  gcc
LIBSDIR     =  ./libs
SOURCE      =  $(foreach dir, $(SOURCEDIR), $(wildcard $(dir)/*.c))
OBJECTS     =  $(addprefix $(LIBSDIR)/, $(notdir $(SOURCE:.c=.o)))
LIBNAME     =  convertorslib
SOURCEDIR   =  ./convertors

default: clean all

all: $(LIBSDIR)/$(LIBNAME).a

clean:
	rm -rf $(LIBSDIR)/*

$(LIBSDIR)/%.o: $(SOURCE)
	$(CC) -c $< -o $@

$(LIBSDIR)/$(LIBNAME).a: $(OBJECTS)
	ar rcs $@ $^
	rm -rf $(LIBSDIR)/*.o
