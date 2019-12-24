#ifndef _MY_HTTPS_H
#define _MY_HTTPS_H 

#define MY_HTTPS_DEFAULT_PORT 8080 

char *http_get(const char *url);
char *http_post(const char *url,const char * post_str); 

typedef struct Module_https
{
    int version;
    int minor_version;
    char *(*get)(const char *url);
    char *(*post)(const char *url,const char * post_str);
} ModuleHttps;

#endif // _MY_HTTPS_H
