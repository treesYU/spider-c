#ifndef _MY_COMMDB_H
#define _MY_COMMDB_H 

typedef struct DbStaticInfo DbSInfo;

typedef struct Module_commdb
{
    DbSInfo* handle;
    int version;
    int minor_version;
    char *(*getDbFilename)(DbSInfo* _handle);
    int (*setDbFilename)(DbSInfo* _handle, const char * _name);
    int (*saveUrl)(DbSInfo* _handle, const char * _url, const int _type);
} ModuleCommDb;

#endif
