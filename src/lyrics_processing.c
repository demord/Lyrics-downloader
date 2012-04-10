#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./Headers/lyrics_processing.h"
#include "./Headers/connection.h"
#include "./Headers/user_interface.h"

#define AZ_BUFFER 450

int az_lyrics()
{
    char artist[41], title[41], *url, *filename;
    int check;
    do
    {
        check = get_song_info(artist, title);
        if (2 == check)
        {
            fflush(0);
            return 1;
            
        }
    }
    while (0 != check);
    filename = (char*) malloc ((80 + 20) * sizeof(char));
    strcpy(filename, "./lyrics/");
    strcat(filename, artist);
    strcat(filename, "-");
    strcat(filename, title);
    strcat(filename, "-azlyrics");
    url = get_az_lyrics_url(artist, title);
    download_html(url, filename);
    filename = extract_az_lyrics(filename);
    remove_html(filename);
    return 0;
}

char* get_az_lyrics_url(char* artist, char* title)
{
    int pos_c;
    char* url;
    pos_c = remove_space_signs(artist);
    pos_c += remove_space_signs(title);
    url = (char*) malloc ((38 + pos_c) * sizeof(char));
    strcpy(url, "http://www.azlyrics.com/lyrics/");
    strcat(url, artist);
    strcat(url, "/");
    strcat(url, title);
    strcat(url, ".html");
    printf("%s\n", url);
    return url;
}

int remove_space_signs(char* string)
{
    int pos = 0;
    int i;
    while (0 != string[pos])
    {
        if ((' ' == string[pos]) || ('_' == string[pos]))
        {
            for (i = pos + 1; 0 != string[i - 1]; i++)
            {
                string[i - 1] = string[i];
            }
        }
        else pos++;
    }
    return pos;
}

char* extract_az_lyrics(char* source_file)
{
    FILE *imput, *output;
    char buffer[AZ_BUFFER + 1];
    char *destination_file, *start_str, *end_str;
    int recording_state = 0;
    
    start_str = (char*) malloc (25 * sizeof(char));
    strcpy(start_str, "<!-- start of lyrics -->");
    end_str = (char*) malloc (23 * sizeof(char));
    strcpy(end_str, "<!-- end of lyrics -->");
    destination_file = (char*) malloc (4 * sizeof(char) + sizeof(source_file));
    strcpy(destination_file, source_file);
    strcat(destination_file, ".txt");
    imput = fopen(source_file, "r");
    output = fopen(destination_file, "w");
    while (0 != fgets(buffer, AZ_BUFFER, imput))
    {
        if (0 == recording_state)
        {
            if (0 == strncmp(buffer, start_str, 24))  recording_state = 1;
        }
        else
        {
            if (0 == strncmp(buffer, end_str, 22))
            {
                break;
            }
            else
            {
                fputs(buffer, output);
            }
        }
    }
    fclose(output);
    fclose(imput);
    free(start_str);
    free(end_str);
    free(source_file);
    return destination_file;
}

int remove_html(char* filename)
{
    FILE* editable_file;
    editable_file = fopen(filename, "r+");
    remove_html_br(editable_file);
    remove_multiple_spaces(editable_file);
    fclose(editable_file);
    return 0;
}

int remove_html_br(FILE* e_file)
{
    rewind(e_file);
    char buffer[121];
    char* to_replace;
    fpos_t locked_pos;
    fgetpos(e_file, &locked_pos);
    while (0 != fgets(buffer, 120, e_file))
    {
        to_replace = strstr(buffer, "<br>");
        if (0 != to_replace)
        {
            strncpy(to_replace, "    ", 4);
            fsetpos(e_file, &locked_pos);
            fputs(buffer, e_file);
            fsetpos(e_file, &locked_pos);
        }
        fgetpos(e_file, &locked_pos);
    }
    return 0;
}

int remove_multiple_spaces(FILE* e_file)
{
    rewind(e_file);
    char buffer[121];
    int i, edited = 0;;
    fpos_t locked_pos;
    fgetpos(e_file, &locked_pos);
    while (0 != fgets(buffer, 120, e_file))  /*for each file*/
    {
        for (i = 0; 0 != buffer[i]; i++)   /*for each symbol in buffer*/
        {
            if ((32 == buffer[i]) && (32 == buffer[i + 1]))
            {
                resize_string(buffer, i);
                i--;
                edited = 1; 
            }
        }
        if (1 == edited)
        {
            fsetpos(e_file, &locked_pos);
            fputs(buffer, e_file);
            edited = 0;
            fsetpos(e_file, &locked_pos);
        }
        fgetpos(e_file, &locked_pos);
    }
    return 0;
}

int resize_string(char* string, int pos)
{
    int i;
    for (i = pos; 0 != string[i]; i++)
    {
        string[i] = string[i + 1];
    }
    return 0;
}