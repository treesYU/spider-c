/**********************************************************************
 *  Descripttion: 
 *  version: 
 *  Author: trees.yu
 *  Date: 2020-01-06 07:47:28
 *  LastEditors: trees.yu
 *  LastEditTime: 2020-01-14 00:15:16
 **********************************************************************/
#ifndef _MY_HTTPS_H
#define _MY_HTTPS_H 

#define MY_HTTPS_DEFAULT_PORT 8080 

char *http_get(const char *url, FILE *fp);
char *http_post(const char *url, const char * post_str); 

typedef struct Module_https
{
    int version;
    int minor_version;
    char *(*get)(const char *url, FILE *fp);
    char *(*post)(const char *url, const char * post_str);
} ModuleHttps;

#endif // _MY_HTTPS_H
