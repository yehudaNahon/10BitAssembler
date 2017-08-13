#include "Node.h"
#include "Memory.h"

void Node_Init(Node* node, void* data)
{
    node->data = data;
    node->next = NULL;
}

void* Node_GetData(Node* node)
{
    return node? node->data : NULL;
}

void* Node_SetData(Node* node, void* data)
{
    node->data = data;
    return data;
}

Node* Node_Next(Node* node)
{
    return node? node->next : NULL;
}

bool Node_SetNext(Node* node, Node* child)
{
    if(node)
    {
        node->next = child;
    } 

    return true;
}

void Node_Delete(Node* node,void (*FreeResource)(void*))
{
    /* delete nodes data using a user provided function for ceaning up*/
    if(node->data)
    {
        FreeResource(node->data);
        Memory_Delete(node->data);
        node->data = NULL;
    }
    /*signal to child to clean and reset it*/
    if(node->next)
    {
        Node_Delete(node->next, FreeResource);
        Memory_Delete(node->next);
        node->next = NULL;
    }
}

