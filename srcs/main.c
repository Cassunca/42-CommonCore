/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 13:17:23 by kamys             #+#    #+#             */
/*   Updated: 2025/11/19 14:24:32 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_env_table	*env = env_init(97);

	load_env(env, envp);
	setup_sig();
	if (isatty(STDIN_FILENO))
	{
		while (1)
		{
			line = readline("> ");
			if (!line)
				break ;
			if (*line)
				add_history(line);
			if (!ft_strncmp(line, "env", 4))
			{
				char **new_env = env_to_envp(env);
				for (size_t i = 0; new_env[i]; i++)
					printf("%s\n",	new_env[i]);
			}
			if (!ft_strncmp(line, "exit", 5))
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
				printf("algum dia vai começar a executar -> %s\n", argv[2]);
	}
	rl_clear_history();
	rl_cleanup_after_signal();
	printf("exit\n");
	return (0);
}
