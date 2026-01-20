#include "AlarmSet.h"
#include <iostream>

using namespace std;

AlarmSet alarm_create() {
    AlarmSet set;
    set.count = 0;
    set.threshold = 50;
    return set;
}

bool alarm_contains(const AlarmSet& set, int sensorId) {
    for (int i = 0; i < set.count; ++i)
        if (set.sensors[i] == sensorId)
            return true;
    return false;
}

void alarm_add(AlarmSet& set, int sensorId) {
    if (!alarm_contains(set, sensorId)) {
        set.sensors[set.count++] = sensorId;
    }
}

void alarm_remove(AlarmSet& set, int sensorId) {
    for (int i = 0; i < set.count; ++i) {
        if (set.sensors[i] == sensorId) {
            set.sensors[i] = set.sensors[set.count - 1];
            set.count--;
            return;
        }
    }
}
// Uppdaterar larm-listan baserat på inkommande data
void alarm_update(AlarmSet& set, const Event& e) {
    // Vi reagerar endast om det är ett temperatur-event
    if (e.type == EventType::TEMP) {
        // Om temperaturen går över gränsen (threshold), lägg till i larmlistan
        if (e.value > set.threshold)
            alarm_add(set, e.sensorId);
        // Om temperaturen sjunker under gränsen, ta bort larmet för denna sensor
        else
            alarm_remove(set, e.sensorId);
    }
}

void alarm_print(const AlarmSet& set) {
    if (set.count == 0) {
        cout << "No active alarms\n";
        return;
    }
    cout << "Active alarms (sensorId): ";
    for (int i = 0; i < set.count; ++i)
        cout << set.sensors[i] << " ";
    cout << "\n";
}