/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 13:23:31 by kamys             #+#    #+#             */
/*   Updated: 2025/11/19 14:20:23 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_env_table
{
	t_env	**buckets;
	size_t	size;
} t_env_table;

// signal.c
int				get_singal(void);
void			reset_signal(void);
void			handler(int sig);
void			setup_sig(void);

// env.c
unsigned long	hash(char *str);
t_env_table 	*env_init(size_t size);
t_env			*env_new(char *key, char *value);
void			env_set(t_env_table *table, char *key, char *value);
void			load_env(t_env_table *table, char **envp);
char			**env_to_envp(t_env_table *table);
char			*env_get(t_env_table *table, char *key);
void			env_unset(t_env_table *table, char *key);


#endif