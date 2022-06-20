var xhttp = new XMLHttpRequest();
var miner = new XMLHttpRequest();
xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
        document.getElementById("state").innerHTML = this.responseText;
    }
};
miner.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
        document.getElementById("mineral").innerHTML = this.responseText;
    }
};
function Fright() {xhttp.open("GET", "/fr"); xhttp.send();}
function Fleft() {xhttp.open("GET", "/fl"); xhttp.send();}
function Fforwards(){xhttp.open("GET", "/ff"); xhttp.send();}
function Fbackwards(){xhttp.open("GET", "/fb"); xhttp.send();}
function Sright() {xhttp.open("GET", "/sr"); xhttp.send();}
function Sleft() {xhttp.open("GET", "/sl"); xhttp.send();}
function Sforwards(){xhttp.open("GET", "/sf"); xhttp.send();}
function Sbackwards(){xhttp.open("GET", "/sb"); xhttp.send();}
function neutral(){xhttp.open("GET", "/nu"); xhttp.send();}
function scan(){miner.open("GET", "/s");miner.send();}
<<<<<<< HEAD
//sets up the URI based on the function
=======
//sets up the URI based on the function
>>>>>>> 8269872b63b62b24e2a9df2ed354ec61890fe104
