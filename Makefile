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
ALIASDIR	= alias
EXPANDDIR	= expander
EXECDIR		= exec
BUILTDIR	= built_in
PROMPTDIR	= prompt
PARSERDIR	= parser
BUILTDIR	= built_in
UTILSDIR	= utils
LEXERDIR	= lexer
ENVDIR		= env
SRCSDIR		= srcs
OBJDIR		= .objs

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
			  frees.c

SRCS_LEXER	= lexer.c				\
			  lexer_operetor.c		\
			  lexer_word.c			\
			  lexer_utils.c

SRCS_BUILT	= built_env.c			\
			  built_cd.c			\
			  built_export.c		\
			  built_export_dis.c	\
			  built_export_utils.c	\
			  built_unset.c			\
			  built_echo.c			\
			  built_pwd.c

SRCS_PARSER = parser.c				\
			  parser_syntax.c		\
			  parser_utils.c		\
			  parse_and.c			\
			  parse_command.c		\
			  parse_or.c			\
			  parse_pipe.c			\
			  parse_sequence.c		\
			  parse_subshell.c	

SRCS_PROMPT	= prompt_init.c			\
			  prompt_expand.c		\
			  prompt_utils.c		\
			  prompt_len.c			\
			  prompt_parser.c		

SRCS_EXPAND	= expand_ast.c			\
			  expand_alias.c		\
			  expand_cmd.c			\
			  expand_quotes.c		\
			  expand_redir.c		\
			  expand_tilde.c		\
			  expand_utils.c		\
			  expand_vars.c			\
			  expand_word.c

SRCS_ALIAS	= alias_init.c			\
			  alias_export.c		\
			  alias_new.c			\
			  alias_table.c			

SRCS_EXEC	= exec.c				\
			  exec_cmd.c			\
			  exec_redirect.c		\
			  exec_pipe.c			\
			  exec_and.c			\
			  exec_or.c				\
			  exec_path.c			\
			  exec_utils.c			\
			  exec_heredoc.c		\
			  exec_heredoc_utils.c	\
			  exec_heredoc_utils2.c\

SRCS_BUILT	= built_env.c		\
			  built_cd.c		\
			  built_export.c

# Add directory prefix
SRCS_ALIAS	:= $(addprefix $(SRCSDIR)/$(ALIASDIR)/, $(SRCS_ALIAS))

SRCS_EXPAND	:= $(addprefix $(SRCSDIR)/$(EXPANDDIR)/, $(SRCS_EXPAND))

SRCS_EXEC	:= $(addprefix $(SRCSDIR)/$(EXECDIR)/, $(SRCS_EXEC))

SRCS_BUILT	:= $(addprefix $(SRCSDIR)/$(BUILTDIR)/, $(SRCS_BUILT))

SRCS_PROMPT	:= $(addprefix $(SRCSDIR)/$(PROMPTDIR)/, $(SRCS_PROMPT))

SRCS_PROMPT	:= $(addprefix $(SRCSDIR)/$(PROMPTDIR)/, $(SRCS_PROMPT))

SRCS_PARSER	:= $(addprefix $(SRCSDIR)/$(PARSERDIR)/, $(SRCS_PARSER))

SRCS_BUILT	:= $(addprefix $(SRCSDIR)/$(BUILTDIR)/, $(SRCS_BUILT))

SRCS_ENV	:= $(addprefix $(SRCSDIR)/$(ENVDIR)/, $(SRCS_ENV))

SRCS_UTILS	:= $(addprefix $(SRCSDIR)/$(UTILSDIR)/, $(SRCS_UTILS))

SRCS_LEXER	:= $(addprefix $(SRCSDIR)/$(LEXERDIR)/, $(SRCS_LEXER))

SRCS		:= $(addprefix $(SRCSDIR)/, $(SRCS)) $(SRCS_ENV) $(SRCS_LEXER) $(SRCS_UTILS) $(SRCS_BUILT) $(SRCS_PARSER) $(SRCS_PROMPT) $(SRCS_EXEC) $(SRCS_EXPAND) $(SRCS_ALIAS)

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
