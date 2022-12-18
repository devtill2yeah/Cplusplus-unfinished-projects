

<style>
* {
margin: 0;
padding: 0;
font-family: 'poppins', sans-serif;
}

Html, body {
display: grid;
height: 100%;
place-items: center;
background: #000000;
}

.wrapper {
height: 350px;
width: 413px;
background: linear-gradient(135deg, #14ffe9, #ffeb3b, #ff00e0);
border-radius: 10px;
animation: animate 1.5s linear infinite;
}

.wrapper .display,
.wrapper span {
position: absolute;
top: 50%;
left: 50%;
transform: translate(-50%, -50%);
}

.wrapper .display {
z-index: 999;
background: #1b1b1b;
height: 85px;
width: 345px;
border-radius: 2px;
text-align: center;
}

.wrapper .display #time {
line-height: 85px;
font-size: 50px;
font-weight: 600px;
letter-spacing: 5px;
background: linear-gradient(135deg, #14ffe9, #ffeb3b, #ff00e0);
-webkit-background-clip: text;
-webkit-text-fill-color: transparent;
animation: animate 1.5s linear infinite;
}

@keyframes animate {
100% {
filter: hue-rotate(360deg);
}
}

.wrapper span {
height: 100%;
width: 100%;
background: inherit;
border-radius: 10px;
}

.wrapper span:last-child {
filter: blur(20px);
</style>
<div class="wrapper">
<div class="display">
<div id="time"></div>
</div>
<span></span>
<span></span>
</div>
<script>
setInterval(()=>{
const time = document.querySelector("#time");
let date = new Date();
let hours = date.getHours();
let minutes = date.getMinutes();
let seconds = date.getSeconds();
let day_night = "AM";
if(hours > 12){
hours = hours - 12;
day_night = "PM";
}
if(hours < 10){
hours = "0" + hours;
}
if(minutes < 10){
minutes = "0" + minutes;
}
if(seconds < 10){
seconds = "0" + seconds;
}
time.textContent = hours +":" + minutes + ":" + seconds + day_night;
});

