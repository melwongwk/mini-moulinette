/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnonpras <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:06:14 by hnonpras          #+#    #+#             */
/*   Updated: 2023/06/10 17:36:35 by hnonpras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include<stdio.h>

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (*str != '\0')
	{
		str++;
		len++;
	}
	return (len);
}

/*
int main(int argc, char **argv)
{
	for(int i = 0; i < argc; i++)
	{
		printf("%s : %d \n", argv[i], ft_strlen(argv[i]));
	}
	return 0;
}
*/
