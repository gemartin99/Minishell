/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 05:18:59 by smiro             #+#    #+#             */
/*   Updated: 2022/12/08 05:19:00 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_cmd	*ft_last(t_cmd **cmd)
{
	t_cmd	*temp;
	
	temp = *cmd;
	while (temp->next)
		temp = temp->next;
	return (temp);
}