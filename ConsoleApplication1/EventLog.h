#pragma once
#include "EventModel.h"

struct EventLog {
    Event* data;
    int size;
    int capacity;
};

// Funktioner
EventLog* log_create(int capacity);
void log_destroy(EventLog* log);
void log_append(EventLog* log, Event e);
void log_print(const EventLog* log); 
void log_find_sensor(const EventLog* log, int sensorId); 