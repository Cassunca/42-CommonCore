/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassunca <cassunca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 16:40:49 by cassunca          #+#    #+#             */
/*   Updated: 2025/12/03 16:55:01 by cassunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built.h"

void	unset(t_env_table *env, char *key)
{
	char	*start;

	start = key;
	while (*start)
	{
		if (*start == '=')
			return ;
		start++;
	}
	env_unset(env, key);
}
