NAME		:= run.exe
SRC_PATH	:= srcs/bin/
LIB_PATH	:= srcs/include/

CC			:= i686-w64-mingw32-gcc
CFLAGS		:= -Wall -Wextra -Werror -g3
INCLUDES	:= -I $(LIB_PATH)

SRCS		:= \
	$(SRC_PATH)main.c \
	$(SRC_PATH)initializer.c \
	$(SRC_PATH)terminate.c \
	$(SRC_PATH)cheats.c \
	$(SRC_PATH)utils.c
OBJS		:= $(SRCS:.c=.o)


###### RULES ######

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

%:.o %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
clean:
	rm -f $(OBJS)

fclean:
	rm -f $(NAME)
	rm -f $(OBJS)

re: fclean all

.PHONY: all clean fclean re