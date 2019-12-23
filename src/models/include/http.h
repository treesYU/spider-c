#ifndef _MY_HTTP_H
#define _MY_HTTP_H 

#define MY_HTTP_DEFAULT_PORT 80 

char *http_get(const char *url);
char *http_post(const char *url,const char * post_str); 

typedef struct Module_http
{
    int version;
    int minor_version;
    char *(*get)(const char *url);
    char *(*post)(const char *url,const char * post_str);
} ModuleHttp;

#endif
