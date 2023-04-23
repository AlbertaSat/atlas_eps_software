/** @file queue.h 
*   @brief Queue definition file
*   @date 20-Jan-2023
*   @author Stefan Damkjar
*
*/

/** 
 *  @defgroup QUEUE QUEUE
 *  @brief A simply queue for data buffering.
 *
 *	Related Files
 *   - queue.h
 *   - queue.c
 *   - stdint.h
 */

#ifndef INCLUDE_QUEUE_H_
#define INCLUDE_QUEUE_H_

#include "stdint.h"

#define QUEUE_MAX_SIZE 50

typedef struct Queue Queue;
struct Queue {
    uint8_t buffer[QUEUE_MAX_SIZE];
    uint8_t head;
    uint8_t tail;
    uint8_t size;
    uint8_t (*isFull)(Queue* const me);
    uint8_t (*isEmpty)(Queue* const me);
    uint8_t (*getSize)(Queue* const me);
    void (*insert)(Queue* const me, uint8_t value);
    uint8_t (*remove)(Queue* const me);
};

void QUEUE_Init(Queue* const me,
            uint8_t (*isFullFunction)(Queue* const me),
            uint8_t (*isEmptyFunction)(Queue* const me),
            uint8_t (*getSizeFunction)(Queue* const me),
            void (*insertFunction)(Queue* const me, uint8_t k),
            uint8_t (*removeFunction)(Queue* const me));

void QUEUE_Cleanup(Queue* const me);

/* Operations */ 
uint8_t QUEUE_isFull(Queue* const me);
uint8_t QUEUE_isEmpty(Queue* const me);
uint8_t QUEUE_getSize(Queue* const me);
void QUEUE_insert(Queue* const me, uint8_t k);
uint8_t QUEUE_remove(Queue* const me);
Queue * QUEUE_Create(void);
void QUEUE_Destroy(Queue* const me);

#endif /*INCLUDE_QUEUE_H_*/
