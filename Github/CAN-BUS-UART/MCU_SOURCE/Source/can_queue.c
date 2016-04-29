#include "board.h"

#ifndef CAN_TXD_DISABLE
CAN_Queue_t CAN_txd_queue;
#endif
CAN_Queue_t CAN_rxd_queue;


// 원형큐 초기화 함수
void can_init_queue(CAN_Queue_t *q)
{
    q->front = q->rear = 0;    
}

// 공백상태 검출 함수
//비어 있으면 true 반환
int can_is_empty(CAN_Queue_t *q)
{
    return (q->front == q->rear);
}

// 포화상태 검출 함수
//꽉차 있으면 true 반환
int can_queue_is_full(CAN_Queue_t *q)
{
    return ((q->rear+1)%MAX_CAN_QUEUE_SIZE == q->front);
}

// 삽입 함수
QueueStatus CAN_enqueue(CAN_Queue_t *q, volatile CanQueueType  item)
{ 
    if( can_queue_is_full(q) ) 
        return QUEUE_ERROR;
	q->rear = (q->rear+1) % MAX_CAN_QUEUE_SIZE;
	q->queue[q->rear] = item;
    
    return QUEUE_SUCCESS;    
}

// 삭제 함수
QueueStatus CAN_dequeue(CAN_Queue_t *q, CanQueueType *item) 
{ 
    if( can_is_empty(q) )
        return QUEUE_ERROR;
    q->front = (q->front+1) % MAX_CAN_QUEUE_SIZE;
    *item = q->queue[q->front];
    
    return QUEUE_SUCCESS;
}
