# ---------- Settings ----------
NAME	= minishell

GREEN		= \033[0;32m
YELLOW		= \033[0;33m
BLUE		= \033[0;34m
PURPLE		= \033[0;95m
NC			= \033[0m

cc			= cc
CFLAGS		= -Wall -Wextra -Werror
INCLUDE		= -I libft/srcs/includes -I include

RDFLAGS		= -lreadline -ltermcap -lncurses

RM			= rm -rf
RUNLIB		= -C libft

# Directories
PARSERDIR	= parser
UTILSDIR	= utils
LEXERDIR	= lexer
ENVDIR		= env
SRCSDIR		= srcs
OBJDIR		= objs

# Source files
SRCS		= main.c				\
			  signal.c

SRCS_ENV	= hash.c				\
			  env_init.c			\
			  env_new.c				\
			  env_table.c			\
			  env_export.c

SRCS_UTILS	= ft_isspace.c			\
			  ft_strcmp.c			\

SRCS_LEXER	= lexer.c				\
			  lexer_operetor.c		\
			  lexer_word.c			\
			  lexer_utils.c

SRCS_PARSER = parser.c				\
			  parser_syntax.c		\
			  parser_utils.c

# Add directory prefix
SRCS_PARSER	:= $(addprefix $(SRCSDIR)/$(PARSERDIR)/, $(SRCS_PARSER))

SRCS_ENV	:= $(addprefix $(SRCSDIR)/$(ENVDIR)/, $(SRCS_ENV))

SRCS_UTILS	:= $(addprefix $(SRCSDIR)/$(UTILSDIR)/, $(SRCS_UTILS))

SRCS_LEXER	:= $(addprefix $(SRCSDIR)/$(LEXERDIR)/, $(SRCS_LEXER))

SRCS		:= $(addprefix $(SRCSDIR)/, $(SRCS)) $(SRCS_ENV) $(SRCS_LEXER) $(SRCS_UTILS) $(SRCS_PARSER)

# Object files
OBJS		= $(SRCS:$(SRCSDIR)/%.c=$(OBJDIR)/%.o)
TOTAL		= $(words $(OBJS))
COUNT		= 0

# Libs
LIBFT		= libft/libft.a

# ---------- Rules ----------
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) $(LIBFT) $(RDFLAGS) -o $(NAME)
	@printf "$(GREEN)🎉 Executable $(NAME) successfully created!$(NC)\n"

# Compile object files with percentage
# $(OBJDIR)/%.o: $(SRCSDIR)/%.c
# 	@mkdir -p $(dir $@)
# 	@$(eval COUNT=$(shell echo $$(($(COUNT)+1))))
# 	@printf "\r\033[K$(BLUE)Compiling:%3d%% [%d/%d] -> %s$(NC)" \
# 		$$((100 * $(COUNT) / $(TOTAL))) $(COUNT) $(TOTAL) $<
# 	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

# $(OBJDIR)/%.o: $(SRCSDIR)/%.c
# 	@mkdir -p $(dir $@)
# 	@$(eval COUNT=$(shell echo $$(($(COUNT)+1))))
# 	@PROGRESS=$$((100 * $(COUNT) / $(TOTAL))); \
# 	BAR_LEN=$$((20 * $(COUNT) / $(TOTAL))); \
# 	BAR=$$(printf "%*s" $$BAR_LEN "" | tr ' ' '='); \
# 	EMPTY=$$(printf "%*s" $$((20-BAR_LEN)) "" | tr ' ' ' '); \
# 	printf "\r\033[K$(BLUE)Compiling: [$$BAR$$EMPTY] %3d%% [%d/%d] -> %s$(NC)" \
# 	$$PROGRESS $(COUNT) $(TOTAL) $<
# 	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJDIR)/%.o: $(SRCSDIR)/%.c
	@mkdir -p $(dir $@)
	@$(eval COUNT=$(shell echo $$(($(COUNT)+1))))
	@PROGRESS=$$((100 * $(COUNT) / $(TOTAL))); \
	BAR_LEN=$$((20 * $(COUNT) / $(TOTAL))); \
	BAR=""; EMPTY=""; \
	FULL_LEN=$$((BAR_LEN * 10 / 10)); \
	MID_LEN=$$((BAR_LEN - FULL_LEN)); \
	for i in $$(seq 1 $$FULL_LEN); do BAR="$${BAR}▓"; done; \
	for i in $$(seq 1 $$MID_LEN); do BAR="$${BAR}▒"; done; \
	for i in $$(seq $$((BAR_LEN+1)) 20); do EMPTY="$${EMPTY}░"; done; \
	printf "\r\033[K$(PURPLE)Compiling: $(GREEN)[$$BAR$$EMPTY] %3d%% $(BLUE)[%d/%d]$(PURPLE) -> %s$(NC)" \
	$$PROGRESS $(COUNT) $(TOTAL) $<
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

# Compile libft silently
$(LIBFT):
	@$(MAKE) $(RUNLIB) -j -s > /dev/null 2>&1
	@printf "\n$(GREEN)✅ Libft successfully compiled$(NC)\n"

# Cleanup
clean:
	@$(RM) $(OBJDIR)
	@$(MAKE) clean $(RUNLIB) -s > /dev/null 2>&1
	@printf "$(YELLOW)🧹 Objects cleaned$(NC)\n"

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) fclean $(RUNLIB) -s > /dev/null 2>&1
	@printf "$(YELLOW)🗑️ Executable removed$(NC)\n"

re: fclean all

.PHONY: all clean fclean re
