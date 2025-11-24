/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:02:50 by amyrodri          #+#    #+#             */
/*   Updated: 2025/11/24 16:11:48 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

unsigned long	hash(char *str)
{
	unsigned long	hash;
	int				c;

	hash = 5381;
	while (*str)
	{
		c = *str++;
		hash = ((hash << 5) + hash) + c;
	}
	return (hash);
}
