/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 13:00:29 by amyrodri          #+#    #+#             */
/*   Updated: 2026/01/08 11:46:25 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_H
# define BUILT_H

# include <dirent.h>
# include "minishell.h"

typedef struct s_env_table	t_env_table;
typedef struct s_cmd		t_cmd;

// ==================== EXPORT ======================
char	*ft_strjoin3(char *s1, char *s2, char *s3);
void	display_export(t_env_table *env);
int		env_len(t_env_table *table);
int		is_append(char *s);
// ==================== EXPORT ======================

void	print_env(t_env_table *env, t_cmd *cmd);
void	export(t_env_table *env, t_cmd *cmd);
void	unset(t_env_table *env, t_cmd *cmd);
void	echo(t_env_table *env, t_cmd *cmd);
void	pwd(t_env_table *env, t_cmd *cmd);
void	cd(t_env_table *env, t_cmd *path);

#endif
