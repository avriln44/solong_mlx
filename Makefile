NAME := so_long

CC := cc

CFLAGS := -Wall -Wextra -Werror

MLX42_DIR 			:= ./library/MLX42
LIBFT_DIR			:= ./library/libft
GET_NEXT_LINE_DIR 	:= ./library/get_next_line

MLX_FLAGS := -L$(MLX42_DIR)/build -lmlx42 -lglfw -ldl -lm -lGL
LIBFT			:= ${LIBFT_DIR}/libft.a
GET_NEXT_LINE	:= ${GET_NEXT_LINE_DIR}/get_next_line.a

INCLUDE 		:= -I ${LIBFT_DIR} -I ${GET_NEXT_LINE_DIR} -I ${MLX42_DIR} -I ./includes/


MAIN			:= ./srcs/main

ERRORS			:= ./srcs/errors

PARSING			:= ./srcs/parsing

GAME			:= ./srcs/game

MAIN_C			:= main.c \

ERRORS_C		:= error_handling.c \

PARSING_C 		:=  check_map.c \
					check_path.c \
					read_map.c \
					utils.c \

GAME_C			:= load_image.c \
				   display_map.c \
				   game_start.c \

SRCS			:= 	$(addprefix ${MAIN}/, ${MAIN_C})		\
					$(addprefix ${PARSING}/, ${PARSING_C})	\
					$(addprefix ${ERRORS}/, ${ERRORS_C})	\
					$(addprefix ${GAME}/, ${GAME_C})	\

OBJS			:= ${SRCS:.c=.o}


all: ${LIBFT} ${GET_NEXT_LINE} ${NAME}

%.o:	%.c
	${CC}	${CFLAGS}	-o $@ -c $< ${INCLUDE}

${NAME}:	${OBJS} ${LIBFT} ${GET_NEXT_LINE}
			@cc ${OBJS} ${LIBFT} ${GET_NEXT_LINE} $(MLX_FLAGS) -o ${NAME}


${LIBFT}:
		@$(MAKE) -C ${LIBFT_DIR}

${GET_NEXT_LINE}:
		@$(MAKE) -C ${GET_NEXT_LINE_DIR}

${MLX_DIR}:
		@$(MAKE) -C ${MLX_DIR}

clean:
	rm	-f	$(OBJS)
	@$(MAKE) -C ${LIBFT_DIR} clean
	@$(MAKE) -C ${GET_NEXT_LINE_DIR} clean


fclean:
	rm	-f	${NAME} ${OBJS}
	@$(MAKE) -C ${LIBFT_DIR} fclean
	@$(MAKE) -C ${GET_NEXT_LINE_DIR} fclean

re:    fclean    all

.PHONY:    all    clean    fclean    re
