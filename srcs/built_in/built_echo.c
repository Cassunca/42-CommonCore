/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 17:51:35 by cassunca          #+#    #+#             */
/*   Updated: 2025/12/05 16:06:02 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built.h"

/*
** TODO: O que precisa ser corrigido no comando echo
**
** 1️⃣ Remover a lógica baseada em `line` e índices fixos
**    - O echo NÃO deve ler a linha crua inteira
**    - Ele deve receber argumentos já separados pelo parser (char **args)
**
** 2️⃣ Implementar verificação da flag -n corretamente
**    - Aceitar "-n", "-nnn", "-n -n", etc
**    - Criar função is_flag_n() para validar múltiplas flags seguidas
**
** 3️⃣ Evitar acessar os caracteres um por um com printf("%c")
**    - Isso está causando duplicação após expandir variáveis
**    - O echo deve imprimir por argumentos com controle de espaço
**
** 4️⃣ Reescrever totalmente a lógica de expansão de variáveis
**    - A função environment() está limitada e depende de "line"
**    - A expansão deve ser feita por argumento (print_with_expand())
**    - Precisa suportar:
**        ✔ $VAR
**        ✔ $? (exit status)
**        ✔ variáveis seguidas de texto (ex: "$HOME/teste")
**        ✘ Não expandir dentro de aspas simples
**
** 5️⃣ Aspas NÃO são responsabilidade do echo
**    - O lexer deve identificar trechos com/sem expansão
**    - O parser deve remover as aspas antes de chegar ao echo
**    - Echo recebe tokens já prontos para impressão
**
** 6️⃣ Cuidado com espaços
**    - Echo deve imprimir espaço SOMENTE entre argumentos
**    - Nunca imprimir espaço extra no final
**
** 7️⃣ Tratar variáveis não encontradas
**    - Ex: "$NAOEXISTE" deve resultar em print vazio
**
** Resumo da arquitetura correta:
**    Lexer  →  separa tokens e trata aspas
**    Parser →  cria array de argumentos para o echo
**    Echo   →  Apenas imprime + expansão simples
**
** Resultado final esperado:
**    int echo(t_env_table *env, char **args)
**    {
**        - identificar flags -n
**        - expandir variáveis quando permitido
**        - imprimir argumentos com espaço adequado
**        - suprimir newline se -n foi encontrado
**    }
*/

static void	environment(t_env_table *env, char *line, int *i)
{
	char	*key_word;
	char	*value;
	int		j;

	j = *i;
	while (line[j] != ' ' && line[j])
		j++;
	key_word = ft_substr(line, *i + 1, (j - *i) - 1);
	value = env_get(env, key_word);
	printf("%s", value);
	*i = j;
}

void	echo(t_env_table *env, char *flag, char *line)
{
	int	i;
	int	flag_n;
	// atualizar codigo ^~^
	(void)env;
	if (!ft_strcmp(flag, "-n"))
	{
		i = 8;
		flag_n = 0;
	}
	else
	{
		i = 5;
		flag_n = 1;
	}
	while (line[i])
	{
		if (line[i] == '$')
			environment(env, line, &i);
		printf("%c", line[i]);
		i++;
	}
	if (flag_n)
		printf("\n");
}
