#include <stdio.h>
#include <string.h>


typedef struct
{
  int Year, Month, Day;
} DATE;

typedef struct
{
  char Surname[30], Name[15];
  DATE Birthday;
  char Phone[20];
  char Sex;
  int Form;
  char FormDigit;
} PUPIL;

void Swap( PUPIL *A, PUPIL *B )
{
  PUPIL tmp = *A;
  *A = *B;
  *B = tmp;
}

int SaveDB(char *Filename, PUPIL *Base, int n)
{
  FILE *F;

  F = fopen(Filename, "wb");
  if (F == NULL)
	return 0;
  fwrite(Base, sizeof(PUPIL), n, F);
  fclose(F);
  return 1;
}

int LoadDB(char *FileName, PUPIL *Base, int MaxSize)
{
  FILE *F;
  int n;

  if ((F = fopen(FileName, "rb")) == NULL)
	return 0;
  n = fread(Base, sizeof(PUPIL), MaxSize, F);
  fclose(F);
  return n;
}


void GetStr( char * Str, int MaxLen )
{
  int i = 0;
  char ch;

  while ((ch = getchar()) != '\n')
	if (Str != NULL && i < MaxLen - 1)
	  Str[i++] = ch;
  if (Str != NULL && i < MaxLen)
	Str[i] = 0;
}

int moreA( PUPIL a, PUPIL b )
{
  char s1[46], s2[46];
  strcpy(s1, a.Surname);
  strcat(s1, " ");
  strcat(s1, a.Name);

  strcpy(s2, b.Surname);
  strcat(s2, " ");
  strcat(s2, b.Name);

  return strcmp(s1, s2) > 0;
}

int moreDate(DATE a, DATE b)
{
  if (a.Year == b.Year)
	if (a.Month == b.Month)
	  return a.Day > b.Day;
	else
	  return a.Month > b.Month;
  else
	return a.Year < b.Year;
}

int moreB(PUPIL a, PUPIL b)
{
  return moreDate(a.Birthday, b.Birthday);
}

void InsertionSortA( PUPIL *mas, int size )
{
  int i, j;
  PUPIL x;

  for (i = 0; i < size; i++)
  {
	x = mas[i];
	j = i - 1;
	while (j >= 0 && moreA(mas[j], x))
	  mas[j + 1] = mas[j], j--;
	mas[j + 1] = x;
  }
}

void InsertionSortB( PUPIL *mas, int size )
{
  int i, j;
  PUPIL x;

  for (i = 0; i < size; i++)
  {
	x = mas[i];
	j = i - 1;
	while (j >= 0 && moreB(mas[j], x))
	  mas[j + 1] = mas[j], j--;
	mas[j + 1] = x;
  }
}

void Reverse( PUPIL *mas, int size )
{
  for (int i = 0; i < size / 2; ++i)
	Swap(&mas[0], &mas[size - i - 1]);
}

#define MAX 50

int main( void )
{
  int DBSize = 0, run = 1, x;
  char FileName[100];
  PUPIL p;
  static PUPIL DB[MAX];

  while (run)
  {
	printf("...\n");
	switch (getchar())
	{
	case '0':
	  run = 0;
	  break;
	case '1':
	  // input: information for pupil
	  // Здесь считать данные в переменную p
	  DB[DBSize] = p;
	  DBSize++;
	  break;
	case '2':
	  // input: number of pupil to be deleted
	  // Здесь считать данные в переменную x
	  for (int i = x; i < DBSize - 1; ++i)
	  {
		DB[i] = DB[i + 1];
	  }
	  DBSize--;
	  break;
	case '3':
	  for (int i = 0; i < DBSize; ++i)
	  {
		// Вывести DB[i]
	  }
	  break;
	case '4':
	  if (getchar() == 'a')
		InsertionSortA(DB, DBSize);
	  else
		InsertionSortB(DB, DBSize);
	  break;
	case '5':
	  Reverse(DB, DBSize);
	  break;
	case '6':
	  printf("file name:");
	  GetStr(FileName, 100);
	  if (SaveDB(FileName, DB, DBSize))
		printf("success");
	  else
		printf("fail");
	  break;
	case '7':
	  printf("file name:");
	  GetStr(FileName, 100);
	  DBSize = LoadDB(FileName, DB, MAX);
	  break;
	default:
	  printf("...\n");
	}
  }
  return 0;
}