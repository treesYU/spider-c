/**********************************************************************
 *  Descripttion: 
 *  version: 
 *  Author: trees.yu
 *  Date: 2020-01-06 07:47:28
 *  LastEditors: trees.yu
 *  LastEditTime: 2020-01-21 09:13:51
 **********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "module.h"
#include "commdb.h"
#include "sqlite3.h"

#define DB_MAJOR_NUM 1
#define DB_MINOR_NUM 0

/* 默认定义 */
#define DB_OK           0   /* Successful result */
/* beginning-of-error-codes */
#define DB_ERROR        1   /* Generic error */

struct DbStaticInfo
{
    char name[300];
    sqlite3 *db;
};

char * get_dbfilename(DbSInfo* _handle)
{
    return _handle->name;
}

int set_dbfilename(DbSInfo* _handle, const char * _name)
{
    int resault = -1;
    if (strnlen(_name,sizeof(_handle->name))<sizeof(_handle->name))
    {
        strcpy(_handle->name,_name);
    }
    return resault;
}

int _open_db(DbSInfo* _handle)
{
    int result = DB_ERROR;
    do
    {
        if (_handle->db != NULL)
        {
            break;
        }
        int res = sqlite3_open(_handle->name, &_handle->db);
        if (res != SQLITE_OK)
        {
            break;
        }
        result = DB_OK;
    }while(0);
    return result;
}

int _close_db(DbSInfo* _handle)
{
    int result = DB_ERROR;
    do
    {
        if (_handle->db == NULL)
        {
            result = DB_OK;
            break;
        }
        int res = sqlite3_close(_handle->db);
        if (res != SQLITE_OK)
        {
            break;
        }
        result = DB_OK;
    }while(0);
    return result;
}

static int CB_sqlite_none( void *data, int argc, char **argv, char **pszColName) 
{
    return 0;
}

static int CB_sqlite_count( void *data, int argc, char **argv, char **pszColName) 
{
    *((int *)data) = atoi(argv[0]);
    return 0;
}

int _checktable(DbSInfo* _handle,int _key)
{
    int result = DB_ERROR;
    char *zErrMsg = 0;
    int res = 0;
    int count = -1;
    do
    {
        {
            char sqlcmd[300] = {0};
            snprintf(sqlcmd,sizeof(sqlcmd),"SELECT COUNT(*) FROM sqlite_master where type='table' and name='T_html_pools';");
            res = sqlite3_exec(_handle->db, sqlcmd, CB_sqlite_count, &count, &zErrMsg);
            if (res != SQLITE_OK)
            {
                break;
            }
        }
        if (count == 0)
        { // 无表，创建
            char sqlcmd[300] = {0};
            snprintf(sqlcmd,sizeof(sqlcmd),"CREATE TABLE T_html_pools(serial INTEGER PRIMARY KEY AUTOINCREMENT,url TEXT NOT NULL, status INT NOT NULL);");
            res = sqlite3_exec(_handle->db, sqlcmd, CB_sqlite_none, NULL, &zErrMsg);
            if (res != SQLITE_OK)
            {
                break;
            }
        }
        result = DB_OK;
    }while(0);
    return result;
}

int _insert_url(DbSInfo* _handle,const char * _url,const int _type)
{
    int result = DB_ERROR;
    char *zErrMsg = 0;
    int res = 0;
    int count = -1;
    do
    {
        {
            char sqlcmd[300] = {0};
            snprintf(sqlcmd,sizeof(sqlcmd),"SELECT COUNT(*) FROM T_html_pools where url='%s';", _url);
            res = sqlite3_exec(_handle->db, sqlcmd, CB_sqlite_count, &count, &zErrMsg);
            if (res != SQLITE_OK)
            {
                break;
            }
        }
        if (count == 0)
        { // 无相同，插入
            char sqlcmd[300] = {0};
            snprintf(sqlcmd,sizeof(sqlcmd),"INSERT INTO T_html_pools(url,status) VALUES('%s',%d);",
                _url, _type);
            res = sqlite3_exec(_handle->db, sqlcmd, CB_sqlite_none, NULL, &zErrMsg);
            if (res != SQLITE_OK)
            {
                break;
            }
        }
        result = DB_OK;
    }while(0);
    return result;
}

int save_Html(DbSInfo* _handle, const char * _url, const int _type)
{
    int result = DB_ERROR;
    do
    {
        if (_open_db(_handle))
        {
            break;
        }
        /* 建表 */
        _checktable(_handle,0);
        /* 插项 */
        _insert_url(_handle, _url, _type);
        if (_close_db(_handle))
        {
            break;
        }
        result = DB_OK;
    }while(0);
    return result;
}

/* 外部调用 */

int module_init(struct Module *modctl)
{
    int res = MODULE_OK;
    do
    {
        /* 保证兼容性 应直接使用常数 调试阶段暂时使用sizeof */
        if (sizeof(ModuleCommDb) != modctl->handlecheck)
        {
            res = MODULE_ERR;
            break;
        }
        /* 申请 */
        void *pbuffer = malloc(sizeof(ModuleCommDb) + sizeof(DbSInfo));
        if (pbuffer == NULL)
        {
            res = MODULE_ERR;
            break;
        }
        memset(pbuffer,0x00,sizeof(ModuleCommDb) + sizeof(DbSInfo));
        ModuleCommDb * pComm = pbuffer;
        DbSInfo * pStatic = pbuffer + sizeof(ModuleCommDb);
        
        /* 接口加载 */
        pComm->handle = pStatic;
        pComm->getDbFilename = get_dbfilename;
        pComm->setDbFilename = set_dbfilename;
        pComm->saveUrl = save_Html;
        
        /* 数据初始化 */
        strncpy(pStatic->name,"./default.db3",sizeof(pStatic->name));

        modctl->handle = pComm;
    }while(0);
    return res;
}


int module_release(struct Module *modctl)
{
    return 0;
}
Module moduleCtl = {
    .version        = DB_MAJOR_NUM,
    .minor_version  = DB_MINOR_NUM,
    .name           = "basedb",
    .init           = module_init,
    .release        = module_release,
    .handlecheck    = sizeof(ModuleCommDb),
    .handle         = NULL
};


