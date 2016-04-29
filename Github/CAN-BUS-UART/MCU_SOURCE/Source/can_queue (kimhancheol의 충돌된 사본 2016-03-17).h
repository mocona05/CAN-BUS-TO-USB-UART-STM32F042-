#pragma once


/* Defines -------------------------------------------------------------------*/
#define MAX_CAN_QUEUE_SIZE      10

/* Type declarations ---------------------------------------------------------*/



typedef struct
{
    volatile int16_t	front, rear;
    volatile CanQueueType	queue[MAX_CAN_QUEUE_SIZE];
} CAN_Queue_t;

typedef enum {QUEUE_SUCCESS = 0, QUEUE_ERROR = !QUEUE_SUCCESS, QUEUE_FULL, QUEUE_EMPT} QueueStatus;
#ifndef CAN_TXD_DISABLE
extern CAN_Queue_t CAN_txd_queue;
#endif
extern CAN_Queue_t CAN_rxd_queue;


/* Function prototypes -------------------------------------------------------*/
void can_init_queue(CAN_Queue_t *q);
int can_is_empty(CAN_Queue_t *q);
int can_queue_is_full(CAN_Queue_t *q);
QueueStatus CAN_enqueue(CAN_Queue_t *q, volatile CanQueueType  item);
QueueStatus CAN_dequeue(CAN_Queue_t *q, volatile CanQueueType *item);
