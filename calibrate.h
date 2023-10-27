const char calibrate_html[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="de">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Thermostat - Kalibrieren</title>

    <style>
        body {
            font-family: Arial;
        }

        h3 {
            text-align: center;
        }

        table {
            width: 100%;
            max-width: 400px;
            margin: auto;
        }

        td {
            text-align: center;
            border-bottom: 1px dotted black;
            padding-top: 8px;
            padding-bottom: 8px;
        }


        button {
            background-color: rgba(238, 238, 238, 0.8);
            border: 1px solid black;
            border-radius: 5px;
            cursor: pointer;
        }

        button:active {
            background-color: #F0F0F1;
            border-color: rgba(0, 0, 0, 0.15);
        }
    </style>

</head>
<body>

<a href="/">zurück</a>
<h3>Kalibrieren des Schrittmotor</h3>
<table>
    <tr>
        <td colspan="2">
            <button onclick="http('/set?pos=0')">Zum Nullpunkt fahren</button>
            <br>
            <small>(Nullpunkt = Thermostat geöffnet)</small>
        </td>
    </tr>
    <tr>
        <td>
            <a>Aktueller Endpunkt:</a>
        </td>
        <td>
            <a id="endPos">...</a>
        </td>
    </tr>
    <tr>
        <td>
            <a>Neuer Endpunkt:</a>
        </td>
        <td>
            <input id="newEndPos" type="number" step="25" min="-100000" max="100000">
            <button onclick="newEndPos()">save</button>
        </td>
    </tr>
    <tr>
        <td colspan="2">
            <button onclick="http('/set?pos=end')">Zum Endpunkt fahren</button>
            <br>
            <small>(Endpunkt = Thermostat geschlossen)</small>
        </td>
    </tr>
    <tr>
        <td>
            <a>Akutelle Position:</a>
        </td>
        <td>
            <a id="currentPos">...</a>
            <button onclick="refreshCurrentPos()"><img src="https://htmlacademy.ru/assets/icons/reload.png"></button>
        </td>
    </tr>
    <tr>
        <td>
            <a>Setzte aktuelle Position:</a>
        </td>
        <td>
            <input id="newCurrentPos" type="number" step="25" min="-100000" max="100000">
            <button onclick="newCurrentPos()">save</button>
        </td>
    </tr>
    <tr>
        <td colspan="2">
            <button onclick="http('/set?stepper=stop')" style="background-color: red">STOP</button>
        </td>
    </tr>
</table>


<script>
    window.onload = function () {
        document.getElementById('endPos').innerText = http("/get?value=endpos")
        document.getElementById('currentPos').innerText = http("/get?value=pos")
    }

    function newEndPos() {
        let newpos = document.getElementById("newEndPos").value
        http('/set?newend=' + String(newpos))
        document.getElementById('endPos').innerText = newpos
        document.getElementById("newEndPos").value = ""
    }

    function newCurrentPos() {
        let newpos = document.getElementById("newCurrentPos").value
        http('/set?newpos=' + String(newpos))
        document.getElementById('currentPos').innerText = newpos
        document.getElementById("newCurrentPos").value = ""
    }

    function refreshCurrentPos() {
        document.getElementById('currentPos').innerText = http("/get?value=pos")
    }

    function http(url, withPrint = false) {
        console.log(url)
        try {
            var request = new XMLHttpRequest();
            request.open("GET", url, false);
            request.send(null);

            if (request.status === 404) {
                return 'error'
            }

            if (true || withPrint) {
                console.log(request.responseText)
            }
            return request.responseText;
        } catch (e) {
            console.log(e)
        }
    }
</script>

</body>
</html>
)=====";