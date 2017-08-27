#ifndef CONTAINER_H
#define CONTAINER_H


#include <stddef.h>

/*
this file contained basic definitions for all container like classes that wants to use the same basic operations
like iterators,finedrs...
*/

/*
    A finder function pointer type normaly it will be used to locate a variable in a container
    is arguments are:
                - a pointer to the data provided
                - a index of some sort of the pointer to be located
                - a pointer to a object recieved by the user of the container to give extra context to the function
    return:     true - this data meets the finder lookup and should be returned
                false - this data is not what i'm looking for move to the next one
*/
typedef bool (*Finder)(void*,size_t,void*);

/*
    A iterator function pointer this type of function normally just go throw the all container data and preform a action
    they are not expected to return any value

    there arguments are:
                - a pointer to the data
                - the datas length
                - aditional context from the user of the container
*/
typedef void (*Iterator)(void*,size_t,void*);

/*
    This is a cleaner function pointer generally used to help clean any data when preforming a realese of resources
    this is very useful when a container whants to discard of an object and is not sure if the object containes any pointer to 
    a dynamic memory that should be cleaned to 

    there aguments are:
            - a pointer to the data contained 
*/
typedef void (*Cleaner)(void*);




#endif