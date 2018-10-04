#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <memory.h>

int main()
{
   int val;
   char str[20];
   
   strcpy(str, "98993489");
   val = ft_atoi(str);
   printf("String value = %s, Int value = %d\n", str, val);

   strcpy(str, "tutorialspoint.com");
   val = ft_atoi(str);
   printf("String value = %s, Int value = %d\n", str, val);

   
    return(0);
}