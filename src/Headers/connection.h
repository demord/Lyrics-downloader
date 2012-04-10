/******
 * Declares all the necessary interface to libcurl:
 *  Connects to specified server
 *  Downloads raw html file
 *  Writes it to specified file
 ******/

#ifndef CONNECTION_H
#define CONNECTION_H

int download_html(char *server, char *local_file);

#endif