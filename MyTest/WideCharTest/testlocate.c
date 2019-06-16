  #include <stdio.h>
  #include <locale.h>

  int main()
  {
    if (!setlocale(LC_ALL, "")) 
    {
      fprintf(stderr, "Can't set the specified locale! Check LANG, LC_CTYPE, LC_ALL.\n");
      return 1;
    }
    printf("%s\n", "Schöne Grüße");
    return 0;
  }
