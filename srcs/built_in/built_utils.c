/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 16:30:48 by kamys             #+#    #+#             */
/*   Updated: 2026/01/18 11:53:19 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built.h"

int	key_len(const char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	return (i);
}

int	key_cmp(const char *s1, const char *s2)
{
	int	i;
	int	len1;
	int	len2;

	i = 0;
	len1 = key_len(s1);
	len2 = key_len(s2);
	while (i < len1 && i < len2)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (len1 - len2);
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
