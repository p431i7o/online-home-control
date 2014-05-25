var http = require('http');
http.createServer(function(req, res){
	res.writeHead(200,{'Content-Type':'text/plain'});
	res.end('Hola Mundo!\n');
}).listen(80,'10.1.1.100');
console.log('Server running at http://127.0.0.1:1337');
