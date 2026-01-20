#pragma once

// Definierar vilka typer av händelser systemet kan hantera
enum class EventType {
    TEMP,
    BUTTON,
    MOTION
};
// Själva "händelse-paketet". Innehåller all data för ett event.
struct Event {
    int timestamp;
    int sensorId;
    EventType type;
    int value;
};