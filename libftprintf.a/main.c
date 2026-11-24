/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocast <joaocast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/24 10:19:08 by joaocast          #+#    #+#             */
/*   Updated: 2026/11/24 10:19:47 by joaocast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"

int	main(void)
{
	int	x;
	int	r1;
	int	r2;

	x = 42;
	r1 = printf("Char: %c | Str: %s | Ptr: %p\n", 'A', "ola", &x);
	r2 = ft_printf("Char: %c | Str: %s | Ptr: %p\n", 'A', "ola", &x);
	printf("ret: %d %d\n\n", r1, r2);
	r1 = printf("Int: %d | %i | Unsigned: %u\n", -42, 42, 42);
	r2 = ft_printf("Int: %d | %i | Unsigned: %u\n", -42, 42, 42);
	printf("ret: %d %d\n\n", r1, r2);
	r1 = printf("Hex: %x | %X | Percent: %%\n", 255, 255);
	r2 = ft_printf("Hex: %x | %X | Percent: %%\n", 255, 255);
	printf("ret: %d %d\n", r1, r2);
	return (0);
}
