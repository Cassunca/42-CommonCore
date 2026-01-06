/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 23:36:55 by kamys             #+#    #+#             */
/*   Updated: 2026/01/06 18:49:17 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include "minishell.h"

typedef struct s_env_table	t_env_table;

/*
** ============================================================================
** Prompt initialization
** ============================================================================
*/

/* Initialize PS1 (default or from environment) */
void	init_ps1(t_env_table *env);

/* Build and return the final prompt string */
char	*get_prompt(t_env_table *env);

/*
** ============================================================================
** Prompt parsing
** ============================================================================
*/

/* Parse the PS1 line */
char	*parse_ps1(t_env_table *env, char *line);

/* Skip spaces and tabs */
char	*skip_whitespace(char *s);

/*
** ============================================================================
** Prompt expansion
** ============================================================================
*/

/* Expand prompt variables (%u, %d, etc) */
char	*interpret_vars(t_env_table *env, char *s);

/* Resolve a single prompt token and update index */
char	*resolve_prompt_token(t_env_table *env, char *s, int *i);

/*
** ============================================================================
** Prompt utilities
** ============================================================================
*/

/* Return current working directory with ~ when applicable */
char	*cwd_with_tilde(t_env_table *env);

/* Expand cwd with depth limit */
char	*expand_cwd(char limit);

/* Set default prompt if PS1 is not defined */
void	prompt_default(t_env_table *env);

/*
** ============================================================================
** Prompt length calculation
** ============================================================================
*/

/* Compute final prompt length after expansion */
size_t	prompt_len(t_env_table *env, char *s);

#endif
