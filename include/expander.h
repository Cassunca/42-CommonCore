/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 14:40:55 by kamys             #+#    #+#             */
/*   Updated: 2026/01/27 14:59:00 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

typedef struct s_wc
{
	char			**matches;
	char			*pattern;
	char			*dir_name;
	int				*count;
}	t_wc;

typedef struct s_shell	t_shell;

/* ========== EXPAND ========== */

void	expand_alias_ast(t_ast *root, t_shell *sh);
void	expand_ast(t_ast *root, t_shell *sh);
void	expand_cmd(t_cmd *cmd, t_shell *sh);
void	expand_redir(t_redir *redir, t_shell *sh);
void	handle_tilde(char **res, char *s, int *i, t_shell *sh);
void	handle_dolar(char **res, char *s, int *i, t_shell *sh);
char	*expand_word(char *s, t_shell *sh, int *quote);

/* ========== EXPAND QUOTES ========== */

void	handle_single_quotes(char **res, char *s, int *i);
void	handle_double_quotes(char **res, char *s, int *i, t_shell *sh);

/* ========== EXPAND UTILS ========== */

void	append_char(char **s, char c);
void	append_str(char **s, char *add);
char	**argv_add(char **argv, char *word);
char	**wildcard_expand(char	**argv, char *word);
int		match_pattern(char *p, char *s);

#endif