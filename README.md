Nedan är länken till mitt repo bara att gå in och kika!
https://github.com/samansadeq/SensorSystem-CPP

# Sensorövervakningssystem (C++)

Detta är ett händelsestyrt system simulerat i konsolen, skrivet i C++. Projektet demonstrerar användning av dynamiskt minne, kösystem och modulär kodstruktur.

## 🛠 Funktioner

* **Händelsekö (Ringbuffer):** En cirkulär kö (`Queue`) som hanterar inkommande sensordata effektivt utan att flytta minne.
* **Dynamisk Logg:** En `EventLog` som automatiskt växer (dubblerar kapacitet) när minnet tar slut.
* **Larmmodul:** Övervakar `TEMP`-events och varnar om temperaturen överstiger ett tröskelvärde.
* **Sortering:** Innehåller en implementation av **Insertion Sort** för att sortera loggen kronologiskt.

## 📂 Filstruktur

* `main.cpp` - Huvudprogrammet och loopen.
* `EventModel.h` - Datastrukturer för Events.
* `Core/` - Innehåller `Queue` och `EventLog`.
* `Modules/` - Innehåller `AlarmSet`.

## 🚀 Hur man kör projektet

1.  Öppna `.sln`-filen i **Visual Studio**.
2.  Bygg lösningen (Ctrl + Shift + B).
3.  Kör programmet (F5).

### Kommandon
När programmet körs kan du använda följande kommandon:

| Kommando | Beskrivning |
| :--- | :--- |
| `tick <n>` | Kör simuleringen *n* steg framåt. |
| `print` | Skriver ut alla sparade händelser. |
| `alarms` | Visar vilka sensorer som larmar just nu. |
| `sort insertion` | Sorterar loggen efter tid. |
| `set-threshold <x>` | Ändra larmgränsen till x grader. |
