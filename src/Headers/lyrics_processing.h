/***********************
 * Interacts with connection in order to download lyrics
 * Cuts out unnecessary information from each html
 * Modifies lyrics to neat format
 ***********************/

#ifndef LYRICS_PROCESSING_H
#define LYRICS_PROCESSING_H

#include <stdio.h>

int az_lyrics();
char* get_az_lyrics_url(char* artist, char* title);
char* extract_az_lyrics(char* filename);    /*returns final filename*/

int remove_html(char* filename);
int remove_html_br(FILE* handle);
int remove_multiple_spaces(FILE* handle);
int remove_space_signs(char* string);

int resize_string(char* string, int pos);

#endif