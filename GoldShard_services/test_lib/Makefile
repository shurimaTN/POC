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
SRCFILE = $(NAME).cc
TARGET = ../bin/$(NAME)
INTERFACEDIR= ../interface

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
	rm $(TARGET)

bin: $(TARGET)

$(TARGET): $(SRCFILE) $(INTERFACEDIR)/service.h
	g++ $(CFLAGS) -rdynamic -Wl,--no-as-needed  -ldl $(SRCFILE) -o $(TARGET) -I  $(INTERFACEDIR)


