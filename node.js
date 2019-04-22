var express = require('express');
var app = express();
/*app.get('/', function (req, res) {
  res.send('Hello World!');
});*/
/*app.listen(8080, function () {
  console.log('Example app listening on port 8080!');
});*/

var http = require('http');
var fs = require('fs');
http.createServer(function (req, res) {
  fs.readFile('demofile1.html', function(err, data) {
    res.writeHead(200, {'Content-Type': 'text/html'});
    res.write(data);
    res.end();
  });
}).listen(8080);


const SerialPort = require('serialport');
const Readline = require('@serialport/parser-readline');
const port = new SerialPort('/dev/ttyUSB0', { baudRate: 9600 });
const parser = port.pipe(new Readline({ delimiter: '\n' }));
// Read the port data
port.on("open", () => {
  console.log('serial port open');
});
parser.on('data', data =>{
  fs.appendFile('gelenVeri.txt', data, function (err) {
    if (err) throw err;
    console.log('Saved!');
  });
  console.log('got word from arduino:', data);
});
