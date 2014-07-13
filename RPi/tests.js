var express = require('express');
var fs=require('fs');
var path = require('path');
var dirname = path.join(__dirname);
var exec = require('child_process').exec;
var app = express();
//var bodyParser = require('body-parser');
var bodyParser  = require('body-parser');
//app.use(bodyParser.json());
app.use(bodyParser.urlencoded({
  extended: true
}));
// simple logger
/*app.use(function(req, res, next){
  console.log('%s %s', req.method, req.url);
  console.log(req);
  next();
});*/
/*var bodyParser = require('body-parser')
app.use( bodyParser.json() );       // to support JSON-encoded bodies
app.use( bodyParser.urlencoded() ); // to support URL-encoded bodies
*/
//app.use(express.json());       // to support JSON-encoded bodies
//app.use(express.urlencoded()); // to support URL-encoded bodies
// respond

app.use(function(req, res, next){
  console.log('%s %s', req.method, req.url);
  //res.send('Hello World');
  fs.readFile(dirname+req.url,{encoding:'utf-8'},function(err,data){
	if(!err){
		res.send(data);
	}else{
		if(req.url=='/'){
			res.status(200).sendfile(dirname+'/index.html');
		}else if(req.url=='/procesarComando'){
			res.set('Content-Type', 'application/json');
			console.log('@@Procesar Comando');
			//console.log(req.body);
			var mensajeBin = req.body.mensajeBin;
			var mensajeHex = req.body.mensajeHex;
			exec('dir '+mensajeHex,function(error,stdout,stderr){
				console.log('stdout: ' + stdout);
				console.log('stderr: ' + stderr);
				if (error !== null) {
				  console.log('exec error: ' + error);
				}
			});
			res.send("{status:'comando procesado',mensajeBin:"+mensajeBin+",mensajeHex:"+mensajeHex+"}");
		}else{
			console.log('#Error Archivo: "'+req.url+'" no existe');
			res.status(404).sendfile(dirname+'/404.html');
		}
	}
  });
  
});


app.listen(1337);
