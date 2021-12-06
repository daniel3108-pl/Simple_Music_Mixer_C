/**&File*/

#ifndef Funkcje_h
#define Funkcje_h

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <unistd.h>

#include "Struktury.h"
//#include "memorilo.h"



/**
  Funkcja sprawdzajaca czy naglowki plikow WAVE maja ta sama ilosc kanalow i takie same probkowanie
 @param f1 sciezka pierwszego pliku wejsciowego
 @param f2 sciezka drugiego pliku wejsciowego
 */
bool isHeaderSimilar(char* f1, char* f2);

/**
  Funkcja nakadajaca na siebie, od wybranego przez usera momentu, dwa pliki wejsciowe WAVE generujac tablice unsigned char zawierajaca dane dziwiekowe po zmiksowaniu
 @param plik1 naglowek pierwszego pliku wejsciowego WAVE
 @param plik2 naglowek drugiego pliku wejsciowego WAVE 
 @param wspol miejsce od ktorego zaczyna sie nakladanie
 @param PCM1 dane probek dzwieku pierwszego pliku wejsciowego
 @param PCM2 dane probek dziweku drugiego pliku wejsciowego
 @param poz pozycja, od ktorej bedzie nakladany plik2 na plik1
 */
unsigned char* mixujWav(AudioFile* plik1, AudioFile plik2, float wspol, unsigned char* PCM1, unsigned char* PCM2, float poz);

/**
  Funkcja wczytujaca danie probek dziwego do tablicy unsigned char* pobranej z pliku wejsciowego
  @param name_Plik sciezka wczytywanego pliku
 */
unsigned char* wczytajPlik(char* name_Plik);

/**
  Funkcja wczytujaca do zmiennej struct AudioFile zawartosc naglowku pliku wejsciowego WAVE
  @param sciezka dostepu do pliku wejsciowego WAVE
 
 */
AudioFile czytajHeader(char* plikName);

/**
  Funkcja obliczajaca rozmiar pliku
 @param f_name nazwa pliku do obliczenia rozmiaru
 */
size_t f_size(char* f_name);

/**
  Funkcja generujaca koncowy plik WAVE po wczesniejszym zmiksowaniu go.
 @param fout_name nazwa pliku wyjsciowego
 @param f_file sciezka pierwszego pliku wejsciowego
 @param f2_name sciezka drugiego pliku wejsciowego
 @param wspolczynnik wartosc mixowania
 @param pozycja pozycja, od ktorej będzie nakładany drugi plik
 */
void generate_Wav(char* fout_name, char* f_file, char* f2_name, float wspolczynnik, float pozycja);

/**
  Funkcja kopiujaca do tablicy unsigned char, dane probek pliku wejsciowego
 @param PCM buffer zawierajacy probki dzwieku
 @param lenght ilosc probek
 @param roznica roznica ilosci probek miedzy pierwszym a drugim plikiem wejsciowym
 */
unsigned char* copyPCM(unsigned char* PCM, int length, int roznica);

/**
 Funkcja obliczająca rozmiar wszystkich zmiksowanych probek zapisywanych do nowego pliku
 @param plik1 nagłowek pierwszego pliku wave
 @param plik2 naglowek drugiego pliku wave 
 @param poz pozycja od, ktorej bedzie miksowany plik
  
 
 */
int write_size(AudioFile plik1, AudioFile plik2, float poz);

#endif /* Funkcje_h */
