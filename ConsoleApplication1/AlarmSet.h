#pragma once
#include "EventModel.h"

struct AlarmSet {
    int sensors[16];
    int count;
    int threshold;
};

AlarmSet alarm_create();
void alarm_update(AlarmSet& set, const Event& e);
void alarm_print(const AlarmSet& set);