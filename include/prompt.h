/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 23:36:55 by kamys             #+#    #+#             */
/*   Updated: 2026/01/22 11:37:18 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include "minishell.h"

typedef struct s_env_table	t_env_table;

/* ========== PROMPT ========== */

void	init_ps1(t_env_table *env);
char	*get_prompt(t_env_table *env);

/* ========== PARSING ========== */

char	*parse_ps1(t_env_table *env, char *line);
char	*skip_whitespace(char *s);

/* ========== EXPANSION ========== */

char	*interpret_vars(t_env_table *env, char *s);
char	*resolve_prompt_token(t_env_table *env, char *s, int *i);

/* ========== UTILS ========== */

char	*cwd_with_tilde(t_env_table *env);
char	*expand_cwd(t_env_table *env, char limit);
void	prompt_default(t_env_table *env);

/* ========== LENGTH ========== */

size_t	prompt_len(t_env_table *env, char *s);

#endif
