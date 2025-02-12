NAME := philo

SRC:= $(addprefix $(SRC_DIR), philo.c init.c actions.c routine.c utils.c monitor.c time.c tools.c)
OBJ_DIR:= .obj/
OBJ:= $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
DEPS:= $(OBJ:%.o=%.d)

CC:= cc
CCFLAGS:= -Wextra -Wall -Werror -pthread
CPPFLAGS = -MMD -MP
SRC_DIR:= src/
INCLUDES:= include/

HEADERS:= -I $(INCLUDES) 

all: welcome $(NAME)

$(NAME):  $(OBJ) 
	$(CC) $(CCFLAGS) $(OBJ)  -o $(NAME)
	@echo "$(GREEN)« La vérité ne se trouve pas dans les résultats, mais dans le processus. » $(BLUE)$(CC) $(CCFLAGS) $(OBJ) -o $(NAME)$(DEF_COLOR)"
	@echo "$(GREEN)« La philosophie a atteint son apogée avec la création de $(NAME). » - Socrate $(DEF_COLOR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@echo "$(MAGENTA)⚒️ « Je pense, donc je compile. » - Descartes, probablement, en compilant $< $(DEF_COLOR)"
	$(CC) $(CCFLAGS) $(CPPFLAGS) $(HEADERS) -o $@ -c $<


# Colors

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

welcome:
	@echo "$(CYAN)💭🤔 « L'enfer, c'est les autres... mais la compilation aussi ! » $(NAME)...  ! $(DEF_COLOR)"

clean:
	@echo "🧹 $(YELLOW)« Nettoyer les objets inutiles, c'est purifier l'âme de la programmation. » - Nietzsche$(DEF_COLOR)"
	@echo "🧹 $(YELLOW)« La déconstruction est un acte de sagesse profonde. » - Nietzsche $(DEF_COLOR)"
	rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(RED)"
	@echo "        💀"
	@echo "       (X_X)"
	@echo "      / | | \\"
	@echo "       /   \\"
	@echo "  « Ce qui ne me tue pas me rend plus fort. » - Nietzsche"
	@echo "$(DEF_COLOR)"
	@echo "$(RED)🧨💥 « La destruction précède la création ! » - Nietzsche 💥🧨 $(DEF_COLOR)"
	rm -f $(NAME)


re: fclean all
	@echo "$(CYAN)« On ne se baigne jamais deux fois dans le même code. » - Héraclite $(DEF_COLOR)"

info:
	@echo "OBJ": $(OBJ)
	@echo "DEPS": $(DEPS)
	@echo "$(GREEN)💡 « La connaissance est la lumière qui éclaire notre chemin. » - Aristote $(DEF_COLOR)"

.PHONY: all clean fclean re