/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 13:48:48 by amyrodri          #+#    #+#             */
/*   Updated: 2025/12/18 17:43:00 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built.h"

/*
** TODO - Ajustes necessários no built-in cd para ficar compatível com o Bash:
**
** 1. Tratar cd - :
**    - Trocar para o diretório armazenado em OLDPWD
**    - Após mudar, imprimir o novo diretório (como o bash faz)
**
** 2. Tratar número de argumentos:
**    - Se houver mais de 1 argumento além de "cd", imprimir:
**         "cd: too many arguments"
**    - Não alterar diretório nesse caso
**
** 3. Tratar caso HOME não definido:
**    - Se cd é chamado sem argumentos e HOME não existe:
**         "cd: HOME not set"
**
** 4. Mensagens de erro mais precisas:
**    - Se chdir falhar, usar perror("cd") para exibir erros corretos:
**      Ex.: Permission denied, Not a directory, etc.
**
** 5. Atualização correta de PWD e OLDPWD:
**    - Atualizar OLDPWD antes do chdir()
**    - Atualizar PWD apenas se chdir() for bem-sucedido
**    - Usar getcwd(NULL, 0) para ter buffer dinâmico
**
** 6. Expansão de "~" (opcional no projeto Minishell):
**    - "~" sozinho deve ir pro HOME (já implementado)
**    - Opcional: "~user" não é necessário no projeto
**
** 7. Não modificar variáveis de ambiente se ocorrer erro no chdir()
**
** 8. Garantir que PWD nunca fique NULL no ambiente
**
** Resumindo:
** - cd sem args → HOME
** - cd ~ → HOME
** - cd - → OLDPWD e printar novo PWD
** - Muitos args → erro
** - HOME não definido → erro
** - Mensagens iguais ao Bash
** - Atualizar PWD/OLDPWD corretamente
*/

static void	set_pwd_oldpwd(t_env_table *env, char *pwd, char *old_pwd)
{
	env_set(env, "OLDPWD", old_pwd);
	env_set(env, "PWD", pwd);
}

static void	cd_path(t_env_table *env, char *path)
{
	char	*cwd;
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (perror("cd"));
	if (chdir(path) == -1)
	{
		printf("cd: %s: No such file or directory\n", path);
		free(old_pwd);
		return ;
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("cd");
		free(old_pwd);
		return ;
	}
	set_pwd_oldpwd(env, cwd, old_pwd);
	free(old_pwd);
	free(cwd);
}

static void	cd_dash(t_env_table *env)
{
	char	*cwd;
	char	*old_pwd;
	char	*pwd;

	old_pwd = env_get(env, "OLDPWD");
	if (!old_pwd)
	{
		ft_putstr_fd("cd: OLDPWD not set\n", STDERR_FILENO);
		return ;
	}
	pwd = env_get(env, "PWD");
	if (chdir(old_pwd) == -1)
	{
		perror("cd");
		return ;
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("cd");
		return ;
	}
	printf("%s\n", cwd);
	set_pwd_oldpwd(env, cwd, pwd);
	free(cwd);
}

static void	cd_home(t_env_table *env)
{
	char	*cwd;
	char	*old_pwd;
	char	*home;

	home = env_get(env, "HOME");
	if (!home)
	{
		ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
		return ;
	}
	old_pwd = getcwd(NULL, 0);
	if (chdir(home) == -1)
	{
		free(old_pwd);
		return (perror("cd"));
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		free(old_pwd);
		return (perror("cd"));
	}
	set_pwd_oldpwd(env, cwd, old_pwd);
	free(cwd);
	free(old_pwd);
}

void	cd(t_env_table *env, t_cmd *cmd)
{
	if (!cmd->argv[1] || !ft_strcmp(cmd->argv[1], "~"))
		cd_home(env);
	else if (!ft_strcmp(cmd->argv[1], "-"))
		cd_dash(env);
	else
		cd_path(env, cmd->argv[1]);
}
