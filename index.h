const char index_html[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="de">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">

    <title>Thermostat</title>

    <style>
        header {
            background-color: lightgray;
            border-radius: 5px;
            padding: 5px;
            padding-bottom: 8px;
            margin-bottom: 2%;
        }

        body {
            font-family: Arial;
        }

        h3 {
            text-align: center;
        }

        h5 {
            margin-top: 3px;
            margin-bottom: 3px;
        }

        table {
            width: 100%;
            max-width: 400px;
            margin: auto;
        }

        td {
            text-align: left;
            border-bottom: 1px dotted black;
            padding-top: 8px;
            padding-bottom: 8px;
        }

        button {
            background-color: rgba(238, 238, 238, 0.8);
            border: 1px solid black;
            border-radius: 5px;
        }

        button:active {
            background-color: #F0F0F1;
            border-color: rgba(0, 0, 0, 0.15);
        }

        small {
            margin: 2px;
        }

        .center {
            text-align: center;
        }

        .rightFloat {
            float: right;
        }

        .tempButton {
            width: 20%;
            min-width: 20px;
        }

        .timeHead {
            text-align: center;
            text-decoration: underline 2px solid black;
        }

        .timePlanDiv {
            border: 1px dotted black;
            border-radius: 5px;
            padding: 5px;
            margin: 5px;
        }

        .dayPlanDiv {
            padding-bottom: 3px;
        }

        .rmButton {
            background-color: orangered;
            border-radius: 50%;
            float: right;
            margin: 5px;
            border-color: transparent;
        }

        .rmButton:active {
            background-color: darkred;
        }

        .switch {
            position: relative;
            display: inline-block;
            width: 30px;
            height: 20px;
            margin: 5px;
        }

        .switch input {
            opacity: 0;
            width: 0;
            height: 0;
        }

        .slider {
            position: absolute;
            cursor: pointer;
            top: 0;
            left: 0;
            right: 0;
            bottom: 0;
            background-color: #ccc;
            -webkit-transition: .2s;
            transition: .2s;
            border-radius: 34px;
        }

        .slider:before {
            position: absolute;
            content: "";
            height: 16px;
            width: 16px;
            left: 2px;
            bottom: 2px;
            background-color: white;
            -webkit-transition: .2s;
            transition: .2s;
            border-radius: 50%;
        }

        input:checked + .slider {
            background-color: #56f157;
        }

        input:checked + .slider:before {
            -webkit-transform: translateX(10px);
            -ms-transform: translateX(10px);
            transform: translateX(10px);
        }

    </style>


</head>
<body>

<header>
    <small id="ipAdress">%IPADRESSE%</small>
    <small id="wifi" class="rightFloat">WiFi: %WIFI%</small>
</header>


<table>
    <tr>
        <td>
            <h5>Aktuelle Temperatur:</h5>
        </td>
        <td>
            <h5 id="currentTemp">%TEMPERATURE%</h5>
        </td>
    </tr>

    <tr>
        <td>
            <h5>Luftfeuchtigkeit:</h5>
        </td>
        <td>
            <h5 id="humidity">%HUMIDITY%</h5>
        </td>
    </tr>

    <tr>
        <td>
            <h5>Zieltemperatur:</h5>
        </td>
        <td>
            <div>
                <input id="estimatedTemp" onchange="tempChanged(0)" placeholder="Temp" type="number" step="0.5" t
                       min="5" max="30">
                <!--                <h5 id="estimatedTemp">19,5°C</h5>-->
                <br>
                <button class="tempButton" onclick="tempChanged(2)">-</button>
                <button class="tempButton" onclick="tempChanged(1)">+</button>
            </div>
        </td>
    </tr>

    <tr>
        <td class="center" colspan="2">
            <h5 class="timeHead">Zeitplan</h5>

            <div id="timePlanDivs"></div>

            <button onclick="addTimePlan()">+</button>
            <button onclick="saveTimePlan()">save</button>
        </td>
    </tr>

    <tr>
        <td>
            <h5>Temperatur außerhalb des Zeitplans:</h5>
        </td>
        <td>
            <input id="normalTemp" placeholder="Temp" type="number" step="0.5" t min="5" max="30">
            <button onclick="normalTempChanged()">save</button>
        </td>
    </tr>

    <tr>
        <td>
            <h5>DHT Temperatur Offset:</h5>
        </td>
        <td>
            <input id="tempOffset" placeholder="Temp" type="number" step="0.5" t min="-20" max="20">
            <button onclick="tempOffsetChanged()">save</button>
        </td>
    </tr>

    <tr>
        <td class="center" colspan="2">
            <button onclick="window.location.href = '/calibrate'">Kalibrieren des Schrittmotor</button>
        </td>
    </tr>
</table>

<script>
    let chosenColor = 'rgba(113, 255, 0, 0.3)'
    let notChosenColor = 'rgba(255, 0, 0, 0.3)'

    window.onload = function () {

        document.getElementById('ipAdress').innerText = "IP: " + http('/get?value=ipadress')
        document.getElementById('wifi').innerText = "WLAN: " + http('/get?value=wifi')
        document.getElementById('currentTemp').innerText = http('/get?value=currenttemp')
        document.getElementById('humidity').innerText = http('/get?value=humidity')
        document.getElementById('estimatedTemp').value = http('/get?value=estimatedtemp')
        document.getElementById('normalTemp').value = http('/get?value=normaltemp')
        document.getElementById('tempOffset').value = http('/get?value=tempoffset')

        //let timePlan = JSON.parse('{"0": {"activ": true, "days": ["Mo", "Di"], "start": "12:00", "end": "21:00", "temp": "19.5"}, "1": {"activ": false, "days": ["Mi", "Do"], "start": "13:00", "end": "20:00", "temp": "19"}}')
        let timePlan = JSON.parse(http('/get?value=timeplan', true))
        console.log(timePlan)
        for (let k in timePlan) {
            let value = timePlan[k]
            addTimePlan(value)
        }
    }

    function tempChanged(add) {
        let estimatedTempElement = document.getElementById('estimatedTemp')
        var temp = parseFloat(estimatedTempElement.value.replace(',', '.'))
        console.log(temp)
        if (add == 1) {
            temp += 0.5
        } else if (add == 2) {
            temp -= 0.5
        }

        http('/set?temp=' + String(temp))
        estimatedTempElement.value = temp
    }

    function onDayClicked(id) {
        let element = document.getElementById(id)

        if (element.style.backgroundColor === chosenColor) {
            element.style.backgroundColor = notChosenColor
        } else {
            element.style.backgroundColor = chosenColor
        }
    }

    function addTimePlan(plan = null) {
        let timePlanDivs = document.getElementById('timePlanDivs')
        let nr = timePlanDivs.getElementsByClassName("timePlanDiv").length

        let timePlanDiv = document.createElement('div')
        timePlanDiv.id = 'timePlanDiv' + String(nr)
        timePlanDiv.className = 'timePlanDiv'


        let dayDiv = document.createElement('div')
        dayDiv.id = 'dayPlanDiv' + String(nr)
        dayDiv.className = 'dayPlanDiv'
        dayDiv.innerHTML = `
            <button id="1${nr}" style="background-color: ${notChosenColor}" onClick="onDayClicked(this.id)">Mo</button>
            <button id="2${nr}" style="background-color: ${notChosenColor}" onClick="onDayClicked(this.id)">Di</button>
            <button id="3${nr}" style="background-color: ${notChosenColor}" onClick="onDayClicked(this.id)">Mi</button>
            <button id="4${nr}" style="background-color: ${notChosenColor}" onClick="onDayClicked(this.id)">Do</button>
            <button id="5${nr}" style="background-color: ${notChosenColor}" onClick="onDayClicked(this.id)">Fr</button>
            <button id="6${nr}" style="background-color: ${notChosenColor}" onClick="onDayClicked(this.id)">Sa</button>
            <button id="0${nr}" style="background-color: ${notChosenColor}" onClick="onDayClicked(this.id)">So</button>
            <br>
        `;

        let addDiv = document.createElement('div')
        addDiv.id = 'timePlan' + String(nr)
        addDiv.innerHTML = `
            <a>von </a>
            <input id="startTime${nr}" type="time">
            <a>bis</a>
            <input id="endTime${nr}" type="time">
            <a>:</a>
            <input id="tempField${nr}" placeholder="Temp" type="number" step="0.5" t min="5" max="30">
            <a>°C</a>
        `;


        let actionDiv = document.createElement('div')
        actionDiv.id = 'actionDiv' + String(nr)
        actionDiv.style.textAlign = 'right'
        actionDiv.innerHTML = `
        <button class="rmButton" onClick="rmTimePlan(${timePlanDiv.id})">-</button>
         <label class="switch">
            <input id="checkbox${nr}" type="checkbox" checked>
            <span class="slider"></span>
        </label>
    `;

        timePlanDiv.appendChild(dayDiv)
        timePlanDiv.appendChild(addDiv)
        timePlanDiv.appendChild(actionDiv)
        timePlanDivs.appendChild(timePlanDiv)

        if (plan != null) {
            for (let d of plan['days']) {
                document.getElementById(String(d) + nr).style.backgroundColor = chosenColor
            }

            console.log(plan['activ'], Boolean(plan['activ']))
            if (plan['activ'] !== true) {
                document.getElementById('checkbox' + nr).checked = false
            }

            document.getElementById('startTime' + nr).value = plan['start']
            document.getElementById('endTime' + nr).value = plan['end']
            document.getElementById('tempField' + nr).value = plan['temp']
        }
    }

    function rmTimePlan(element) {
        if (document.getElementById(element) != null) {
            document.getElementById(element)
        } else {
            element.remove()
        }
    }

    function saveTimePlan() {
        let timePlanDivs = document.getElementById('timePlanDivs')
        let divElements = timePlanDivs.getElementsByClassName('timePlanDiv')

        http('/timeplan?action=new')

        for (let i = 0; i < divElements.length; i++) {
            //{"0": {"days": ["Mo", "Di"], "start": "12:00", "end": "21:00", "temp": "19.5"}, "1": {"days": ["Mi", "Do"], "start": "13:00", "end": "20:00", "temp": "19"}}
            let dayPlanDiv = document.getElementById('dayPlanDiv' + i)
            var days = []
            for (let button of dayPlanDiv.querySelectorAll(`button[style*="background-color: ${chosenColor}"]`)) {
                days.push(button.id.slice(0, -String(i).length))
            }

            let start = document.getElementById('startTime' + i).value
            let end = document.getElementById('endTime' + i).value
            let temp = document.getElementById('tempField' + i).value
            let activ = document.getElementById('checkbox' + i).checked

            http(`/timeplan?n=${String(i)}&activ=${activ}&days=[${days.join(',')}]&start=${start}&end=${end}&temp=${temp}`)
        }
    }

    function normalTempChanged() {
        http('/set?normaltemp=' + document.getElementById('normalTemp').value)
    }

    function tempOffsetChanged() {
        http('/set?tempoffset=' + document.getElementById('tempOffset').value)
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

            if (withPrint) {
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