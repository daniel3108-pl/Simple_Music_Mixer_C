
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <unistd.h>

//#include "memorilo.h"
#include "Funkcje.h"
#include "Struktury.h"

int main(int argc, char *argv[])
{

  // -w -> arg wspolczynnika || -p -> arg pozycji miksowania || -o nazwa pliku wyjsciowego //
  // np. Test.wav Test2.wav -o nowy.wav -x 0.5 -p 0.5

  int kolejnosc;
  char *Plik1 = "Test1.wav";
  char *Plik2 = "Test2.wav";
  char *out = "TestOut.wav";
  float wspo = 0.5;
  float poz = 0.5;

  for (int i = 1; i + 1 <= argc; i++)
  {
    if (argv[i][0] == '-')
    {
      switch (argv[i][1])
      {
      case 'w':
        wspo = atof(argv[i + 1]);
        i++;
        break;
      case 'p':
        poz = atof(argv[i + 1]);
        i++;
        break;
      case 'o':
        out = argv[i + 1];
        i++;
        break;
      default:
        break;
      }
    }
    else
    {
      switch (kolejnosc)
      {
      case 0:
        Plik1 = argv[i];
        kolejnosc = 1;
        break;
      case 1:
        Plik2 = argv[i];
        kolejnosc = 2;
        break;
      case 2:
        break;
      default:
        break;
      }
    }
  }
  if (strstr(Plik1, ".wav") == NULL || strstr(Plik2, ".wav") == NULL || strstr(out, ".wav") == NULL)
  {
    printf("Podano bledne rozszerzenia plikow!");
    return 0;
  }
  else
  {
    if (isHeaderSimilar(Plik1, Plik2))
    {
      if (wspo <= 1 && wspo >= 0 && poz <= 1 && poz >= 0)
      {
        generate_Wav(out, Plik1, Plik2, wspo, poz);
        //__print_report();
      }
      else
      {
        printf("Blednie podana wartosc miksowania!");
        return 0;
      }
    }
    else
    {
      printf("Pliki o roznej specyfikacji!");
      return 0;
    }
  }
  return 0;
}