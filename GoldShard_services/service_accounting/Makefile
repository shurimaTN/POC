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
SRC = $(NAME).cc accounting_trade_data.cc cre_generator.cc cre_function.cc
OBJ= $(SRC:.cc=.o)

TARGET = ../bin/$(NAME).so

LIBDIR=../bin
INCLUDE_LIBFIN=../include
INTERFACEDIR= ../interface

OPTS= -O2
ifeq ($(DEBUG),1)
   OPTS = -g -DDEBUG
endif

ifeq ($(DEBUG),2)
   OPTS = -O0 --coverage  
endif

CFLAGS = --std=c++11  -Wall -fexceptions -fPIC $(OPTS)

INCLUDE =  -I $(INTERFACEDIR) -I $(INCLUDE_LIBFIN)

all:  service

clean:
	rm -f $(TARGET)
	rm -f *.o

service: $(TARGET)

%.o: %.cc $(INTERFACEDIR)/service.h $(INCLUDE_LIBFIN)/libfinance.h
	@echo "-------Compilation: $<----------------"
	g++ -o $@ -c $< $(CFLAGS) $(INCLUDE)

$(TARGET): $(INTERFACEDIR)/service.h $(INCLUDE_LIBFIN)/libfinance.h $(LIBDIR)/libfinance.a $(OBJ)
	@echo "-------Generation: $<----------------"
	g++ $(CFLAGS)  -rdynamic -shared  $(OBJ) -o $(TARGET) $(INCLUDE) -Wl,--whole-archive $(LIBDIR)/libfinance.a -Wl,--no-whole-archive


