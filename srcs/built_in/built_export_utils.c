/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export_uitls.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 16:30:48 by kamys             #+#    #+#             */
/*   Updated: 2026/01/06 16:37:04 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built.h"

int	env_len(t_env_table *table)
{
	size_t	count;
	size_t	i;
	t_env	*curr;

	count = 0;
	i = 0;
	while (i < table->size)
	{
		curr = table->buckets[i++];
		while (curr)
		{
			count++;
			curr = curr->next;
		}
	}
	return (count);
}

char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	size_t	len1;
	size_t	len2;
	size_t	len3;
	char	*new_str;

	len1 = 0;
	len2 = 0;
	len3 = 0;
	if (s1)
		len1 = ft_strlen(s1);
	if (s2)
		len2 = ft_strlen(s2);
	if (s3)
		len3 = ft_strlen(s3);
	new_str = malloc(len1 + len2 + len3 + 1);
	if (!new_str)
		return (NULL);
	if (s1)
		ft_memcpy(new_str, s1, len1);
	if (s2)
		ft_memcpy(new_str + len1, s2, len2);
	if (s3)
		ft_memcpy(new_str + len1 + len2, s3, len3);
	new_str[len1 + len2 + len3] = '\0';
	return (new_str);
}

int	is_append(char *s)
{
	char	*eq;

	eq = ft_strchr(s, '=');
	if (eq && eq > s && *(eq - 1) == '+')
		return (1);
	return (0);
}
