NAME = philo

CC= gcc
CFLAGS = -Wall -Wextra -Werror

DEPS = ${OBJS:.o=.d}

INC = ./includes/philo.h

SRC_PATH = ./srcs

SRCS = philo.c initialize.c thread.c dead_file.c philo_utils.c \

SRC = $(addprefix $(SRC_PATH)/, $(SRCS))

OBJS_PATH = ./objs
OBJS_NAMES = $(SRC:.c=.o)

OBJ := $(patsubst $(SRC_PATH)%,%,$(filter $(SRC_PATH)%,$(OBJS_NAMES)))

OBJS = $(addprefix $(OBJS_PATH), $(OBJ))

GREEN = \033[0;32m
RED = \033[0;31m
NC = \033[0m
YELLOW = \033[33m

all: $(NAME)

$(NAME): $(OBJS) $(INC)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)Compilation complete! \n$(YELLOW)$(NAME) is ready to execute.$(NC)"

$(OBJS): $(OBJS_PATH)/%.o: $(SRC_PATH)/%.c $(INC)
	@mkdir -p $(OBJS_PATH)
	@$(CC) $(CFLAGS) -MMD -MP -c $< -o $@
	@echo "$(GREEN)Compiled:$(NC) $<"
	
clean:
	@rm -rf $(OBJS_PATH)
	@rm -rf $(DEPS)
	@echo "$(RED)Cleaned up object files.$(NC)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(RED)Cleaned up executable.$(NC)"

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re bonus