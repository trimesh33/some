#include <stdio.h>
#include <string.h> 
#include <ctype.h>


int NumOfWords( char *str )
{
  int i, cnt = 0;
  char prev = ' ';

  for (i = 0; str[i] != 0; prev = str[i], i++)
	if (!isspace(str[i]) && isspace(prev))
	  cnt++;
  return cnt;
}

int IsSym( char *str )
{
  int i = 0, j = 0;

  while (str[j] != 0 && !isspace(str[j]))
	j++;
  j--;
  while (i <= j)
  {
	if (str[i] != str[j])
	  return 0;
	i++;
	j--;
  }
  return 1;
}

int SymWordCnt( char *str )
{
  int i, cnt = 0;
  char prev = ' ';

  for (i = 0; str[i] != 0; i++)
  {
	if (!isspace(str[i]) && isspace(prev))
	  if (IsSym(&str[i]))
		cnt++;
	prev = str[i];
  }
  return cnt;
}

int CntNumber(char *str)
{
  int i, sum = 0;
  char prev = ' ';

  for (i = 0; str[i] != 0; i++)
  {
	int n = 0;

	if (!isspace(str[i]) && isspace(prev))
	{
	  while (str[i] != 0 && !isspace(str[i]))
	  {
		if (isdigit(str[i]))
		  n *= 10, n += str[i] - '0';
		i++;
	  }
	  sum += n;
	  i--;
	}
	prev = str[i];
  }
  return sum;
}


int main( void )
{
  char str[] = " hjjbj4dffg7nfnne dj.e.l[3rgr3erf,r .frpop09er..8";
  printf("%i", CntNumber(str));
  while (1);
  return 0;
}