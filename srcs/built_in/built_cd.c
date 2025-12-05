/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 13:48:48 by amyrodri          #+#    #+#             */
/*   Updated: 2025/12/05 16:32:50 by kamys            ###   ########.fr       */
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
** - cd - → OLDPWD e printar novo PWD
** - Muitos args → erro
** - HOME não definido → erro
** - Mensagens iguais ao Bash
** - Atualizar PWD/OLDPWD corretamente
*/

void	cd(t_env_table *env, char *path)
{
	char	*cwd;
	char	*old_pwd;
	char	*home;
	// atualizar codigo ^~^
	if (!path || !ft_strcmp(path, "~"))
	{
		home = env_get(env, "HOME");
		chdir(home);
		old_pwd = env_get(env, "PWD");
		cwd = getcwd(NULL, 0);
		if (!cwd)
			perror("cd");
		else
		{
			env_set(env, "PWD", cwd);
			env_set(env, "OLDPWD", old_pwd);
			free(cwd);
		}
		return ;
	}
	if (chdir(path) == -1)
	{
		printf("cd: %s: No such file or directory\n", path);
		return ;
	}
	old_pwd = env_get(env, "PWD");
	cwd = getcwd(NULL, 0);
	if (!cwd)
		perror("cd");
	else
	{
		env_set(env, "PWD", cwd);
		env_set(env, "OLDPWD", old_pwd);
		free(cwd);
	}
}
