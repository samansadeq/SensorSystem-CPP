#include "Queue.h"

Queue* queue_create(int capacity) {
    Queue* q = new Queue;
    q->capacity = capacity;
    q->buffer = new Event[capacity];
    q->head = 0;
    q->tail = 0;
    q->count = 0;
    return q;
}

void queue_destroy(Queue* q) {
    delete[] q->buffer;
    delete q;
}
// Lägger till ett event sist i kön
bool queue_enqueue(Queue* q, Event e) {
    if (q->count == q->capacity) return false;
    // Kontrollera om kön är full (viktigt för att undvika krasch)
    q->buffer[q->tail] = e;
    q->tail = (q->tail + 1) % q->capacity;
    q->count++;
    return true;
}
// Hämtar det äldsta eventet först i kön
bool queue_dequeue(Queue* q, Event* out) {
    // Om kön är tom finns inget att hämta
    if (q->count == 0) return false;
    *out = q->buffer[q->head];
    // Flytta fram "huvudet" cirkulärt
    q->head = (q->head + 1) % q->capacity;
    q->count--;
    return true;
}