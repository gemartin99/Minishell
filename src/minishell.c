/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 02:21:47 by smiro             #+#    #+#             */
/*   Updated: 2022/12/08 02:20:53 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/libft/libft.h"

void	recive_arguments(t_msh *msh)
{
	char	*read_line;

	while (1)
	{
		read_line = readline(BLUE_T "Mi" WHITE_T "ni" YELLOW_T "s"
				WHITE_T "he" BLUE_T "ll" "🇦🇷 🧉->" RESET_COLOR);
		if (!read_line)
			exit_error("exit", g_error);
		if (check_only_space(read_line) == -1 || read_line[0] == '\0')
		{
			free(read_line);
			printf("");
		}
		else
		{
			add_history(read_line);
			if (tokenize(msh, &msh->cmd, read_line) && msh->flags->quote != 0)
			{
				if (check_nonpipables(msh->cmd, str_noquotes(msh->cmd->cmd)))
					execute_nonpipe(msh->cmd, str_noquotes(msh->cmd->cmd));
				else
					execute_cmd(&(msh->cmd), init_pipes(), 1);
			}
		}
	}
}

int	main(int ac, char **av, char **ev)
{
	t_msh	*msh;

	if (ac != 1)
		many_args(av);
	g_error = 0;
	msh = init(ev);
	wait_signal(1);
	recive_arguments(msh);
	return (0);
}
