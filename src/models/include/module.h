/**********************************************************************
 *  Descripttion: 
 *  version: 
 *  Author: trees.yu
 *  Date: 2020-01-06 07:47:28
 *  LastEditors: trees.yu
 *  LastEditTime: 2020-01-06 08:43:50
 **********************************************************************/
#ifndef __MODULE_H_
#define __MODULE_H_

#define MODULE_OK 0
#define MODULE_ERR 1

typedef struct Module
{
    int version; 
    int minor_version;

    const char *name;

    int (*init)(struct Module *);
    int (*release)(struct Module *);
    unsigned int handlecheck;
    void *handle;
} Module;


#endif // __MODULE_H_
