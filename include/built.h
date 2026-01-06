/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 13:00:29 by amyrodri          #+#    #+#             */
/*   Updated: 2026/01/06 13:00:08 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_H
# define BUILT_H

# include <dirent.h>
# include "minishell.h"

typedef struct s_env_table	t_env_table;
typedef struct s_cmd		t_cmd;

void	print_env(t_env_table *env, t_cmd *cmd);
void	cd(t_env_table *env, t_cmd *path);
void	export(t_env_table *env, t_cmd *cmd);
void	unset(t_env_table *env, char *key);
void	echo(t_env_table *env, t_cmd *cmd);
void	pwd(void);

#endif
