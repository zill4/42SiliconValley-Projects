#include "ft_printf.h"
#include "libft.h"

// Get flags and stores them in the attribute structure.
// If there is no flag function returns a zero else then one.

static int get_flags(char flg, t_argu *arg)
{
  // So we are basically |= gating the attribute flag tracker and if it returns true.
  // Then we regard this as a found attribute, and we return for the flag that we have found.
  flg == '#' ? arg->flags |= HASH : 0;
  flg == '0' ? arg->flags |= ZERO : 0;
  flg == '-' ? arg->flags |= MINUS : 0;
  flg == ' ' ? arg->flags |= SPACE : 0;
  flg == '+' ? arg->flags |= PLUS : 0;
  return (flg == '#' || flg == '0' || flg == '-' || flg == ' ' || flg == '+');
}

// Gets the minimum number of chracters that are output. IF the number of
// Characters in the output values is less than the specified widith, blanks are added.
// to the left or the right of the values-depending on whether the left alignment is speced.

static int get_width (va_list ap, char *string, t_argu *arg)
{
  int width;
  char *num;

  width = 0;
  // If the midifier is an asterisk '*'
  if (string[width] == '*')
  {
    // Then you access the next variable argument.
    // Set it within the att to width
    arg->width = va_arg(ap, int);
    if (arg->width < 0)
    {
      arg->width *= -1; 
      arg->flags |= MINUS;
    }
    width = 1;
  }
  else
  {
    // While we get numbers...
    while (ft_isdigit(string[width]))
      width++;
    // increment save the to our string convert and return the value after free. 
    if (!width || !(num = ft_strsub(string, 0, width)))
        return (0);
    arg->width = ft_atoi(num);
    // free that num;
    free(num);
  }
  return (width);
}

// Specifies the number of string characters, the number of decial palces....
// or the number of sig figits to be output. 
// For numbers, precision sis the minimum number of digits to be written.
// If the value to be written is shorter than this number, the result is padded......

static int get_prec(va_list ap, char *string, t_argu *arg)
{
  int prec;
  char *num;

  // prec is initialized to 0;
  prec = 0;
  // if we are currently at a '.'
  if (string[0] == '.')
  {
    prec = 1;
    if (string[prec] == '*')
    {
      // take that argument, assign precision to this task.
      arg->precision = va_arg(ap, int);
      // increase the precision to at least 2.
      prec++;
    }
    else
    {
      // THis lets upgrab all the numbers of which we are precise to...
      while (ft_isdigit(string[prec]))
        prec++;
      if (!(num = ft_strsub(string, 1, prec)))
        return (0);
      arg->precision = (prec != 1) ? ft_atoi(num) : 0;
      free (num);
    }
  }
    return (prec);
}


// modifies the length of the data type.
// as set within a given chart....

static int get_mod(char *string, t_argu *arg)
{
  int len;

  len = 0;
  while (string[len] == 'h' || string[len] == 'l' || string[len] == 'j' || string[len] == 'z')
  {
    // just check for given type and flag it if the return is true
    // hh cannout be hl or jj for example 
    if (string[len] == 'h' )
        string[len + 1] == 'h' ? (arg->flags |= HH) : (arg->flags |= H);
    if (string[len] == 'l')
        string[len + 1] == 'l' ? (arg->flags |= LL) : (arg->flags |= L);
    if (arg->flags == HH || arg->flags == LL)
      len++;
    if (string[len] == 'j')
      arg->flags |= J;
    if (string[len] == 'z')
      arg->flags |= Z;
    len++;
  }
  return (len); //Distance traveled within the parsing.
}


// Get the flags, width, precision and len of the format. 
// returns bool yes or no whether the format is valid.
int   get_atts(char **string, va_list ap, t_argu *arg)
{
  char *init;
  int f_width;

  init = *string;
  while (get_flags(**string, arg))
      (*string)++;
// We now check for the width and have that return us the proper values.
  while ((f_width = get_width(ap, *string, arg)))
  {
    // width is returned as either a 0, 1 or the length of the characters 
    arg->flags |= WIDTH;
    // move format forward the correct number of characters in width.
    (*string) += f_width;
  }
  while ((f_width = get_prec(ap, *string, arg)))
  {
    // if precision exists bit shift flag to precision
    if (arg->precision >= 0)
        arg->flags |= PRECISION;
    (*string) += f_width;
  }
  while ((f_width = get_mod(*string, arg)))
      (*string) += f_width;
  // return if the format is moved forward further than the initial copy?
  return (*string > init);
}
