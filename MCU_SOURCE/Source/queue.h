#pragma once


#ifndef QUEUE_H
#define QUEUE_H

/* Defines -------------------------------------------------------------------*/
#define MAX_QUEUE_SIZE      255

/* Type declarations ---------------------------------------------------------*/
typedef struct
{
    volatile int32_t	front, rear;
    volatile uint8_t	queue[MAX_QUEUE_SIZE];
} QueueType;

typedef enum {QUEUE_SUCCESS = 0, QUEUE_ERROR = !QUEUE_SUCCESS, QUEUE_FULL, QUEUE_EMPT} QueueStatus;



/* Function prototypes -------------------------------------------------------*/
void init_queue(QueueType *q);
int is_empty(QueueType *q);
int is_full(QueueType *q);
QueueStatus enqueue(QueueType *q, unsigned char item);
QueueStatus dequeue(QueueType *q, unsigned char *item);

#endif

