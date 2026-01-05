/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 12:59:58 by amyrodri          #+#    #+#             */
/*   Updated: 2026/01/22 11:33:02 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built.h"

void	print_env(t_env_table *env, t_cmd *cmd)
{
	t_env	*curr;
	size_t	i;

	(void)cmd;
	i = 0;
	while (i < env->size)
	{
		curr = env->buckets[i++];
		while (curr)
		{
			if (curr->value)
				printf("%s=%s\n", curr->key, curr->value);
			curr = curr->next;
		}
	}
}
