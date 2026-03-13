NAME		:= run.exe
SRC_PATH	:= srcs/
LIB_PATH	:= srcs/include/
OBJ_PATH	:= objs/

CC			:= i686-w64-mingw32-gcc
CFLAGS		:= -Wall -Wextra -Werror -g3
INCLUDES	:= -I $(LIB_PATH)

FILES		:= \
				main.c \
				memory_manager.c \
				overlay_manager.c \
				terminate.c \
				hack_thread.c \
				utils.c \
				esp.c
SRCS        := $(addprefix $(SRC_PATH), $(FILES))
OBJS        := $(addprefix $(OBJ_PATH), $(FILES:.c=.o))


###### RULES ######

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ -lgdi32

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_PATH)*

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re