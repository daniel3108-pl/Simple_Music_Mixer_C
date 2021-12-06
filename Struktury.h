

#ifndef Struktury_h
#define Struktury_h



/// Struktura zwieraca parametry zwiazane ze specyfikacja naglowka pliku typu WAVE
typedef struct _AudioFile{

    unsigned char   riff[4];
    unsigned int    overall_size;
    unsigned char   wave[4];
    unsigned char   fmt_chunk_marker[4];
    unsigned int    length_of_fmt;
    unsigned short  format_type;
    unsigned short  channels;
    unsigned int    sample_rate;
    unsigned int    byterate;
    unsigned short  block_align;
    unsigned short  bits_per_sample;
    unsigned char   data_chunk_header[4];
    unsigned int    data_size;

}AudioFile;



#endif /* Struktury_h */
