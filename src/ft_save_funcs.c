/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inunez-g <inunez-g@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 11:22:53 by inunez-g          #+#    #+#             */
/*   Updated: 2022/09/24 11:22:56 by inunez-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*save_words(char *str, int *i)
{
	int	j;

	j = *i;
	pass_word(str, i);
	return (ft_substr(str, j, *i - j));
}
