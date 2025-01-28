#ifndef QUEUE_H
#define QUEUE_H

typedef struct QueueNode
{
    int key;
    struct QueueNode *next;
    struct QueueNode *prev;
} QueueNode;

typedef struct Queue
{
    QueueNode *front;
    QueueNode *back;
    unsigned int length;

    bool(*empty)(struct Queue *);
    void(*clear)(struct Queue *);
    void(*dequeue)(struct Queue *);
    void(*enqueue)(struct Queue *, QueueNode *);
} Queue;

Queue queue_init(void);
QueueNode *queue_create_node(int key);
void queue_clear(Queue *self);
bool queue_empty(Queue *self);
void queue_dequeue(Queue *self);
void queue_enqueue(Queue *self, QueueNode *node);

#endif
