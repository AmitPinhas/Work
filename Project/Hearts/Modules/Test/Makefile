
TARGET= hearts_test
CC= gcc
CFLAGS= -ansi -g -pedantic -Wall -Werror -I../include
OBJS= 
SRCS = ../card/card.c Test.c ../UI/UI.c ../game/game.c ../round/round.c ../deck/deck.c ../player/player.c ../trick/trick.c ../hand/hand.c ../table/table.c ../decision/decision.c 
$(TARGET): $(SRCS)
	 $(CC) $(CFLAGS) -o $(TARGET) $(SRCS) 
clean:
	 rm -f $(TARGET) $(OBJS)	 

test: $(TARGET)
	./$(TARGET)

	 
