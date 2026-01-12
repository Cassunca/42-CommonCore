/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 21:08:53 by kamys             #+#    #+#             */
/*   Updated: 2026/01/11 21:10:32 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	append_char(char **s, char c)
{
	char	tmp[2];
	char	*new;

	tmp[0] = c;
	tmp[1] = 0;
	new = ft_strjoin(*s, tmp);
	free(*s);
	*s = new;
}

void	append_str(char **s, char *add)
{
	char	*new;

	new = ft_strjoin(*s, add);
	free(*s);
	*s = new;
}
