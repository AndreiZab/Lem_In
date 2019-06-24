/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhealitt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 22:07:46 by rhealitt          #+#    #+#             */
/*   Updated: 2019/06/23 22:22:08 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

void	ft_ft(char **asd)
{
	char 	*ptr;
	//s++;
	*asd = "asdfggggg";
}

int main()
{
	char *s;
	char q[10] = "ti pidir";

	s = (char *)malloc(sizeof(char) * 10);
	s[0] = 'a';
	s[1] = 'p';
	s[2] = '\0';
	ft_ft(&s);
	printf("%s\n%s\n", s, q);
}
