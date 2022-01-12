// Author: ReXulEc
// Website: rexulec.com

//You can add more files using this method!

const char webpageCode[] =
R"=====(
<!DOCTYPE html>
<html>
<!------------------------------C S S--------------------------------->
<head>
    <style>
        #btn
        {
          display: inline;
          text-decoration: none;
          background: red;
          color:rgba(0, 0, 255, 0.7);
          font: 80px calibri;
          border-radius: 50%;
          box-shadow: 0px 0px 10px 15px #000000;
          border: solid 10px rgba(255, 255, 0, 0.9);
          cursor: pointer;
        }
        body {font-family: "Calibri"; background-color: grey}
        h1   {color: whitesmoke; text-align:center; font-size: 50px;}
    </style>
</head>
<!----------------------------H T M L--------------------------------->
<body>
    <h1>
        ESP8266 Webpage <br> (HTML + CSS + JavaScript) <br><br>
        <a href="#" id="btn" ONCLICK='JS1()'>JS1</a> <br><br>
        <a href="#" id="btn" ONCLICK='JS2()'>JS2</a> <br><br>
        <a href="#" id="btn" ONCLICK='JS3()'>JS3</a>
    </h1>
<!---------------------------JavaScript------------------------------->
<script>
    //function displays text message
    let m1 = 'JavaScript is an object-oriented language'
    let m2 = ' that creates interactive effects within web browsers.'
    let m3 = ' The code syntax of JavaScript is similar to C++.'
    function JS1()
    {
      alert(m1 + m2 + m3);
    }
    //function prompts for name, then displays message
    function JS2()
    {
        let yourName;
        do
        {
            yourName = prompt("Who are you?");
        } while (!yourName);
        alert('Hello ' + yourName);
    }
    //function computes factorial of integer number
    function JS3()
    {
        let f = 1;
        let n = prompt('FACTORIAL\nEnter positive integer number: ');
        for(let i=1; i<=n; i++) f = f * i;
        alert('Factorial = ' + f);
    }   
</script>
</body>
</html>
)=====";
