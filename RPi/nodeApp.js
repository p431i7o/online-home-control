var fs=require('fs');
var path = require('path');
var filePath = path.join(__dirname+'/index.html');

fs.readFile(filePath,{encoding:'utf-8'},function(err,data){
  if(!err){
    console.log('datos recibidos' + data);
    response.writeHead(200,{'Content-Type':'text/html'});
    response.write(data);
    response.end();
  }else{
    console.log('err');
    console.log(err);
  }
});
/*
var http = require('http');
var express = require('express');
http.createServer(function(req, res){
	res.writeHead(200,{'Content-Type':'text/plain'});
	res.end('Hola Mundo!\n');
}).listen(80,'10.1.1.100');
console.log('Server running at http://127.0.0.1:1337');
*/