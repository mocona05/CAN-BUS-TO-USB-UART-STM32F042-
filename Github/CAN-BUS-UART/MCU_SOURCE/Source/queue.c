#include "board.h"



// 원형큐 초기화 함수
void init_queue(QueueType *q)
{
    q->front = q->rear = 0;    
}

// 공백상태 검출 함수
int is_empty(QueueType *q)
{
    return (q->front == q->rear);
}

// 포화상태 검출 함수
int is_full(QueueType *q)
{
    return ((q->rear+1)%MAX_QUEUE_SIZE == q->front);
}

// 삽입 함수
QueueStatus enqueue(QueueType *q, unsigned char item)
{ 
    if( is_full(q) ) 
        return QUEUE_ERROR;
	q->rear = (q->rear+1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = item;
    
    return QUEUE_SUCCESS;    
}

// 삭제 함수
QueueStatus dequeue(QueueType *q, unsigned char *item) 
{ 
    if( is_empty(q) )
        return QUEUE_ERROR;
    q->front = (q->front+1) % MAX_QUEUE_SIZE;
    *item = q->queue[q->front];
    
    return QUEUE_SUCCESS;
}
