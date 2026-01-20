#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "EventModel.h"
#include "EventLog.h"
#include "Queue.h"
#include "AlarmSet.h"

using namespace std;

static int globalTimestamp = 0;

Event createRandomEvent() {
    Event e;
    e.timestamp = ++globalTimestamp;
    e.sensorId = rand() % 5;
    e.type = static_cast<EventType>(rand() % 3);
    e.value = rand() % 100;
    return e;
}

void insertionSort(EventLog* log) {
    for (int i = 1; i < log->size; ++i) {
        Event key = log->data[i];
        int j = i - 1;
        while (j >= 0 && log->data[j].timestamp > key.timestamp) {
            log->data[j + 1] = log->data[j];
            j--;
        }
        log->data[j + 1] = key;
    }
}

void printHelp() {
    cout << "Commands:\n";
    cout << "  tick <n>              Run n iterations\n";
    cout << "  print                 Print event log\n";
    cout << "  sort insertion        Sort log\n";
    cout << "  find <id>             Find events by sensor\n";
    cout << "  alarms                List active alarms\n";
    cout << "  set-threshold <value> Set temperature threshold\n";
    cout << "  help                  Show help\n";
    cout << "  exit                  Exit program\n";
}

int main() {
    // Initiera slumpgeneratorn en gång vid start
    srand((unsigned int)time(nullptr));

    // Skapa de nödvändiga objekten i minnet (dynamisk allokering)
    EventLog* log = log_create(8);
    Queue* queue = queue_create(5);
    AlarmSet alarms = alarm_create();

    printHelp();

    // Huvudloopen som körs tills användaren skriver "exit"
    while (true) {
        cout << "\n> ";
        string command;
        cin >> command;

        if (command == "tick") {
            int n;
            cin >> n;
            for (int i = 0; i < n; ++i) {
                // 1. Simulera att en sensor skickar data
                Event e = createRandomEvent();
                queue_enqueue(queue, e);

                // 2. Bearbeta datan (ta ut den från kön och logga/kolla larm)
                Event out;
                if (queue_dequeue(queue, &out)) {
                    log_append(log, out);
                    alarm_update(alarms, out);
                }
            }
            cout << "Tick executed: " << n << " iterations\n";
        }
        else if (command == "print") {
            log_print(log);
        }
        else if (command == "sort") {
            string name;
            cin >> name;
            if (name == "insertion") {
                insertionSort(log);
                cout << "Log sorted\n";
            }
            else {
                cout << "Unknown sort algorithm\n";
            }
        }
        else if (command == "find") {
            int id;
            cin >> id;
            log_find_sensor(log, id);
        }
        else if (command == "alarms") {
            alarm_print(alarms);
        }
        else if (command == "set-threshold") {
            int value;
            cin >> value;
            alarms.threshold = value;
            cout << "Threshold set to " << value << "\n";
        }
        else if (command == "help") {
            printHelp();
        }
        else if (command == "exit") {
            break;
        }
        else {
            cout << "Unknown command. Type 'help'\n";
        }
    }

    // VIKTIGT: Städa upp minnet innan programmet avslutas för att undvika minnesläckor
    log_destroy(log);
    queue_destroy(queue);
    return 0;
}