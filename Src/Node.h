#ifndef NODE_H
#define NODE_H

#include <stddef.h>
#include <stdbool.h>


typedef struct Node
{
    void* data;
    struct Node* next;    
}Node;

void Node_Init(Node* node, void* data);

void* Node_GetData(Node* node);

void* Node_SetData(Node* node, void* data);

Node* Node_Next(Node* node);

bool Node_SetNext(Node* node, Node* child);

void Node_Delete(Node* node, void (*FreeResource)(void*));



#endif