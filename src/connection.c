#include <stdio.h>
#include <curl/curl.h> 
#include "./Headers/connection.h"

int download_html(char *server, char *local_file)
{
    FILE* write_to;
    CURL* curl_handle;
    CURLcode is_success;
    curl_handle = curl_easy_init();
    if (0 != curl_handle)
    {
        write_to = fopen(local_file, "w");
        curl_easy_setopt(curl_handle, CURLOPT_URL, server);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, write_to);
        is_success = curl_easy_perform(curl_handle);
        curl_easy_cleanup(curl_handle);
        fclose(write_to);
        if (0 != is_success)
        {
            printf("\nCurl perform failure.\n");
            return 1;
        }
        return 0;
    }
    else
    {
        printf("\nCurl init failure.\n");
        return 1;
    }
}