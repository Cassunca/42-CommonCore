/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 14:40:55 by kamys             #+#    #+#             */
/*   Updated: 2026/01/22 11:46:44 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

typedef struct s_shell	t_shell;

/* ========== EXPAND ========== */

void	expand_alias_ast(t_ast *root, t_shell *sh);
void	expand_ast(t_ast *root, t_env_table *env);
void	expand_cmd(t_cmd *cmd, t_env_table *env);
void	expand_redir(t_redir *redir, t_env_table *env);
void	handle_tilde(char **res, char *s, int *i, t_env_table *env);
void	handle_dolar(char **res, char *s, int *i, t_env_table *env);
char	*expand_word(char *s, t_env_table *env);

/* ========== EXPAND QUOTES ========== */

void	handle_single_quotes(char **res, char *s, int *i);
void	handle_double_quotes(char **res, char *s, int *i, t_env_table *env);

/* ========== EXPAND UTILS ========== */

void	append_char(char **s, char c);
void	append_str(char **s, char *add);

#endif