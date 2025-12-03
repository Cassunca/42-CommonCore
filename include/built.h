/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 13:00:29 by amyrodri          #+#    #+#             */
/*   Updated: 2025/12/03 14:11:44 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_H
# define BUILT_H

# include <dirent.h>
# include "minishell.h"

typedef struct s_env_table	t_env_table;

void	print_env(t_env_table *env);
void	cd(t_env_table *env, char *path);

#endif