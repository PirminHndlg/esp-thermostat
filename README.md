# ESP-Thermostat

In Zeiten, in denen das Heizen ein Vermögen kostet, haben viele Haushalte sich entschieden, Smarte Thermostate zur Steuerung der Raumtemperatur zu kaufen. Diese kosten allerdings gerne 60-100€, was ich für zu teuer halte und nicht bereit bin zu zahlen. 

Deshalb habe ich mich dazu entschlossen, mein eigenes Thermostat zu bauen!

Das Ergebnis des Bauprozesses möchte ich hier veröffentlichen. Die Kosten für den Eigenbau sind ca. 10-15€

## Konzeptidee
Meine Idee ist, dass ich wie bei gekauften Smarten Thermostaten das bestehende Thermostat ersetze. Allerdings nutzte ich aber den Metall-Anschluss-Ring des originalen Thermostats zur Befestigung. Mit einem kleinen Stepper Motor und einem Wemos D1 Mini Mikrocontroller, lässt sich der Bolzen der Heizung steuern, der beeinflusst, wie viel warmes Wasser in den Heizkörper fließt. Die Bewegung wird mit einer Schraube getätigt, welche vom Motor gedreht wird und somit zur Heizung, bzw. von ihr weg, bewegt wird.


## Einstellungen auf lokaler Website
<img src="/img/screenshot-main.png" width="50%"> <img src="/img/screenshot-stepper.png" width="49%">
Der ESP erzeugt eine Website, über welche sich dann Einstellungen für das Thermostat vornehmen lassen. Es ist möglich einen Zeitplan zu erstellen oder die Zieltemperatur für den Raum einzustellen. Die Offsettemperatur des Temperatursensors ist dafür da, dass es sein kann, dass die Temperatur direkt neben der Heizung höher ist als im restlichen Raum.

## Richtiger Anschluss und Gewinde eines Heizkörperventils ermitteln
...

## Empfohlenes Vorwissen
- Löten
- Erfahrung mit Arduinos oder ESPs

## Benötigte Materialien
### Bauteileliste
- Wemos D1 Mini [^1]
- 28byj-48 Stepper Motor + Driver Modul (Standardmotor in Arduino Kits)
- DHT11 oder DHT22 (geht aber auch ohne)

[^1]: oder ähnlichen ESP8266, dann muss man das Case aber ggf. anpassen

### Werkzeug
- Lötkolben
- Möglichst 3D Drucker (nicht zwingend notwendig, Kauf der Teile auch möglich)

### Kleinzeug
- 1x Female Steckpins für D1 Mini
- Kabel zum Verlöten
- 3x M3 Schraube (25mm oder besser 30mm) + 3x M3 Mutter
- Micro USB Kabel + Netzteil

Natürlich benötigt man auch einen Laptop zum Programmieren des ESPs

## 3D Druck Dateien
Da viele Leute keien 3D Drucker besitzen habe ich mich entschieden die gedruckten Teile selber auf [etsy](etsy.com) zu verkaufen. Dabei biete ich die Teile für den Filamentpreis an und habe kein Interesse daran große Gewinne zu machen.

Allerdings besitze ich nur einen Prusa Mini, somit ist die Qualität der Drucke nicht die beste.

Link zum Verkauf: [hier](etsy.com) - Link fehlt noch

## Zusammenbau
Genaue Anweisung zum Zusammenbau im YouTube-Video [hier](youtube.com) - Link fehlt noch

