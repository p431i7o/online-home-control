var http = require('http');
var express = require('express');
var fs=require('fs');
var path = require('path');
var filePath = path.join(__dirname+'/index.html');
var qs = require('querystring');

http.createServer(function(req, response){
  if(req.method=='POST'){
    var body = '';
    req.on('data', function (data) {
	body += data;

	// Too much POST data, kill the connection!
	if (body.length > 1e6)
	    req.connection.destroy();
    });
    req.on('end', function () {
    	var post = qs.parse(body);
    	console.log('POST recibido');
    	console.log(post);
    });
  }else{
    
    fs.readFile(filePath,{encoding:'utf-8'},function(err,data){
      if(!err){
    //    console.log('datos recibidos' + data);
	console.log('llamada recibida');
    //    console.log(req);
	response.writeHead(200,{'Content-Type':'text/html'});
	response.write(data);
	response.end();
      }else{
	console.log('err');
	console.log(err);
      }
    });
  }//else post
}).listen(80,'10.1.1.100');
console.log('Server running at http://10.1.1.100:80');
