NAME        =   philosophers
INCLUDES    =   -I include

CFLAGS      =   -Wall -Werror -Wextra $(INCLUDES)
DEBUG_FLAGS =   -fsanitize=address
SRC_DIR     =   src
OBJ_DIR     =   obj
RM          =   rm -rf
CC          =   cc

SRCS        =   $(shell find $(SRC_DIR) -name '*.c')
OBJS        =   $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TOTAL_SRCS  =   $(words $(SRCS))

# Colors
DEF_COLOR   =   \033[0;39m
GREEN       =   \033[0;92m
CYAN        =   \033[0;96m
YELLOW      =   \033[0;93m
BAR_COLOR   =   \033[42m
RED         =   \033[0;91m
RESET_COLOR =   \033[0m

all: $(NAME) norm

$(NAME): $(OBJS)
	@printf "\r\033[K"  # Clear the progress bar line
	@printf "$(CYAN)Linking $(CYAN)$(NAME)$(DEF_COLOR)...\n"
	@$(CC) $(OBJS) -o $(NAME)
	@echo "$(GREEN)All done 👍$(DEF_COLOR)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@BAR_WIDTH=30; \
	NUM_OBJS=$$(find $(OBJ_DIR) -type f | wc -l); \
	COMPLETED=$$(((NUM_OBJS + 1) * BAR_WIDTH / $(TOTAL_SRCS))); \
	printf "\r$(BAR_COLOR)%-*s$(RESET_COLOR)%-*s $(GREEN)(%d/%d) Compiling: $(YELLOW)%s$(DEF_COLOR)\033[K" \
		$$COMPLETED "" $$((BAR_WIDTH - COMPLETED)) "" $$((NUM_OBJS + 1)) $(TOTAL_SRCS) "$<"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ_DIR)
	@echo "$(CYAN)$(NAME) object files cleaned!$(DEF_COLOR)"

fclean:
	@$(RM) $(OBJ_DIR) $(NAME)
	@echo "$(CYAN)$(NAME) executable files cleaned!$(DEF_COLOR)"

re: fclean all

debug: $(OBJS)
	@$(CC) $(DEBUG_FLAGS) $(OBJS) -o $(NAME)
	@echo "\n$(GREEN)Rebuilt everything for $(NAME) in debug mode!$(DEF_COLOR)"

norm:
	@echo "$(CYAN)Looking for norm errors...$(DEF_COLOR)"
	@norminette $(SRCS) include/*.h | grep -v OK | awk '{print "\033[0;91m" $$0 "\033[0m"}' || true
	@if ! norminette $(SRCS) include/*.h | grep -q -v OK; then \
		echo "$(GREEN)No norm errors found!$(DEF_COLOR)"; \
	fi



.PHONY: all clean fclean re debug norm
