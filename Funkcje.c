
//#include "memorilo.h"
#include "Funkcje.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "Struktury.h"

#define HEADER_SIZE 44


AudioFile czytajHeader(char *plikName)
{

    printf("Wczytywanie zawartosci Wave...\n");
    AudioFile wavFile;

    FILE *plik = fopen(plikName, "rb");
    if (!plik)
    {
        printf("Nie mozna wczytac plikow!\n");
        usleep(1000);
        fclose(plik);
        exit(1);
    }
    unsigned char buffer[4];
    unsigned char buffer2[2];

    fread(wavFile.riff, sizeof(wavFile.riff), 1, plik);

    fread(buffer, sizeof(buffer), 1, plik);
    wavFile.overall_size = buffer[0] |
                           (buffer[1] << 8) |
                           (buffer[2] << 16) |
                           (buffer[3] << 24);

    fread(wavFile.wave, sizeof(wavFile.wave), 1, plik);

    fread(wavFile.fmt_chunk_marker, sizeof(wavFile.fmt_chunk_marker), 1, plik);

    fread(buffer, sizeof(buffer), 1, plik);
    wavFile.length_of_fmt = buffer[0] |
                            (buffer[1] << 8) |
                            (buffer[2] << 16) |
                            (buffer[3] << 24);

    fread(buffer2, sizeof(buffer2), 1, plik);
    wavFile.format_type = buffer2[0] | (buffer2[1] << 8);

    fread(buffer2, sizeof(buffer2), 1, plik);
    wavFile.channels = buffer2[0] | (buffer2[1] << 8);

    fread(buffer, sizeof(buffer), 1, plik);
    wavFile.sample_rate = buffer[0] |
                          (buffer[1] << 8) |
                          (buffer[2] << 16) |
                          (buffer[3] << 24);

    fread(buffer, sizeof(buffer), 1, plik);
    wavFile.byterate = buffer[0] |
                       (buffer[1] << 8) |
                       (buffer[2] << 16) |
                       (buffer[3] << 24);

    fread(buffer2, sizeof(buffer2), 1, plik);
    wavFile.block_align = buffer2[0] | (buffer2[1] << 8);

    fread(buffer2, sizeof(buffer2), 1, plik);
    wavFile.bits_per_sample = buffer2[0] | (buffer2[1] << 8);

    fread(wavFile.data_chunk_header, sizeof(wavFile.data_chunk_header), 1, plik);

    fread(buffer, sizeof(buffer), 1, plik);
    wavFile.data_size = buffer[0] |
                        (buffer[1] << 8) |
                        (buffer[2] << 16) |
                        (buffer[3] << 24);

    fclose(plik);

    return wavFile;
}

bool isHeaderSimilar(char *f1, char *f2)
{
    AudioFile Header1 = czytajHeader(f1);
    AudioFile Header2 = czytajHeader(f2);

    if (Header1.sample_rate != Header2.sample_rate || Header1.channels != Header2.channels || Header1.bits_per_sample != Header2.bits_per_sample)
        return false;
    else
        return true;
}

unsigned char *wczytajPlik(char *name_Plik)
{

    printf("Wczytywanie drugiego pliku...\n");

    FILE *plik = fopen(name_Plik, "rb");
    unsigned char *buffor1;
    AudioFile plik2Header = czytajHeader(name_Plik);

    if (!plik)
    {
        printf("Nie mozna wczytac plikow!\n");
        fclose(plik);
        usleep(1000);
        return 0;
    }

    fseek(plik, HEADER_SIZE, SEEK_SET);
    size_t sizeHeader = ftell(plik);
    fseek(plik, 0, SEEK_END);
    size_t size = ftell(plik) - sizeHeader;
    fseek(plik, HEADER_SIZE, SEEK_SET);

    buffor1 = (unsigned char *)malloc(size);

    if (fread(buffor1, sizeof *buffor1, size, plik) != size)
    {
        printf("Nie mozna wczytac plikow!\n");
        fclose(plik);
        usleep(1000);
        return 0;
    }
    else
    {
        fclose(plik);
        return buffor1;
    }
}
size_t f_size(char *f_name)
{
    FILE *f = fopen(f_name, "rb");
    if (f)
    {
        fseek(f, 0, SEEK_END);
        size_t size = ftell(f);
        fseek(f, 0, SEEK_SET);
        fclose(f);
        return size;
    }
    else
    {
        size_t size = 0;
        printf("Nie udalo sie obliczyc rozmiaru pliku!");
        usleep(1000);
        fclose(f);
        return 0;
    }
}

unsigned char *copyPCM(unsigned char *PCM, int length, int roznica)
{

    unsigned char* copiedPCM;
    copiedPCM = (unsigned char *)malloc(length + roznica);
    for (int i = 0; i < length; i++)
    {
        copiedPCM[i] += PCM[i];
    }

    return copiedPCM;
}
int write_size(AudioFile plik1, AudioFile plik2, float poz)
{
    int num_samples_f1 = (8 * plik1.data_size) / (plik1.channels * plik1.bits_per_sample) * 2;
    int num_samples_f2 = (8 * plik2.data_size) / (plik2.channels * plik2.bits_per_sample) * 2;
    int roznica_samples = num_samples_f1 - ((1 - poz) * num_samples_f2);
    return num_samples_f1 + roznica_samples;
}
unsigned char *mixujWav(AudioFile *plik1, AudioFile plik2, float wspol, unsigned char *PCM1, unsigned char *PCM2, float poz)
{
    
    int num_samples_f1 = (8 * plik1->data_size) / (plik1->channels * plik1->bits_per_sample) * 2;
    int num_samples_f2 = (8 * plik2.data_size) / (plik2.channels * plik2.bits_per_sample) * 2;
    int roznica_samples = num_samples_f1 - ((1 - poz) * num_samples_f2);
    unsigned char *zmiksowaneAudio = copyPCM(PCM1, num_samples_f1, roznica_samples);
    plik1->data_size *= 2;
    plik1->overall_size *= 2;

    int starting_point = 0;
    int i = 0;

    for (starting_point = 0 + (num_samples_f1 * poz); starting_point < num_samples_f1 + roznica_samples && i < num_samples_f2; starting_point++)
    {
        if (starting_point < num_samples_f1)
        {
            zmiksowaneAudio[starting_point] = (wspol * PCM1[starting_point] + ((1 - wspol) * PCM2[i])) / wspol;
        }
        else
            zmiksowaneAudio[starting_point] += PCM2[i];
        i++;
    }
    printf("plik zostal pomyslnie zmiksowany!\n");
    return zmiksowaneAudio;
}

void generate_Wav(char *fout_name, char *f_name, char *f2_name, float wspol, float poz)
{

    AudioFile plik1Header = czytajHeader(f_name);
    AudioFile plik2Header = czytajHeader(f2_name);
    unsigned char *buffer = wczytajPlik(f_name);
    unsigned char *buffer2 = wczytajPlik(f2_name);
    int write_sz = write_size(plik1Header, plik2Header, poz);
    // printf("\nWrite size = %d\n", write_sz);
    unsigned char *zmiksowaneAudio = mixujWav(&plik1Header, plik2Header, wspol, buffer, buffer2, poz);

    FILE *wav_New = fopen(fout_name, "wb");
    if (wav_New)
    {
        fwrite("RIFF", sizeof(unsigned char), 4, wav_New);
        fwrite(&plik1Header.overall_size, sizeof(unsigned int), 1, wav_New);
        fwrite("WAVE", sizeof(unsigned char), 4, wav_New);
        fwrite("fmt ", sizeof(unsigned char), 4, wav_New);
        fwrite(&plik1Header.length_of_fmt, sizeof(unsigned int), 1, wav_New);
        fwrite(&plik1Header.format_type, sizeof(unsigned short), 1, wav_New);
        fwrite(&plik1Header.channels, sizeof(unsigned short), 1, wav_New);
        fwrite(&plik1Header.sample_rate, sizeof(unsigned int), 1, wav_New);
        fwrite(&plik1Header.byterate, sizeof(unsigned int), 1, wav_New);
        fwrite(&plik1Header.block_align, sizeof(unsigned short), 1, wav_New);
        fwrite(&plik1Header.bits_per_sample, sizeof(unsigned short), 1, wav_New);
        fwrite("data", sizeof(unsigned char), 4, wav_New);
        fwrite(&plik1Header.data_size, sizeof(unsigned int), 1, wav_New);
        //fwrite(zmiksowaneAudio, sizeof *zmiksowaneAudio, write_sz, wav_New); // dziala tak samo jak petla ponizej

        for (int k = 0; k < write_sz; ++k)
        {
            int n = fwrite(zmiksowaneAudio + k, 1, 1, wav_New);
            if (n != 1)
            {
                int a = 5;
            }
        }
        
        fclose(wav_New);
        printf("Plik utworzono!");
    }
    else
    {
        printf("Nie udalo sie utworzyc pliku! ");
        usleep(1000);
        return;
    }

    free(buffer);
    free(buffer2);
    free(zmiksowaneAudio);
}
