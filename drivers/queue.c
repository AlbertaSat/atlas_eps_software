#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

void QUEUE_Init(Queue* const me,
            uint8_t (*isFullfunction)(Queue* const me),
            uint8_t (*isEmptyfunction)(Queue* const me),
            uint8_t (*getSizefunction)(Queue* const me),
            void (*insertfunction)(Queue* const me, uint8_t k),
            uint8_t (*removefunction)(Queue* const me) )
{ 
    /* initialize attributes */

    me->head = 0;
    me->size = 0;
    me->tail = 0;
    
    /* initialize member function pointers */
    
    me->isFull = isFullfunction;
    me->isEmpty = isEmptyfunction;
    me->getSize = getSizefunction;
    me->insert = insertfunction;
    me->remove = removefunction;


}

/* operation Cleanup() */
void QUEUE_Cleanup(Queue* const me)
{

}

/* operation isFull() */
uint8_t QUEUE_isFull(Queue* const me)
{
    return (me->head+1) % QUEUE_MAX_SIZE == me->tail;
}

/* operation isEmpty() */
uint8_t QUEUE_isEmpty(Queue* const me)
{ 
    return (me->head == me->tail);
}

/* operation getSize() */ 
uint8_t QUEUE_getSize(Queue* const me)
{ 
    return me->size;
}

/* operation insert(int) */ 
void QUEUE_insert(Queue* const me, uint8_t value)
{
    if (!me->isFull(me))
    { 
        me->buffer[me->head] = value;
        me->head = (me->head+1) % QUEUE_MAX_SIZE;
        ++me->size;
    }
}

/* operation remove */
uint8_t QUEUE_remove(Queue* const me)
{ 
    uint8_t value = 0;
    
    if (!me->isEmpty(me)) 
    { 
        value = me->buffer[me->tail]; 
        me->tail = (me->tail+1) % QUEUE_MAX_SIZE; 
        --me->size;
    }

    return value; 
}

Queue * QUEUE_Create(void)
{ 
    Queue* me = (Queue *) malloc(sizeof(Queue)); 
    if(me!=NULL)
    {
        QUEUE_Init(me, QUEUE_isFull, QUEUE_isEmpty, QUEUE_getSize, QUEUE_insert, QUEUE_remove);
    } 

    return me; 
}

void QUEUE_Destroy(Queue* const me)
{ 
    if(me!=NULL) 
    {
        QUEUE_Cleanup(me); 
    }
    
    free(me); 
}
