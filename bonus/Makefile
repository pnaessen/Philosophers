NAME := philo_bonus

SRC:= $(addprefix $(SRC_DIR), philo_bonus.c init_bonus.c routine_bonus.c monitor_bonus.c actions_bonus.c  utils_bonus.c tools_bonus.c)
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
	$(CC) $(CCFLAGS) $(OBJ) -o $(NAME)
	@echo "$(GREEN)« Le paradoxe du philosophe : il meurt de faim entouré de spaghettis. » $(BLUE)$(CC) $(CCFLAGS) $(OBJ) -o $(NAME)$(DEF_COLOR)"
	@echo "$(GREEN)« Les processus ont atteint l'état de nirvana avec $(NAME). » - Bouddha (peut-être) $(DEF_COLOR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@echo "$(MAGENTA)⚒️ « La sémaphore est la clé de la synchronisation. » - Alan Turing, en compilant $< $(DEF_COLOR)"
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
	@echo "$(CYAN)💭🤔 « Les processus sont comme les pensées: parfois ils se bloquent ! » Compilation de $(NAME)...  ! $(DEF_COLOR)"

clean:
	@echo "🧹 $(YELLOW)« Nettoyer le code, c'est nettoyer l'esprit. » - Platon$(DEF_COLOR)"
	@echo "🧹 $(YELLOW)« La suppression est parfois un acte de création. » - Socrate $(DEF_COLOR)"
	rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(RED)"
	@echo "        💀"
	@echo "       (X_X)"
	@echo "      / | | \\"
	@echo "       /   \\"
	@echo "  « Pour obtenir le savoir, il faut d'abord tout détruire. » - Zeno"
	@echo "$(DEF_COLOR)"
	@echo "$(RED)🧨💥 « Un processus sans but est un processus mort ! » - Jean-Paul SIGTERM 💥🧨 $(DEF_COLOR)"
	rm -f $(NAME)


re: fclean all
	@echo "$(CYAN)« fork() crée, waitpid() patiente, kill() détruit, tel est le cycle de la vie. » - Spinoza $(DEF_COLOR)"

info:
	@echo "OBJ": $(OBJ)
	@echo "DEPS": $(DEPS)
	@echo "$(GREEN)💡 « La connaissance du code est la première étape vers la sagesse. » - Aristote $(DEF_COLOR)"

-include $(DEPS)

.PHONY: all clean fclean re welcome info