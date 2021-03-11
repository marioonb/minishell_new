/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelorge <mbelorge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 11:12:31 by mbelorge          #+#    #+#             */
/*   Updated: 2021/02/16 18:58:33 by mbelorge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	reset_fd(t_ms *ms)
{
	dup2(ms->in, 0);
	dup2(ms->out, 1);
	dup2(ms->err, 2);
}

void	close_pipe(t_ms *ms)
{
	close(ms->fdp[0]);
	close(ms->fdp[1]);
}
