# ESP-Thermostat

In Zeiten, in denen das Heizen ein Vermögen kostet, haben viele Haushalte sich entschieden, Smarte Thermostate zur Steuerung der Raumtemperatur zu kaufen. Diese kosten allerdings gerne 60-100€, was ich für zu teuer halte und nicht bereit bin zu zahlen. 

Deshalb habe ich mich dazu entschlossen, mein eigenes Thermostat zu bauen!

Das Ergebnis des Bauprozesses möchte ich hier veröffentlichen.

## Konzeptidee
Meine Idee ist, dass ich wie bei gekauften Smarten Thermostaten das bestehende Thermostat ersetze. Allerdings nutzte ich aber den Metall-Anschluss-Ring des originalen Thermostats zur Befestigung. Mit einem kleinen Stepper Motor und einem Wemos D1 Mini Mikrocontroller, lässt sich der Bolzen der Heizung steuern, der beeinflusst, wie viel warmes Wasser in den Heizkörper fließt. Die Bewegung wird mit einer Schraube getätigt, welche vom Motor gedreht wird und somit zur Heizung, bzw. von ihr weg, bewegt wird.


## Einstellungen auf lokaler Website
<img src="/img/screenshot-main.png" width="45%"> <img src="/img/screenshot-stepper.png" width="45%">

## Richtiger Anschluss und Gewinde eines Heizkörperventils ermitteln
...

## Empfohlenes Vorwissen
- Löten
- Erfahrung mit Arduinos oder ESPs

## Benötigte Materialien
### Bauteileliste
- Wemos D1 Mini
- 28byj-48 Stepper Motor + Driver Modul (Standardmotor in Arduino Kits)
- DHT11 oder DHT22 (geht aber auch ohne)

### Werkzeug
- Lötkolben
- Möglichst 3D Drucker (nicht zwingend notwendig, Kauf der Teile auch möglich)

### Kleinzeug
- 1x Female Steckpins für D1 Mini
- Kabel zum Verlöten
- 3x M3 Schraube (25mm oder besser 30mm) + 3x M3 Mutter
- Micro USB Kabel + Netzteil

Natürlich benötigt man auch einen Laptop zum Flashen des ESPs

## Zusammenbau
Genaue Anweisung zum Zusammenbau im YouTube-Video [hier](youtube.com) - Link fehlt noch

