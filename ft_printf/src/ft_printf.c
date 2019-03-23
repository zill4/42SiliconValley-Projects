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
#include "ft_printf.h"
#include "libft.h"

static int print_no_spec(char c, t_argu *arg)
{
  int len;
  if (!(arg->flags & MINUS))
    len = print_spaces(arg->width, 1, arg->flags);
  ft_putchar(c);
  if (arg->flags & MINUS)
    len = print_spaces(arg->width, 1, arg->flags);
  return (len);
}
// Now that most of the flags have been collected each specifier can be printed.
static int print_spec(char string, va_list ap, t_argu *arg, int i)
{
  int   print;

  print = 0;
  if (i == S)
    print = print_str(ap, arg);
  else if (i == D || i == I || i == U)
    print = print_dec(ap, arg);
  else if (i == O)
    print = print_oct(ap, arg);
  else if (i == P || i == LOWER_X || I == UPPER_X)
    print = print_hex(ap, arg);
  else if (i == C)
    print = print_char(ap, arg);
  else
    print = print_no_spec(string, arg);
  return (print);
}
// Same as print_stdout
static int print_buff(const char *string[], va_list ap)
{
  // the current specifier holder
  int specifier;
  // attribute holder.
  t_argu arg;

  //initialize current specifier to 0's.
  arg.flags = 0;
  arg.width = 0;
  arg.precision = 0;
  // return the specifier found from the given % flag.
  specifier = spec_buff(ap, (char **)string, &arg);
  if (!**string)
    return (-1);
  // return the specifier function for formatting???????
  // Flags and modifiers gathered, time to print.
  return (print_spec((char)**string, ap, &arg, specifier));
}
// Takes in a string*, and a variable number of arguments.
int ft_printf(const char* string, ...)
{
  // We return character count as a part of the function.
  int   count;
  // Length is the a container for count
  int   len;
  // Our variable list to be be iterated through.
  va_list ap;
  len = 0;
  count = 0;
  va_start(ap, string);
  while (*string)
  {
    // If we run into the flag.
    if (*string == '%')
    {
        // Move the character forward.
        string += 1;
        // check if the buffer is returning prorperly after print attempt.
        if ((len = print_buff(&string, ap)) == PRINTF_FAILURE)
            break ;
        count += len;
    }
    else
    {
      ft_putchar(*string);
      count += 1;
    }
    string += 1;
  }  
  // exit the list.
  va_end(ap);
  return (count);
}

