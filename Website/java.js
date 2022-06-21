var last_key = 0;
function changecolor(i){
    document.getElementById(i).style.backgroundColor = "rgb(93, 93, 93)";
};
//change the associated button to the on click color
document.onkeydown = function down(event){
    var key_press = event.keyCode;
    if(key_press == last_key){
    }else if(key_press == 87){
        Fforwards();changecolor("f");
    }else if(key_press == 83){
        Fbackwards();changecolor("b");
    }else if(key_press == 65){
        Fleft();changecolor("l");
    }else if(key_press == 68){
        Fright();changecolor("r");
    }else if(key_press == 81){
        scan();changecolor("s");
    }else if(key_press == 38){
        Sforwards();changecolor("f");
    }else if(key_press == 40){
        Sbackwards();changecolor("b");
    }else if(key_press == 37){
        Sleft();changecolor("l");
    }else if(key_press == 39){
        Sright();changecolor("r");
    }else if(key_press == 69){
        reset();
    }
    last_key = key_press;
};
//Works out what function should run based on the key clicks and makes sure if a key is held
//there is only on output
document.onkeyup = function up(event){
    neutral();
    for (let i = 0; i < 5; i++){
        document.getElementsByClassName("btn")[i].style.backgroundColor = "rgb(54, 54, 54)";
    }
    last_key = 0;
};
//Runs the nuetral function and resets all button colors
