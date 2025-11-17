/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 13:17:23 by kamys             #+#    #+#             */
/*   Updated: 2025/11/17 17:19:09 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv)
{
	char	*line;

	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	if (isatty(STDIN_FILENO))
	{
		while (1)
		{
			if (get_singal() == SIGINT)
				reset_signal();
			ft_putstr_fd("> ", 1);
			line = get_next_line(STDIN_FILENO);
			if (!line)
				break ;
			if (!ft_strncmp(line, "exit\n", 5))
			{
				free(line);
				break ;				
			}
			free(line);
		}		
	}
	else
	{
		if (argc >= 2)
			if (!ft_strncmp(argv[1], "-c", 2))
				printf("argumento -> %s\n", argv[2]);
	}
	printf("exit\n");
	return (0);
}
