/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 23:36:55 by kamys             #+#    #+#             */
/*   Updated: 2025/12/21 10:43:30 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# define RED     "\033[31m"
# define GREEN   "\033[32m"
# define YELLOW  "\033[33m"
# define BLUE    "\033[34m"
# define RESET   "\033[0m"

# include "minishell.h"

typedef struct s_env_table	t_env_table;

void	init_ps1(t_env_table *env);
char	*get_prompt(t_env_table *env);
void	prompt_default(t_env_table *env);

#endif
