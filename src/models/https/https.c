#include <curl/curl.h>
#include "https.h"





char *https_post(const char *url, const char *post_str)
{
    return NULL;
}


char *https_get(const char *url)
{
    CURL *curl;
    CURLcode res;
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

    res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
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

