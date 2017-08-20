#ifndef LOG_H
#define LOG_H

#include <stdarg.h>


#define MEMORY_ERR ("Failed Locating Memory")
#define PARAM_ERR ("Recieved incorrect parameter in function call")
typedef enum ELogType
{
    eWarning,
    eError,
    eInfo
}ELogType;

/**
    Write an error log to the stdout 

    type - a error log type will be one on the ELogType enum
    message - a null terminated ascii formated string with aditional information about the error
*/
void Log(ELogType type, const char *fmt, ...);


#endif