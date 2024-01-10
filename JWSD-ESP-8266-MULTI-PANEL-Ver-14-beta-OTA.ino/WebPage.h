String message, XML;

const char setwaktu[] PROGMEM = R"=====(

<!DOCTYPE HTML>
<html>

<body bgcolor="#DBF8DC">
    <meta name='viewport' content='width=device-width, initial-scale=1'>

    <head>
        <title>JWSD Hamtronik.com</title>
        <style>
            body {
                width: 97%;
                text-align: center;
            }

            input,
            select,
            button,
            textarea {
                max-width: 100%;
                margin: 5px;
                padding: 5px;
                border-radius: 7px;
            }

            meter,
            progress,
            output {
                max-width: 100%;
            }

            h1 {
                color: grey;
            }

            .note {
                color: #555;
                font-size: 1em;
            }

            .info {
                background-color: #eee;
                border-radius: 3px;
                padding-top: 17px;
                margin: 5px;
            }

            .tombol {
                background-color: #ccc;
                margin: 20px;
                padding: 10px;
                border-radius: 10px;
                text-decoration: none;
            }

            .button {
                padding: 7px 20px;
                font-size: 18px;
                text-align: center;
                cursor: pointer;
                outline: none;
                color: #fff;
                background-color: #04AA6D;
                border: none;
                border-radius: 15px;
                box-shadow: 0 5px #999;
            }

            .button:hover {
                background-color: #3e8e41
            }

            .button:active {
                background-color: #3e8e41;
                box-shadow: 0 5px #666;
                transform: translateY(4px);
            }

            .btn {
                border: none;
                color: white;
                padding: 7px 20px;
                font-size: 14px;
                cursor: pointer;
                border-radius: 10px;
            }

            .success {
                background-color: #04AA6D;
            }

            /* Green */
            .success:hover {
                background-color: #46a049;
            }

            .info {
                background-color: #2196F3;
            }

            /* Blue */
            .info:hover {
                background: #0b7dda;
            }

            .warning {
                background-color: #ff9800;
            }

            /* Orange */
            .warning:hover {
                background: #e68a00;
            }

            .danger {
                background-color: #f44336;
            }

            /* Red */
            .danger:hover {
                background: #da190b;
            }

            .default {
                background-color: #e7e7e7;
                color: black;
            }

            /* Gray */
            .default:hover {
                background: #ddd;
            }
        </style>
    </head>

    <body onload='process()'>

        <h1>Sesuaikan Waktu</h1>
        <div class='info'>
            <span id='day'></span>/<span id='month'></span>/<span id='year'></span><span> </span>
            <span id='hour'></span>:<span id='minute'></span>:<span id='second'></span><span> </span>
            <span id='temp'></span><span>&degC</span><br><br>
        </div>
        <table width='100%'>
            <tr>
                <td>
                    <form>
                        <h4>Tanggal</h4>
                        <input type='date' name='date' min='2017-03-20'><br><br>
                        <input type='submit' value='Ubah Tanggal'>
                    </form>
                </td>
                <td>
                    <form>
                        <h4>Jam</h4>
                        <input type='TIME' name='time'><br><br>
                        <input type='submit' value='Ubah Jam'>
                    </form>
                </td>
            </tr>
        </table>
        <hr>
        <br>
        <a style="text-decoration:none" class='button' href="/setjws">Jam Sholat</a>
        <a style="text-decoration:none" class='button' href="/setwifi">Wifi</a>
        <a style="text-decoration:none" class='button' href="/setdisplay">Display</a>
        <br><br>
        <hr>
        <br><br><br>
        <table align="center">
            <tr>
                <td>
                    <a style="text-decoration:none" href="https://www.youtube.com/hamtronik" class="btn danger"> YOUTUBE </a>
                </td>
                <td>
                    <a style="text-decoration:none" href="https://www.facebook.com/yuliamsyah.adi" class="btn info"> FACEBOOK </a>
                </td>
            </tr>
            <tr>
                <td colspan="2">
                    <br>

                    <a style="text-decoration:none" href="https://www.hamtronik.com" class="btn warning"> HAMTRONIK </a>
                </td>
                <td>

                </td>
            </tr>

        </table>



    </body>

</html>

<script>
    var xmlHttp = createXmlHttpObject();

    function createXmlHttpObject() {
        if (window.XMLHttpRequest) {
            xmlHttp = new XMLHttpRequest();
        } else {
            xmlHttp = new ActiveXObject('Microsoft.XMLHTTP'); // code for IE6, IE5
        }
        return xmlHttp;
    }

    function process() {
        if (xmlHttp.readyState == 0 || xmlHttp.readyState == 4) {
            xmlHttp.open('PUT', 'xml', true);
            xmlHttp.onreadystatechange = handleServerResponse;
            xmlHttp.send(null);
        }
        setTimeout('process()', 1000);
    }

    function handleServerResponse() {
        if (xmlHttp.readyState == 4 && xmlHttp.status == 200) {
            xmlResponse = xmlHttp.responseXML;

            xmldoc = xmlResponse.getElementsByTagName('rYear');
            message = xmldoc[0].firstChild.nodeValue;
            document.getElementById('year').innerHTML = message;

            xmldoc = xmlResponse.getElementsByTagName('rMonth');
            message = xmldoc[0].firstChild.nodeValue;
            document.getElementById('month').innerHTML = message;

            xmldoc = xmlResponse.getElementsByTagName('rDay');
            message = xmldoc[0].firstChild.nodeValue;
            document.getElementById('day').innerHTML = message;

            xmldoc = xmlResponse.getElementsByTagName('rHour');
            message = xmldoc[0].firstChild.nodeValue;
            document.getElementById('hour').innerHTML = message;

            xmldoc = xmlResponse.getElementsByTagName('rMinute');
            message = xmldoc[0].firstChild.nodeValue;
            document.getElementById('minute').innerHTML = message;

            xmldoc = xmlResponse.getElementsByTagName('rSecond');
            message = xmldoc[0].firstChild.nodeValue;
            document.getElementById('second').innerHTML = message;

            xmldoc = xmlResponse.getElementsByTagName('rTemp');
            message = xmldoc[0].firstChild.nodeValue;
            document.getElementById('temp').innerHTML = message;

        }
    }
</script>

</html>


)=====";

const char setjws[] PROGMEM = R"=====(
<!DOCTYPE HTML>
<html>

<body bgcolor="#DBF8DC">
    <meta name="viewport" content="width=device-width, initial-scale=1">

    <head>
        <title>Hamtronik | JWS </title>
        <style>
            body {
                width: 97%;
                text-align: center;
            }

            input,
            select,
            button,
            textarea {
                max-width: 100%;
                margin: 5px;
                padding: 5px;
                border-radius: 7px;
            }

            meter,
            progress,
            output {
                max-width: 100%;
            }

            h1 {
                color: grey;
            }

            .note {
                color: #555;
                font-size: 1em;
            }

            .info {
                background-color: #eee;
                border-radius: 3px;
                padding-top: 17px;
                margin: 5px;
            }

            .tombol {
                background-color: #ccc;
                margin: 20px;
                padding: 10px;
                border-radius: 10px;
                text-decoration: none;
            }

            .button {
                padding: 7px 20px;
                font-size: 18px;
                text-align: center;
                cursor: pointer;
                outline: none;
                color: #fff;
                background-color: #04AA6D;
                border: none;
                border-radius: 15px;
                box-shadow: 0 5px #999;
            }

            .button:hover {
                background-color: #3e8e41
            }

            .button:active {
                background-color: #3e8e41;
                box-shadow: 0 5px #666;
                transform: translateY(4px);
            }

            .btn {
                border: none;
                color: white;
                padding: 7px 20px;
                font-size: 14px;
                cursor: pointer;
                border-radius: 10px;
            }

            .success {
                background-color: #04AA6D;
            }

            /* Green */
            .success:hover {
                background-color: #46a049;
            }

            .info {
                background-color: #2196F3;
            }

            /* Blue */
            .info:hover {
                background: #0b7dda;
            }

            .warning {
                background-color: #ff9800;
            }

            /* Orange */
            .warning:hover {
                background: #e68a00;
            }

            .danger {
                background-color: #f44336;
            }

            /* Red */
            .danger:hover {
                background: #da190b;
            }

            .default {
                background-color: #e7e7e7;
                color: black;
            }

            /* Gray */
            .default:hover {
                background: #ddd;
            }
        </style>
    </head>

    <body onload='process()'>
        <h1>Waktu Sholat</h1>
        <hr>
        <h4>Iqomah</h4>
        <form>
            <table width='100%'>
                <tr>
                    <td>
                        <label for="iqmhs">Subuh</label><br>
                        <input id="iqmhs" placeholder="12" maxlength="2" size="3" />
                    </td>
                    <td>
                        <label for="iqmhd">Dzuhur</label><br>
                        <input id="iqmhd" placeholder="8" maxlength="2" size="3" />
                    </td>
                    <td>
                        <label for="iqmha">Ashar</label><br>
                        <input id="iqmha" placeholder="6" maxlength="2" size="3" />
                    </td>
                </tr>
                <tr>
                    <td>
                        <label for="iqmhm">Maghrib</label><br>
                        <input id="iqmhm" placeholder="5" maxlength="2" size="3" />
                    </td>
                    <td>
                        <label for="iqmhi">Isya</label><br>
                        <input id="iqmhi" placeholder="5" maxlength="2" size="3" />
                    </td>
                    <td>
                        <label for="durasiadzan">Adzan</label><br>
                        <input id="durasiadzan" placeholder="2" maxlength="2" size="3" />
                    </td>
                </tr>
            </table>
            <hr>
            <table width='100%'>
                <tr>
                    <td>
                        <label for="latitude">Latitude</label><br>
                        <input id="latitude" placeholder="-6.165010" size="9" />
                    </td>
                    <td>
                        <label for="longitude">Longitude</label><br>
                        <input id="longitude" placeholder="106.608892" size="9" />
                    </td>
                </tr>
                <tr>
                    <td>
                        <label for="zonawaktu">Zona Waktu</label><br>
                        <input id="zonawaktu" placeholder="7" size="3" />
                    </td>
                    <td>
                        <label for="ihti">Ihtiyati</label><br>
                        <input id="ihti" placeholder="2" maxlength="2" size="3" />
                    </td>
                </tr>
            </table>
            <br>
            <hr>
            <div>
                Nama <br>
                <textarea name="" id="nama" cols="30" rows="5"></textarea>
            </div>
            <div>
                Info Satu <br>
                <textarea name="" id="info1" cols="30" rows="5"></textarea>
                <!-- <label for="info1">Info Satu</label>
                <input id="info1" placeholder="Ini adalah isi dari Info Satu" /> -->
            </div>
            <div>
                Info dua <br>
                <textarea name="" id="info2" cols="30" rows="5"></textarea>
                <!-- <label for="info2">Info Dua</label>
                <input id="info2" placeholder="Ini adalah isi dari Info Dua" /> -->
            </div>
            <br>
            <div>
                <button class="btn info" onClick="setJws()"> Simpan </button>
            </div>
        </form>
        <hr>
        <br>

        <a style="text-decoration:none" class='button' href="/">Home</a>
        <a style="text-decoration:none" class='button' href="/setwifi">Wifi</a>
        <a style="text-decoration:none" class='button' href="/setdisplay">Display</a>
        <br><br>
        <hr>
        <br><br>
        <table align="center">
            <tr>
                <td>
                    <a style="text-decoration:none" href="https://www.youtube.com/hamtronik" class="btn danger"> YOUTUBE </a>
                </td>
                <td>
                    <a style="text-decoration:none" href="https://www.facebook.com/yuliamsyah.adi" class="btn info"> FACEBOOK </a>
                </td>
            </tr>
            <tr>
                <td colspan="2">
                    <br>
                    <a style="text-decoration:none" href="https://www.hamtronik.com" class="btn warning"> HAMTRONIK </a>
                </td>
                <td>
                </td>
            </tr>
        </table>


    </body>
    <script>
        var xmlHttp = createXmlHttpObject();

        function createXmlHttpObject() {
            if (window.XMLHttpRequest) {
                xmlHttp = new XMLHttpRequest();
            } else {
                xmlHttp = new ActiveXObject('Microsoft.XMLHTTP'); // code for IE6, IE5
            }
            return xmlHttp;
        }

        function process() {
            if (xmlHttp.readyState == 0 || xmlHttp.readyState == 4) {
                xmlHttp.open('PUT', 'xml', true);
                xmlHttp.onreadystatechange = handleServerResponse;
                xmlHttp.send(null);
            }

        }

        function handleServerResponse() {
            if (xmlHttp.readyState == 4 && xmlHttp.status == 200) {
                xmlResponse = xmlHttp.responseXML;

                xmldoc = xmlResponse.getElementsByTagName('rIqmhs');
                message = xmldoc[0].firstChild.nodeValue;
                document.getElementById('iqmhs').value = message;

                xmldoc = xmlResponse.getElementsByTagName('rIqmhd');
                message = xmldoc[0].firstChild.nodeValue;
                document.getElementById('iqmhd').value = message;

                xmldoc = xmlResponse.getElementsByTagName('rIqmha');
                message = xmldoc[0].firstChild.nodeValue;
                document.getElementById('iqmha').value = message;

                xmldoc = xmlResponse.getElementsByTagName('rIqmhm');
                message = xmldoc[0].firstChild.nodeValue;
                document.getElementById('iqmhm').value = message;

                xmldoc = xmlResponse.getElementsByTagName('rIqmhi');
                message = xmldoc[0].firstChild.nodeValue;
                document.getElementById('iqmhi').value = message;

                xmldoc = xmlResponse.getElementsByTagName('rDurasiAdzan');
                message = xmldoc[0].firstChild.nodeValue;
                document.getElementById('durasiadzan').value = message;

                xmldoc = xmlResponse.getElementsByTagName('rIhti');
                message = xmldoc[0].firstChild.nodeValue;
                document.getElementById('ihti').value = message;

                xmldoc = xmlResponse.getElementsByTagName('rLatitude');
                message = xmldoc[0].firstChild.nodeValue;
                document.getElementById('latitude').value = message;

                xmldoc = xmlResponse.getElementsByTagName('rLongitude');
                message = xmldoc[0].firstChild.nodeValue;
                document.getElementById('longitude').value = message;

                xmldoc = xmlResponse.getElementsByTagName('rZonaWaktu');
                message = xmldoc[0].firstChild.nodeValue;
                document.getElementById('zonawaktu').value = message;

                xmldoc = xmlResponse.getElementsByTagName('rNama');
                message = xmldoc[0].firstChild.nodeValue;
                document.getElementById('nama').value = message;

                xmldoc = xmlResponse.getElementsByTagName('rInfo1');
                message = xmldoc[0].firstChild.nodeValue;
                document.getElementById('info1').value = message;

                xmldoc = xmlResponse.getElementsByTagName('rInfo2');
                message = xmldoc[0].firstChild.nodeValue;
                document.getElementById('info2').value = message;

            }
        }


        function setJws() {
            console.log("tombol telah ditekan!");
           
            var iqmhs = document.getElementById("iqmhs").value;
            var iqmhd = document.getElementById("iqmhd").value;
            var iqmha = document.getElementById("iqmha").value;
            var iqmhm = document.getElementById("iqmhm").value;
            var iqmhi = document.getElementById("iqmhi").value;
            var durasiadzan = document.getElementById("durasiadzan").value;
            var ihti = document.getElementById("ihti").value;
            var latitude = document.getElementById("latitude").value;
            var longitude = document.getElementById("longitude").value;
            var zonawaktu = document.getElementById("zonawaktu").value;
            var nama = document.getElementById("nama").value;
            var info1 = document.getElementById("info1").value;
            var info2 = document.getElementById("info2").value;
            var datajws = {
                
                iqmhs: iqmhs,
                iqmhd: iqmhd,
                iqmha: iqmha,
                iqmhm: iqmhm,
                iqmhi: iqmhi,
                durasiadzan: durasiadzan,
                ihti: ihti,
                latitude: latitude,
                longitude: longitude,
                zonawaktu: zonawaktu,
                nama: nama,
                info1: info1,
                info2: info2
            };

            var xhr = new XMLHttpRequest();
            var url = "/settingjws";

            xhr.onreadystatechange = function() {
                if (this.onreadyState == 4 && this.status == 200) {
                    console.log(xhr.responseText);
                }
            };
            xhr.open("POST", url, true);
            xhr.send(JSON.stringify(datajws));
        };
    </script>

</html>

)=====";

const char setwifi[] PROGMEM = R"=====(
<!DOCTYPE HTML>
<html>

<body bgcolor="#DBF8DC">
    <meta name="viewport" content="width=device-width, initial-scale=1">

    <head>
        <title>Hamtronik | Display</title>
        <style>
            body {
                width: 97%;
                text-align: center;
            }

            input,
            select,
            button,
            textarea {
                max-width: 100%;
                margin: 5px;
                padding: 5px;
                border-radius: 7px;
            }

            meter,
            progress,
            output {
                max-width: 100%;
            }

            h1 {
                color: grey;
            }

            .note {
                color: #555;
                font-size: 1em;
            }

            .info {
                background-color: #eee;
                border-radius: 3px;
                padding-top: 17px;
                margin: 5px;
            }

            .tombol {
                background-color: #ccc;
                margin: 20px;
                padding: 10px;
                border-radius: 10px;
                text-decoration: none;
            }

            .button {
                padding: 7px 20px;
                font-size: 18px;
                text-align: center;
                cursor: pointer;
                outline: none;
                color: #fff;
                background-color: #04AA6D;
                border: none;
                border-radius: 15px;
                box-shadow: 0 5px #999;
            }

            .button:hover {
                background-color: #3e8e41
            }

            .button:active {
                background-color: #3e8e41;
                box-shadow: 0 5px #666;
                transform: translateY(4px);
            }

            .btn {
                border: none;
                color: white;
                padding: 7px 20px;
                font-size: 14px;
                cursor: pointer;
                border-radius: 10px;
            }

            .success {
                background-color: #04AA6D;
            }

            /* Green */
            .success:hover {
                background-color: #46a049;
            }

            .info {
                background-color: #2196F3;
            }

            /* Blue */
            .info:hover {
                background: #0b7dda;
            }

            .warning {
                background-color: #ff9800;
            }

            /* Orange */
            .warning:hover {
                background: #e68a00;
            }

            .danger {
                background-color: #f44336;
            }

            /* Red */
            .danger:hover {
                background: #da190b;
            }

            .default {
                background-color: #e7e7e7;
                color: black;
            }

            /* Gray */
            .default:hover {
                background: #ddd;
            }
        </style>
    </head>

    <body onload='process()'>
        <h1>SETTING Wifi</h1>
        <hr>
        <hr>
        <h5>Isikan SSID dan Pasword dari Akses Poin Anda, IP akan tampil pada Display saat Restart</h5>

        <form>
            <table align="center">
                <tr>
                    <td>
                        Wifi SSID
                    </td>
                    <td>
                        <input id="wifissid" />
                    </td>
                </tr>
                <tr>
                    <td>
                        Wifi Password
                    </td>
                    <td>
                        <input type="wifipassword" id="wifipassword" />
                    </td>
                </tr>
            </table>
            <div>
                <button class="btn info" onClick="setWifi()"> Simpan & Restart </button>
            </div>
        </form>
        <br>
        <hr>
        <br>

        <a style="text-decoration:none" class='button' href="/setdisplay">Display</a>
        <a style="text-decoration:none" class='button' href="/setjws">Jam Sholat</a><br><br><br>
        <a style="text-decoration:none" class='button' href="/">Home</a>
        <br><br>
        <hr>
        <br><br>
        <table align="center">
            <tr>
                <td>
                    <a style="text-decoration:none" href="https://www.youtube.com/hamtronik" class="btn danger"> YOUTUBE </a>
                </td>
                <td>
                    <a style="text-decoration:none" href="https://www.facebook.com/yuliamsyah.adi" class="btn info"> FACEBOOK </a>
                </td>
            </tr>
            <tr>
                <td colspan="2">
                    <br>
                    <a style="text-decoration:none" href="https://www.hamtronik.com" class="btn warning"> HAMTRONIK </a>
                </td>
                <td>
                </td>
            </tr>
        </table>

    </body>

    <script>
        var xmlHttp = createXmlHttpObject();

        function createXmlHttpObject() {
            if (window.XMLHttpRequest) {
                xmlHttp = new XMLHttpRequest();
            } else {
                xmlHttp = new ActiveXObject('Microsoft.XMLHTTP'); // code for IE6, IE5
            }
            return xmlHttp;
        }

        function process() {
            if (xmlHttp.readyState == 0 || xmlHttp.readyState == 4) {
                xmlHttp.open('PUT', 'xml', true);
                xmlHttp.onreadystatechange = handleServerResponse;
                xmlHttp.send(null);
            }

        }

        function handleServerResponse() {
            if (xmlHttp.readyState == 4 && xmlHttp.status == 200) {
                xmlResponse = xmlHttp.responseXML;

                xmldoc = xmlResponse.getElementsByTagName('rWifissid');
                message = xmldoc[0].firstChild.nodeValue;
                document.getElementById('wifissid').value = message;

            }
        }

        function setWifi() {
            console.log("tombol telah ditekan!");

            var wifissid = document.getElementById("wifissid").value;
            var wifipassword = document.getElementById("wifipassword").value;
            var data = {
                wifissid: wifissid,
                wifipassword: wifipassword
            };

            var xhr = new XMLHttpRequest();
            var url = "/settingwifi";

            xhr.onreadystatechange = function() {
                if (this.onreadyState == 4 && this.status == 200) {
                    console.log(xhr.responseText);
                }
            };
            xhr.open("POST", url, true);
            xhr.send(JSON.stringify(data));
        };
    </script>

</html>

)=====";

const char setdisplay[] PROGMEM = R"=====(

<!DOCTYPE HTML>
<html>

<body bgcolor="#DBF8DC">
    <meta name='viewport' content='width=device-width, initial-scale=1'>

    <head>
        <title>Display</title>
        <style>
            body {
                width: 97%;
                text-align: center;
            }

            input,
            select,
            button,
            textarea {
                max-width: 100%;
                margin: 5px;
                padding: 5px;
                border-radius: 7px;
            }

            meter,
            progress,
            output {
                max-width: 100%;
            }

            h1 {
                color: grey;
            }

            .note {
                color: #555;
                font-size: 1em;
            }

            .info {
                background-color: #eee;
                border-radius: 3px;
                padding-top: 17px;
                margin: 5px;
            }

            .tombol {
                background-color: #ccc;
                margin: 20px;
                padding: 10px;
                border-radius: 10px;
                text-decoration: none;
            }

            .button {
                padding: 7px 20px;
                font-size: 18px;
                text-align: center;
                cursor: pointer;
                outline: none;
                color: #fff;
                background-color: #04AA6D;
                border: none;
                border-radius: 15px;
                box-shadow: 0 5px #999;
            }

            .button:hover {
                background-color: #3e8e41
            }

            .button:active {
                background-color: #3e8e41;
                box-shadow: 0 5px #666;
                transform: translateY(4px);
            }

            .btn {
                border: none;
                color: white;
                padding: 7px 20px;
                font-size: 14px;
                cursor: pointer;
                border-radius: 10px;
            }

            .success {
                background-color: #04AA6D;
            }

            /* Green */
            .success:hover {
                background-color: #46a049;
            }

            .info {
                background-color: #2196F3;
            }

            /* Blue */
            .info:hover {
                background: #0b7dda;
            }

            .warning {
                background-color: #ff9800;
            }

            /* Orange */
            .warning:hover {
                background: #e68a00;
            }

            .danger {
                background-color: #f44336;
            }

            /* Red */
            .danger:hover {
                background: #da190b;
            }

            .default {
                background-color: #e7e7e7;
                color: black;
            }

            /* Gray */
            .default:hover {
                background: #ddd;
            }
        </style>
    </head>

    <body onload='process()'>
        <h1>SETT DISPLAY</h1>
        <hr>
        <p>Kercerahan: <span id="demo"> </span> </p>

        <form>
            <label>Redup<input id="cerah" type='range' name='Cerah' min='1' max='250' onchange="setDisp()">Cerah
                <br><br>
                <label for="jpanel">Jumlah Panel</label>
                <input type="number" id="jpanel" min='1' max='4' />
        </form>
        <br>
        <button class="btn info" onClick="setDisp()"> Simpan1 </button><span> </span>
        <br>
        <hr>
        <br>
        <a style="text-decoration:none" class='button' href="/">Home</a>
        <a style="text-decoration:none" class='button' href="/setwifi">Wifi</a>
        <a style="text-decoration:none" class='button' href="/setjws">Jam Sholat</a>
        <br><br>
        <hr>
        <br><br>
        <table align="center">
            <tr>
                <td>
                    <a style="text-decoration:none" href="https://www.youtube.com/hamtronik" class="btn danger"> YOUTUBE </a>
                </td>
                <td>
                    <a style="text-decoration:none" href="https://www.facebook.com/yuliamsyah.adi" class="btn info"> FACEBOOK </a>
                </td>
            </tr>
            <tr>
                <td colspan="2">
                    <br>
                    <a style="text-decoration:none" href="https://www.hamtronik.com" class="btn warning"> HAMTRONIK </a>
                </td>
                <td>
                </td>
            </tr>
        </table>
    </body>

    <script>
        var slider = document.getElementById("cerah");
		var output = document.getElementById("demo");
		output.innerHTML = slider.value;

		slider.oninput = function() {
  		output.innerHTML = this.value;
		}
        
        
        function setDisp() {

            console.log("tombol telah ditekan!");

            var cerah = document.getElementById("cerah").value;
            var jpanel = document.getElementById("jpanel").value;
            var datadisp = {
                cerah: cerah,
                jpanel: jpanel
            };

            var xhr = new XMLHttpRequest();
            var url = "/settingdisp";

            xhr.onreadystatechange = function() {
                if (this.onreadyState == 4 && this.status == 200) {
                    console.log(xhr.responseText);
                }
            };
            xhr.open("POST", url, true);
            xhr.send(JSON.stringify(datadisp));

        }

        var xmlHttp = createXmlHttpObject();

        function createXmlHttpObject() {
            if (window.XMLHttpRequest) {
                xmlHttp = new XMLHttpRequest();
            } else {
                xmlHttp = new ActiveXObject('Microsoft.XMLHTTP'); // code for IE6, IE5
            }
            return xmlHttp;
        }

        function process() {
            if (xmlHttp.readyState == 0 || xmlHttp.readyState == 4) {
                xmlHttp.open('PUT', 'xml', true);
                xmlHttp.onreadystatechange = handleServerResponse;
                xmlHttp.send(null);
            }

        }

        function handleServerResponse() {
            if (xmlHttp.readyState == 4 && xmlHttp.status == 200) {
                xmlResponse = xmlHttp.responseXML;

                xmldoc = xmlResponse.getElementsByTagName('rCerah');
                message = xmldoc[0].firstChild.nodeValue;
                document.getElementById('cerah').value = message;

                xmldoc = xmlResponse.getElementsByTagName('rPanel');
                message = xmldoc[0].firstChild.nodeValue;
                document.getElementById('jpanel').value = message;
            }
        }

    </script>

</html>


)=====";
