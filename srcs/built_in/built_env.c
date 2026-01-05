/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 12:59:58 by amyrodri          #+#    #+#             */
/*   Updated: 2026/01/05 16:28:31 by amyrodri         ###   ########.fr       */
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
