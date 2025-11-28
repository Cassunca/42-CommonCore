# ---------- Settings ----------
NAME        = minishell

GREEN       = \033[0;32m
YELLOW      = \033[0;33m
NC          = \033[0m

CC          = cc
CFLAGS      = -Wall -Wextra -Werror
INCLUDE     = -I libft/srcs/includes -I include

RDFLAGS		= -lreadline -ltermcap -lncurses

RM          = rm -rf
RUNLIB      = -C libft

# Directories
UTILSDIR	= utils
LEXERDIR	= lexer
ENVDIR      = env
SRCSDIR     = srcs
OBJDIR      = objs

# Source files
SRCS 		= main.c		\
			  signal.c

SRCS_ENV	= hash.c		\
			  env_init.c	\
			  env_new.c		\
			  env_table.c	\
			  env_export.c

SRCS_UTILS	= ft_isspace.c 
  
SRCS_LEXER	= lexer.c		\
			  lexer_operetor.c	\
			  lexer_word.c	\
			  lexer_utils.c 

# Add directory prefix
SRCS_ENV := $(addprefix $(SRCSDIR)/$(ENVDIR)/, $(SRCS_ENV))

SRCS_UTILS := $(addprefix $(SRCSDIR)/$(UTILSDIR)/, $(SRCS_UTILS))

SRCS_LEXER := $(addprefix $(SRCSDIR)/$(LEXERDIR)/, $(SRCS_LEXER))

SRCS := $(addprefix $(SRCSDIR)/, $(SRCS)) $(SRCS_ENV) $(SRCS_LEXER) $(SRCS_UTILS)

# Object files
OBJS = $(SRCS:$(SRCSDIR)/%.c=$(OBJDIR)/%.o)

# Libs
LIBFT = libft/libft.a

# ---------- Rules ----------
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) $(LIBFT) $(RDFLAGS) -o $(NAME)
	@printf "$(GREEN)🎉 Executable $(NAME) successfully created!$(NC)\n"

# Compile object files (auto-create subfolders)
$(OBJDIR)/%.o: $(SRCSDIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@printf "$(YELLOW)⚙️ Compiling %s -> %s$(NC)\n" "$<" "$@"

# Compile libft silently
$(LIBFT):
	@$(MAKE) $(RUNLIB) -s > /dev/null 2>&1
	@printf "$(GREEN)✅ Libft successfully compiled$(NC)\n"

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
