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


NAME:= $(shell basename `pwd` )
SRC = $(NAME).cc tools.cc
OBJ= $(SRC:.cc=.o)

TARGET = ../bin/$(NAME)
INTERFACEDIR= ../interface
INCLUDE= ../include

OPTS= -O2
ifeq ($(DEBUG),1)
   OPTS = -g -DDEBUG
endif

ifeq ($(DEBUG),2)
   OPTS = -O0 --coverage 
endif

CFLAGS = --std=c++11  -Wall -fexceptions $(OPTS)

all:  bin

clean:
	rm -f *.o
	rm -f $(TARGET)
	

%.o: %.cc $(INTERFACEDIR)/service.h 
	@echo "-------Compilation: $<----------------"
	g++ -o $@ -c $< $(CFLAGS) -I  $(INTERFACEDIR) -I $(INCLUDE)


bin: $(TARGET)

$(TARGET): $(OBJ)  $(INTERFACEDIR)/service.h 
	@echo "-------Generation: $@----------------"
	g++ $(CFLAGS) -rdynamic -Wl,--no-as-needed  -ldl $(OBJ) -o $(TARGET) ../bin/libfinance.a

