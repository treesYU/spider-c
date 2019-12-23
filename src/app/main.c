#include <stdio.h>
#include "http.h"
#include <dlfcn.h>

#define MODULE_PATH "../lib/" 

int main()
{
    char npath[200]="../lib/libhttp.so";
    void* handle = NULL;
    if((handle = dlopen(npath, RTLD_GLOBAL|RTLD_NOW)) == NULL)
    {
         printf("Load module fail(dlopen):%s", dlerror());
    }
    printf("open so!\n");
    void* rv = NULL;
    if((rv = dlsym(handle, "httpctl")) == NULL)
    {
        printf("Load func fail(dlopen):%s", dlerror());
    }
    ModuleHttp* http = (ModuleHttp*)rv;
    printf("http version %d.%d\n",http->version,http->minor_version);
    //http->get("http:\\www.baidu.com");
    printf("%s",http->get("http://www.baidu.com")); 
    return 0;
}
