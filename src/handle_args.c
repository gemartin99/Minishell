/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 05:27:11 by smiro             #+#    #+#             */
/*   Updated: 2022/12/07 05:27:13 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char *get_comand(char *read_line)
{
	int	i;
	int	start;

	i = 0;
	while (read_line[i] == 32 || (read_line[i] >= 9 && read_line[i] <= 13))
		i++;
	start = i;
	while (read_line[i] && read_line[i] != 32 
			&& !(read_line[i] >= 9 && read_line[i] <= 13))
		i++;
	*read_line += i;
	return (ft_substr(read_line, start, i));
}

static t_cmd	*add_cmd(char *read_line)
{
	t_cmd *temp;

	temp = ft_calloc(sizeof(t_cmd), 1);
	if (!temp)
		exit_error("Error malloc", 9);
	temp->cmd = get_comand(read_line);
	temp->next = NULL;
	return (temp);
}

static void	tokenize(t_msh *msh, char *read_line) //
{
	int i;
	t_cmd	*temp;

	temp = msh->cmd;
	i = 0;
	while (i <= msh->flags->pipe)
	{
		temp = add_cmd(read_line);
		temp = temp->next;
	}
}

void	recive_arguments(t_msh *msh) //Leer la linea, tokenizar y ejecutar
{
	char	*read_line;

	while (1)
	{
		read_line = readline( BLUE_T "Mi" WHITE_T "ni" YELLOW_T "s"
				WHITE_T "he" BLUE_T "ll" "🇦🇷 🧉->" RESET_COLOR);
		if (!read_line)
			exit_error("exit", 0);
		if (read_line[0] == '\0')
			printf("");
		else
		{
			add_history(read_line);
			tokenize(msh, read_line);
		}
	}
}
