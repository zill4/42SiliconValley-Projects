#include "ft_printf.h"
#include "libft.h"

// Why is this static?  bascially checks if each specifier is in the string...
// I feel like I can use strchr or something to find the character position....
static int spec_check(char c, char *str)
{
  int i;

  i = 0;

  while (str[i])
  {
      if (c == str[i])
        return (i);
    i++;
  }
  return (-1);
}

static int get_spec(char c, t_argu *arg, char *spec)
{
  int *tbl;
  int specifier;

  tbl = ft_memalloc(sizeof(int) * SPECI_SIZE);
  tbl[S] = S_BIT;
  tbl[P] = P_BIT;
  tbl[D] = D_BIT;
  tbl[I] = I_BIT;
  tbl[O] = O_BIT;
  tbl[U] = U_BIT;
  tbl[LOWER_X] = LOW_X_BIT;
  tbl[UPPER_X] = UPP_X_BIT;
  tbl[C] = C_BIT;
  // I'm not quite sure how |= gating works.
  if (((specifier = spec_check(c, spec)) != -1) && c)
    arg->flags |= tbl[specifier];
  free(tbl);
  return (specifier);
}

// parse the specifier to the following input 
int   spec_buff(va_list ap, char **string, t_argu *arg)
{
  // Specifier ends up getting set to a given bit value.
  int specifier;
  int valid;
  // storing the converted string %123.d
  char *conv;
  
  // This should already be assigned to zero
  arg->flags = 0;
  // allocate memory for our specifier string, to speci_size.
  if (!(conv = (char *)malloc(SPECI_SIZE)))
    return (0);
  conv = ft_strncpy(conv, SPECIFIERS, SPECI_SIZE);
  specifier = PRINTF_FAILURE; // Initialized to -1?
  while (**string)
  {
    // This basically if is true means it found the specifier...
    if ((spec_check(**string, conv) != -1) && (specifier = get_spec(**string, arg, conv)))
        break;
    if (!(valid = get_atts(string, ap, arg)))
        break;
  }
  free(conv);
  return (specifier);
}