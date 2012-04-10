#include <stdio.h>
#include "./Headers/lyrics_processing.h"

int get_song_info(char* artist, char* title)
{
    artist[40] = 0;
    title[40] = 0;
    printf("Enter the artist of wanted song (up to 40 characters):\n");
    gets(artist);
    if (0 == artist)
    {
        printf("Artist cannot be blank.\n");
        return 1;
    }
    if (0 != artist[40])
    {
        printf("Too many characters. Terminating.\n");
        return 2;
    }
    printf("Enter the title of wanted song (up to 40 characters):\n");
    gets(title);
    if (0 == title)
    {
        printf("Title cannot be blank.\n");
        return 1;
    }
    if (0 != title[40])
    {
        printf("Too many characters. Terminating.\n");
        return 2;
    }
    return 0;
}