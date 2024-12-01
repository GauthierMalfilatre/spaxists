##
## EPITECH PROJECT, 2024
## DAMIEN
## File description:
## Makefile
##

SRC =	src/damien/linked_data/musics.c \
		src/damien/linked_data/textures.c \
		src/damien/linked_data/actors.c \
		src/damien/linked_data/scenes.c \
		src/damien/linked_data/sounds.c \
		src/damien/linked_data/sort.c \
		src/damien/linked_data/buttons.c \
		src/damien/actors/station.c \
		src/damien/actors/roket.c \
		src/damien/actors/general.c \
		src/damien/actors/player.c \
		src/damien/actors/buttons.c \
		src/damien/actors/rastazers.c \
		src/damien/game_struct.c \
		src/damien/scenes/game.c \
		src/damien/scenes/menu.c \
		src/damien/scenes/pause.c \
		src/damien/scenes/over.c \
		src/damien/actors/yohann.c \
		src/damien/load_game.c \
		src/damien/load_game2.c \
		src/damien/destroy.c \
		src/myhunter.c \
		src/saves/save.c \
		src/damien/utils.c \
		src/damien/utils2.c \

OBJ = $(SRC:.c=.o)

NAME = my_hunter

CFLAGS = -Wall -g

PLS_IGNORE := $(shell >&2 printf "\e[91m \
\e[36m   _____ ____  ___   _  __ ____________________\n")
PLS_IGNORE := $(shell >&2 printf "\e[91m \
\e[36m  / ___// __ \/   | | |/ //  _/ ___/_  __/ ___/\n")
PLS_IGNORE := $(shell >&2 printf "\e[91m \
\e[36m  \__ \/ /_/ / /| | |   / / / \__ \ / /  \__ \ \n")
PLS_IGNORE := $(shell >&2 printf "\e[91m \
\e[36m ___/ / ____/ ___ |/   |_/ / ___/ // /  ___/ / \n")
PLS_IGNORE := $(shell >&2 printf "\e[91m \
\e[36m/____/_/   /_/  |_/_/|_/___//____//_/  /____/  \n")
PLS_IGNORE := $(shell >&2 printf " \
\e[0;34m           - By Gauthier Malfilatre          \e[0m\n")
PLS_IGNORE := $(shell >&2 printf "\n")
PLS_IGNORE := $(shell >&2 printf "\e[32mBuilding $(NAME)\n")
PLS_IGNORE := $(shell >&2 printf "\e[32m    Requested : $(MAKECMDGOALS)\n")
PLS_IGNORE := $(shell >&2 printf "\e[0m\e[39m\n")

all: $(NAME)

$(NAME): $(OBj)
	@rm -f include/my.h
	@rm -f include/my_printf.h
	@make -C lib/my > /dev/null
	@cp lib/libmy.a libmy.a
	@gcc -o $(NAME) $(SRC) -lcsfml-graphics -lcsfml-window -lcsfml-audio \
	-lcsfml-system -lm -Llib/ -lmy $(CFLAGS) > /dev/null
	@echo "MAKED"

.PHONY: run
run: re
	@echo "RUNNING $(NAME)"
	@./$(NAME)
	@echo "SUCCESFULLY RUNNED $(NAME)"

.PHONY: debug
debug:	re
	valgrind --track-origins=yes --leak-check=full ./$(NAME)

.PHONY: clean
clean:
	@find . -name "*~" -delete -o -name "#*#" -delete -o -name "*.out" -delete
	@find . -name "*.o" -delete -o -name "unit_tests"  -delete > /dev/null
	@find . -name "*.a" -delete -o -name "*.log" -o -name "'#*#'" -delete
	@find . -name "*.gcda" -delete -o -name "*.gcno" -delete > /dev/null
	@find . -name "unit_test" -delete > /dev/null
	@echo "CLEAN"

.PHONY: fclean
fclean: clean
	@rm -f $(NAME)

.PHONY: code
code: fclean
	@coding-style . . > /dev/null
	@cat coding-style-reports.log
	@rm -f coding-style-reports.log
	@echo "CODING-STYLE CHECKED"

.PHONY: push
push: fclean
	@git add .
	@echo "What did you change ?" ; read COMMIT ; git commit -m "$$COMMIT"
	@git push -u origin main

re: fclean all

.PHONY: cowsay_%
cowsay_%:
	@echo " -------"
	@echo "| $(*F) |"
	@echo " -------"
	@echo "        \\   ^__^"
	@echo "         \\  (oo)\\_______"
	@echo "            (__)\\       )\\/\\"
	@echo "                ||----w |"
	@echo "                ||     ||"

.PHONY: kronk
kronk:
	@echo "Oh ouais."
