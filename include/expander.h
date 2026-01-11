/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 14:40:55 by kamys             #+#    #+#             */
/*   Updated: 2026/01/10 21:32:39 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

typedef struct s_shell	t_shell;

void	expand_alias_ast(t_ast *root, t_shell *sh);
void	expand_ast(t_ast *root, t_env_table *env);

#endif