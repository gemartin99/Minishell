/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 23:40:38 by smiro             #+#    #+#             */
/*   Updated: 2022/12/11 23:40:43 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		rl_replace_line("HOLA", 0);
		write(1, "\n", 1);
		kill(0, SIGCONT);
	}
	return ;
}

void	wait_signal(void)
{
	struct	sigaction sa;
	sa.sa_handler = &signal_handler;
	sa.sa_flags = SA_RESTART;

	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
}