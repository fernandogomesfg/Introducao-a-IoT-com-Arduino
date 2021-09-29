const turnON = document.getElementById('turnON');
const turnOFF = document.getElementById('turnOFF');
const lamp = document.getElementById('lamp');

function Lampada_Ligada(){
    lamp.src = 'img/ligada.png'
}

function Lampada_Desligada(){
    lamp.src = 'img/desligada.png'
}


turnON.addEventListener('click', Lampada_Ligada);
turnOFF.addEventListener('click', Lampada_Desligada);
