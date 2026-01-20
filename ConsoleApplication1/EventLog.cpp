#include "EventLog.h"
#include <iostream>
#include <string>

using namespace std;

string typeToString(EventType t); 

EventLog* log_create(int capacity) {
    EventLog* log = new EventLog;
    log->size = 0;
    log->capacity = capacity;
    log->data = new Event[capacity];
    return log;
}

void log_destroy(EventLog* log) {
    delete[] log->data;
    delete log;
}

void log_append(EventLog* log, Event e) {
    if (log->size == log->capacity) {
        int newCapacity = log->capacity * 2;
        Event* newData = new Event[newCapacity];
        for (int i = 0; i < log->size; ++i)
            newData[i] = log->data[i];
        delete[] log->data;
        log->data = newData;
        log->capacity = newCapacity;
    }
    log->data[log->size++] = e;
}

// Hjälpfunktion för textkonvertering (behövs för utskrift)
string typeToString(EventType t) {
    switch (t) {
    case EventType::TEMP: return "TEMP";
    case EventType::BUTTON: return "BUTTON";
    case EventType::MOTION: return "MOTION";
    }
    return "?";
}

void log_print(const EventLog* log) {
    if (log->size == 0) {
        cout << "The log is empty\n";
        return;
    }
    for (int i = 0; i < log->size; ++i) {
        const Event& e = log->data[i];
        cout << "[" << e.timestamp << "] "
            << "Sensor " << e.sensorId << " "
            << typeToString(e.type)
            << " Value=" << e.value << "\n";
    }
}

void log_find_sensor(const EventLog* log, int sensorId) {
    bool found = false;
    for (int i = 0; i < log->size; ++i) {
        if (log->data[i].sensorId == sensorId) {
            found = true;
            const Event& e = log->data[i];
            cout << "[" << e.timestamp << "] "
                << typeToString(e.type)
                << " Value=" << e.value << "\n";
        }
    }
    if (!found)
        cout << "No events found for sensor " << sensorId << "\n";
}