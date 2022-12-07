/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 02:21:47 by smiro             #+#    #+#             */
/*   Updated: 2022/12/07 02:21:49 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int ac, char **av, char **ev)
{
	t_msh	*msh;

	if (ac != 1)
		many_args(av);
	msh = init(ev);
	recive_arguments(msh);
	return (0);
}