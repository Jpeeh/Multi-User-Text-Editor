CC		:= gcc
C_FLAGS := -Wall -Wextra

OUT		:= out
SRC		:= src
INCLUDE	:= include

LIBRARIES	:= -lncurses

EXECUTABLE	:= server

all: $(OUT)/$(EXECUTABLE)

clean:
	-$(RM) $(OUT)/$(EXECUTABLE)

run: all
	./$(OUT)/$(EXECUTABLE)

$(OUT)/$(EXECUTABLE): $(SRC)/*.c
	$(CC) $(C_FLAGS) -I$(INCLUDE) $^ -o $@ $(LIBRARIES)