/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcrisp <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 10:45:50 by jcrisp            #+#    #+#             */
/*   Updated: 2018/09/20 19:09:30 by jcrisp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/ft_printf.h"
#include <stdio.h>
#include <limits.h>

// Takes in a string*, and a variable number of arguments.
int ft_printf(char* string, ...)
{
  // We return character count as a part of the function.
  int   count;
  // Length is the a container for count
  int   len;
  // Our variable list to be be iterated through.
  va_list ap;

  count = 0;
  va_start(ap, string);
  while (*string)
  {
    // If we run into the flag.
    if (*string == '%')
    {
        // Move the character forward.
        string += 1;
        
        count += 1;
    }
    string += 1;
  }  
  // exit the list.
  va_end(ap);
  return (count);
}

int   main()
{
  printf("First example %d", 1);
  ft_printf("First example %d", 1);
  return (0);
}