# ESP-Thermostat

In Zeiten, in denen das Heizen ein Vermögen kostet, haben viele Haushalte sich entschieden, Smarte Thermostate zur Steuerung der Raumtemperatur zu kaufen. Diese kosten allerdings gerne 60-100 €, was ich für zu teuer halte und nicht bereit bin zu zahlen.

Deshalb habe ich mich dazu entschlossen, mein eigenes Thermostat zu bauen!

Das Ergebnis des Bauprozesses möchte ich hier veröffentlichen. Die Kosten für den Eigenbau sind ca. 10-15 €.

## Konzeptidee
Meine Idee ist, dass ich, wie bei gekauften smarten Thermostaten, das bestehende Thermostat ersetze. Allerdings nutze ich den Metall-Anschluss-Ring des originalen Thermostats zur Befestigung. Mit einem kleinen Schrittmotor und einem Wemos D1 Mini Mikrocontroller lässt sich der Bolzen der Heizung steuern, der beeinflusst, wie viel warmes Wasser in den Heizkörper fließt. Die Bewegung wird mit einer Schraube getätigt, die vom Motor gedreht wird und somit zur Heizung bzw von ihr weg bewegt wird.

YouTube-Video zum Bauprozess [hier](https://www.youtube.com/watch?v=YOUTUBE_VIDEO_ID_HERE) - Link fehlt noch

[![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/YOUTUBE_VIDEO_ID_HERE/0.jpg)](https://www.youtube.com/watch?v=YOUTUBE_VIDEO_ID_HERE)


## Einstellungen auf lokaler Website
<img src="/img/screenshot-main.png" width="50%"> <img src="/img/screenshot-stepper.png" width="49%">
Der ESP erzeugt eine Website, über die sich Einstellungen für das Thermostat vornehmen lassen. Es ist möglich, einen Zeitplan zu erstellen oder die Zieltemperatur für den Raum einzustellen. Die Offsettemperatur des Temperatursensors ist dafür da, da es sein kann, dass die Temperatur direkt neben der Heizung höher ist als im restlichen Raum.

## Empfohlenes Vorwissen
- Löten
- Erfahrung mit Arduinos oder ESPs

## Benötigte Materialien
### Bauteileliste
- Wemos D1 Mini [^1]
- 28byj-48 Stepper Motor + Driver Modul (Standardmotor in Arduino Kits)
- DHT11 oder DHT22 (geht aber auch ohne)

[^1]: oder ähnlichen ESP8266, dann muss man das Case aber ggf. anpassen

### Werkzeuge
- Lötkolben
- Möglichst 3D Drucker (nicht zwingend notwendig, Kauf der Teile auch möglich)

### Kleinzeug
- 1x Female-Steckpins für D1 Mini
- Kabel zum Verlöten
- 3x M3 Schraube (25mm oder besser 30mm) + 3x M3 Mutter
- Micro USB Kabel + Netzteil

Natürlich benötigt man auch einen Laptop zum Programmieren des ESPs

## 3D-Druck-Dateien
Da viele Leute keien 3D Drucker besitzen habe ich mich entschieden die gedruckten Teile selber auf [etsy](etsy.com) zu verkaufen. Dabei biete ich die Teile für den Filamentpreis an und habe kein Interesse daran große Gewinne zu machen.

Allerdings besitze ich nur einen Prusa Mini, somit ist die Qualität der Drucke nicht die beste.

Link zum Verkauf: [hier](etsy.com) - Link fehlt noch


## Richtiger Anschluss und Gewinde des Heizkörperventils ermitteln
<img src="/img/IMG_2659.jpeg" width="49%"> <img src="/img/IMG_2658.jpeg" width="49%">
<img src="/img/IMG_2657.jpeg" width="49%"> <img src="/img/IMG_2654.jpeg" width="49%">

#### Abmaße
- Außendurchmesser Heizungsrohr: 30mm
- Außendurchmesser Sechskant am Heizungsrohr: 15mm
- Innendurchmesser Schraubring: 26,5mm (+/- 0,5mm)
- Außendurchmesser Thermostatring: 28mm
- Innendurchmesser Thermostatring: 20,5mm

Das sind die Maße von der Heizung, für die ich mein Thermostat gebaut habe. Ich weiß nicht, ob die Thermostat-Befestigungen genormt sind. Falls es bei dir die gleichen sind, sollten die 3D-Teile passen.

<img src="/img/3d-holder.jpeg" width="250px">

## Zusammenbau
Genaue Anweisung zum Zusammenbau im YouTube-Video [hier](youtube.com) - Link fehlt noch

