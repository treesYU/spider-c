#include <stdio.h>
#include "https.h"
#include <dlfcn.h>
#include <regex.h>
#include <string.h>
#include "module.h"
#include "commdb.h"
#define MODULE_PATH "../lib/" 

int main(int argc,char *argv[])
{
   /* {
        char npath[200]="../lib/libhttps.so";
        void* handle = NULL;
        if((handle = dlopen(npath, RTLD_GLOBAL|RTLD_NOW)) == NULL)
        {
             printf("Load module fail(dlopen):%s", dlerror());
        }
        printf("open so!\n");
        void* rv = NULL;
        if((rv = dlsym(handle, "httpsctl")) == NULL)
        {
            printf("Load func fail(dlopen):%s", dlerror());
        }
        ModuleHttps* https = (ModuleHttps*)rv;
        printf("http version %d.%d\n",https->version,https->minor_version);
    }*/
    {
        char npath[200]="../lib/libcommdb.so";
        void* handle = NULL;
        if((handle = dlopen(npath, RTLD_GLOBAL|RTLD_NOW)) == NULL)
        {
             printf("Load module fail(dlopen):%s", dlerror());
        }
        printf("open so!\n");
        void* rv = NULL;
        if((rv = dlsym(handle, "moduleCtl")) == NULL)
        {
            printf("Load func fail(dlopen):%s", dlerror());
        }
        Module* pModctl = (Module*)rv;
        printf("Load lib %s\n",pModctl->name);
        printf("lib version %d.%d\n",pModctl->version,pModctl->minor_version);
        int res = pModctl->init(pModctl);
        if (res != MODULE_OK)
        {
            printf("Load lib error");
        }
	ModuleCommDb * dbctl = pModctl->handle;

        printf("default db: %s\n",dbctl->getDbFilename(dbctl->handle));
        dbctl->setDbFilename(dbctl->handle,"./test.db3");
        printf("default db: %s\n",dbctl->getDbFilename(dbctl->handle));
        dbctl->saveUrl(dbctl->handle,"https://www.baidu.com",1);
    }
    return 0;
    {
        FILE *fp = fopen("data.html", "r");
        char buffer[999999] = {0};
        int res = fread(buffer, 1, sizeof(buffer), fp);
        printf(" %d Byte is read!",res);
        const char *regex = "[a-zA-z]+://[^']+";
        regex_t preg;
        const size_t nmatch = 10;
        regmatch_t pm[nmatch];
        res = regcomp(&preg, regex, REG_EXTENDED);
        printf("comp res = %d\n",res);
        int z = regexec(&preg, buffer, nmatch, pm, 0);
        if (z == REG_NOMATCH)
        {
            printf("REG_NOMATCH\n");
            return 0;
        }
        else
        {
            int x=0;
            for (x = 0; x < nmatch && pm[x].rm_so != -1; ++ x)
            {
                char https[300] = {0};
                memcpy(https,buffer+pm[x].rm_so,pm[x].rm_eo-pm[x].rm_so);
                printf("  '%s'\n", https);
            }
        }
        printf("\n");
        
    }


    return 0;
}
