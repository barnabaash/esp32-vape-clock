# esp32-vape-clock
# ESP32-C3 Vape Clock

Két kiszedett VapSolo Quads kijelző órának/percnek, ESP32-C3 Super Minivel, NTP idővel.

Library: [SmokeDisplays](https://github.com/the-developer-guy/SmokeDisplays)

## Pinout

| Modul láb | Óra (bal) | Perc (jobb) |
|---|---|---|
| A | GPIO0 | GPIO7 |
| B | GPIO1 | GPIO10 |
| C | GPIO3 | GPIO20 |
| D | GPIO4 | GPIO21 |
| E | GPIO5 | GPIO2 |
| F | GPIO6 | GPIO8 |

A modulokon nincs tápláb, Charlieplexing, 12 GPIO kell.

## Használat
1. Telepítsd a SmokeDisplays library-t (ZIP).
2.Töltsd fel az ESP32-C3-ra.

![kép](images/clock.jpg)
