#------------------------------------------------------------------------------#
#   ______      __    _______ __                   __
#  / ____/___  / /___/ / ___// /_  ____ __________/ /
# / / __/ __ \/ / __  /\__ \/ __ \/ __ `/ ___/ __  /
#/ /_/ / /_/ / / /_/ /___/ / / / / /_/ / /  / /_/ /
#\____/\____/_/\__,_//____/_/ /_/\__,_/_/   \__,_/
#Developed by GoldShard 2020
#------------------------------------------------------------------------------#
#	$@ : fait référence à la cible.
#	$? : contient les noms de tous les composants plus récents que la cible.
#	$< : contient le premier composant d'une règle.
#	$^ : contient tous les composants d'une règle.
#
TARGET=../bin/libfinance.a

SRC=factory_trade.cc
OBJ= $(SRC:.cc=.o)


OPTS= -O2
ifeq ($(DEBUG),1)
   OPTS = -g -DDEBUG
endif

ifeq ($(DEBUG),2)
   OPTS = -O0 --coverage 
endif

CFLAGS=-W -Wall -ansi -pedantic --std=c++11 -fPIC $(OPTS)

all: $(TARGET) copy ../include/libfinance.h

clean:
	rm -f *.o
	rm -f $(TARGET)
	rm -f ../include/*

$(TARGET): $(OBJ)
	@echo "-------Creation de la lib: $(TARGET)----------------"
	ar -rv $(TARGET) $(OBJ)
	ranlib $(TARGET)

%.o: %.cc %.h
	@echo "-------Compilation: $<----------------"
	g++ -o $@ -c $< $(CFLAGS)

../include/libfinance.h:	*.h
	@ rm -f $@
	@echo "#include \"tools.h\" " >   $@
	@echo "#include \"trade.h\" " >>  $@
	@echo "#include \"swap.h\" " >>  $@
	@echo "#include \"factory_trade.h\" " >>  $@

copy:
	cp *.h ../include
