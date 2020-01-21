/**********************************************************************
 *  Descripttion: 
 *  version: 
 *  Author: trees.yu
 *  Date: 2020-01-06 07:47:28
 *  LastEditors: trees.yu
 *  LastEditTime: 2020-01-14 00:15:00
 **********************************************************************/
#include <curl/curl.h>
#include "module.h"
#include "https.h"

#define MAJOR_NUM 1
#define MINOR_NUM 0

size_t process_data(void *buffer, size_t size, size_t nmemb, void *user_p)
{
    FILE *fp = (FILE *)user_p;
    size_t return_size = fwrite(buffer, size, nmemb, fp);
    return return_size;
}


/**********************************************************************
 *  name    : 
 *  describe: 
 *  input   : 
 *  output  : 
 *  return  : 
 *  editlogs: 
 **********************************************************************/
char *https_post(const char *url, const char *post_str)
{
    return NULL;
}


/**********************************************************************
 *  name    : 
 *  describe: 
 *  input   : 
 *  output  : 
 *  return  : 
 *  editlogs: 
 **********************************************************************/
char *https_get(const char *url, FILE *fp)
{
    CURL *curl;
    CURLcode return_code;
    curl = curl_easy_init();
    if (!curl)
    {
        return NULL;
    }

    /*设置easy handle属性*/
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 60L);
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 10L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &process_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

    return_code = curl_easy_perform(curl);
    if (return_code != CURLE_OK)
    {
        fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(return_code));
    }
    
    curl_easy_cleanup(curl);
    return NULL;
}

ModuleHttps httpsctl = {
    .version = 1,
    .minor_version = 2,
    .get = https_get,
    .post = https_post
};

int module_init(struct Module *modctl)
{
    int res = MODULE_OK;
    do
    {
        if (sizeof(ModuleHttps) != modctl->handlecheck)
        {
            res = MODULE_ERR;
            break;
        }
        modctl->handle = (void*)&httpsctl;
    }while(0);
    return res;
}

Module moduleCtl = {
    .version        = MAJOR_NUM,
    .minor_version  = MINOR_NUM,
    .name           = NULL,
    .init           = module_init,
    .handlecheck    = sizeof(ModuleHttps),
    .handle         = NULL
};
