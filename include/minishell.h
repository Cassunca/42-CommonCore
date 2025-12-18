/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 13:23:31 by kamys             #+#    #+#             */
/*   Updated: 2026/01/22 11:44:30 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "env.h"
# include "built.h"
# include "lexer.h"
# include "utils.h"
# include "parser.h"
# include "colors.h"
# include "prompt.h"
# include "exec.h"
# include "expander.h"
# include "alias.h"

# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <string.h>
# include <limits.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_alias_table	t_alias_table;

typedef struct s_shell
{
	t_env_table		*env;
	t_alias_table	*aliases;
	int				last_status;
}	t_shell;

/* ========== INPUT ========== */

void	input(char	*line, t_shell *sh);

/* ========== FREE ========== */

void	free_tokens(t_token *tok);
void	free_redir(t_redir *r);
void	free_cmd(t_cmd *cmd);
void	free_ast(t_ast *root);
void	clean_up(t_shell *sh);

/* ========== SIGNAL ========== */

int		get_signal(void);
void	reset_signal(void);
void	handler(int sig);
void	setup_sig(void);

#endif