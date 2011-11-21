#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "stack.h"

void Stack_init(Stack *s, unsigned int initial_capacity)
{
    s->index = -1;
    s->capacity = initial_capacity;
    s->data = (void**)malloc(initial_capacity * sizeof(void*));
}

void Stack_push(Stack *s, void *item)
{
    if (++(s->index) + 1 == s->capacity)
    {
        Stack_grow(s);
    }
    s->data[s->index] = item;
}

#ifndef NDEBUG
void *Stack_pop(Stack *s)
{
    return (s->index > -1) ? s->data[s->index--] : NULL;
}

int Stack_is_empty(const Stack *s)
{
    return (s->index == -1);
}
#endif

void Stack_grow(Stack *s)
{
    s->capacity *= 2;
    data = (void**)realloc((void*)data, s->capacity * sizeof(void*));
}

void Stack_free(Stack *s)
{
    free(s->data);
}
