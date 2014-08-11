var v_indicador='apagado'; //normal-enf rapido-swing-apagado-temporizador
var v_ventilador='minimo'; //aireacion-maximo-medio-minimo-(MAXIMO -> enf rapido)
var v_temperatura_actual=24; //30-18 (17-16 -> solo en modo calor)      
var v_modo = 'frio';//calor-frio-deshumidicar
var v_swing = 'apagado';
var v_enfriado_rapido = 'apagado';
var v_temporizador = 'apagado';
var mensajeHex='';
var mensajeBin='';
      
function cambiar_modo(){
    if(v_modo=='frio'){
        v_modo = 'deshumidicar';
      }else if(v_modo=='deshumidicar'){
        v_modo = 'calor';
      }else if(v_modo == 'calor'){
        v_modo = 'frio';
      }
	actualizar();
	normal();
}

function encender(){
    console.log('@@encender estado actual',v_indicador);
     var header = str2bin(cabecera());

    var cuarteto1 = '0000';
    var cuarteto2 = '0000';    

    if(v_indicador == 'apagado'  ){
        v_indicador = 'encendido';
    }else{
        v_indicador = 'apagado';
    }
    console.log('@@encender estado actual',v_indicador);
    actualizar();
    
    if(v_indicador=='apagado'){
        var indicador = '1100';
        cuarteto3 = '0101';
        var bitsum = padString(((parseInt(indicador,2)+parseInt(cuarteto1,2)+parseInt(cuarteto2,2)+parseInt(cuarteto3,2))%16).toString(2),'0',4,'left');
        var mensaje = header+indicador+cuarteto1+cuarteto2+cuarteto3+bitsum;
        
        console.log('@@apagar@@',mensaje,parseInt(mensaje,2).toString(16));
		mensajeBin=mensaje;
		mensajeHex=parseInt(mensaje,2).toString(16);
		//procesarComando();
        console.log('@@apagar');
    }else{
        var indicador = '0000';
        
        //var bitsum = padString(((parseInt(indicador,2)+parseInt(cuarteto1,2)+parseInt(cuarteto2,2)+parseInt(cuarteto3,2))%16).toString(2),0,4,'left');
       // var mensaje = header+indicador+cuarteto1+cuarteto2+cuarteto3+bitsum;
        
      //  console.log('prueba=>mensaje',mensaje,'mensajeHex=>',parseInt(mensaje,2).toString(16));
        normal();  
    }

}

function temperatura(accion){
    if(accion=='subir'){
        if(v_temperatura_actual >=30){
            v_temperatura_actual = 30;
        }else{
            v_temperatura_actual++;
        }
    }else if(accion=='bajar'){
        if(v_modo=='frio'){
            if(v_temperatura_actual <= 18){
                v_temperatura_actual = 18;
            }else{
                v_temperatura_actual--;
            }
        }else if(v_modo =='calor'){
            if(v_temperatura_actual <= 16){
                v_temperatura_actual = 16;
            }else{
                v_temperatura_actual--;
            }
        }
    }
    actualizar();
    normal();
}

function enfriado_rapido(){
    if(v_enfriado_rapido=='apagado'){
        v_enfriado_rapido ='encendido';
        v_indicador = 'enf-rap';
    }else{
        v_enfriado_rapido = 'apagado';
        v_indicador ='normal';
    }
    actualizar();
    var header = str2bin(cabecera());
    var indicador = '0001';
    var cuarteto1 = '0000';
    var cuarteto2 = '0000';
    var cuarteto3 = '1000'; //velocidad maxima
    var bitsum = padString(((parseInt(indicador,2)+parseInt(cuarteto1,2)+parseInt(cuarteto2,2)+parseInt(cuarteto3,2))%16).toString(2),'0',4,'left');
    var mensaje = header+indicador+cuarteto1+cuarteto2+cuarteto3+bitsum;
    
    console.log('@@enfriado rapido@@');
    //console.log(mensaje,parseInt(mensaje,2),parseInt(mensaje,2).toString(16));
	mensajeBin=mensaje;
	mensajeHex=parseInt(mensaje,2).toString(16);
}

function swing(){
    if(v_swing=='apagado'){
        v_swing = 'encendido';	
    }else{
        v_swing = 'apagado';
    }
    actualizar();
    var header = str2bin(cabecera());
    var indicador = '0001';
    var cuarteto1 = '0000';
    var cuarteto2 = '0000';
    var cuarteto3 = '0000';
    var bitsum = padString(((parseInt(indicador,2)+parseInt(cuarteto1,2)+parseInt(cuarteto2,2)+parseInt(cuarteto3,2))%16).toString(2),'0',4,'left');
    var mensaje = header+indicador+cuarteto1+cuarteto2+cuarteto3+bitsum;
    console.log('@@swing@@');
    //console.log(mensaje,parseInt(mensaje,2).toString(16));
	mensajeBin=mensaje;
	mensajeHex=parseInt(mensaje,2).toString(16);
}

function actualizar(){
    if(v_indicador == 'apagado'){
        gebi('estado').innerHTML = 'Apagado';
    }else{
        gebi('estado').innerHTML = 'Encendido';
    }
    gebi('ventilador').innerHTML = '<strong>Ventilador</strong> '+v_ventilador;
    gebi('temperatura').innerHTML ='<strong>Temperatura</strong> '+ v_temperatura_actual;
    gebi('modo').innerHTML ='<strong>Modo</strong> '+v_modo;
    gebi('swing').innerHTML ='<strong>Swing</strong> '+v_swing;
    gebi('indicador').innerHTML ='<strong>Indicador</strong> '+v_indicador;
    gebi('temporizador').innerHTML ='<strong>Temporizador</strong> '+v_temporizador;
}

function temporizador(){
    if(v_temporizador=='apagado'){
        v_temporizador = 1;
    }else if(v_temporizador < 7){
        v_temporizador++;
    }else{
        v_temporizador = 'apagado';
    }
    actualizar();
    var header = str2bin(cabecera());
    var indicador = '1010';
    if(v_temporizador=='apagado'){
        var tiempo = padString(0,'0',12,'left');
    }else{
        var tiempo = padString((60*v_temporizador).toString(2),'0',12,'left');
    }
    
    console.log('tiempo',tiempo);
    var cuarteto1 = tiempo.substr(0,4);
    var cuarteto2 = tiempo.substr(4,4);
    var cuarteto3 = tiempo.substr(8,4);
    
    var bitsum = padString(((parseInt(indicador,2)+parseInt(cuarteto1,2)+parseInt(cuarteto2,2)+parseInt(cuarteto3,2))%16).toString(2),'0',4,'left');
    var mensaje = header+indicador+cuarteto1+cuarteto2+cuarteto3+bitsum;
    console.log('@@temporizador@@');
	mensajeBin=mensaje;
	mensajeHex=parseInt(mensaje,2).toString(16);
    //console.log(mensaje,parseInt(mensaje,2).toString(16),v_temporizador);
}



function ventilador(){

if(v_ventilador=='minimo'){
v_ventilador = 'medio';

}else if(v_ventilador == 'medio'){
v_ventilador = 'maximo';
}else if(v_ventilador == 'maximo'){
v_ventilador = 'aireacion';
}else if(v_ventilador == 'aireacion'){
v_ventilador = 'minimo';
}
actualizar();
normal();
}

function gebi(id){
    return document.getElementById(id);
}

function normal(){
	console.log('normal:');
    var header = str2bin(cabecera());
    var indicador= padString('0','0',4,'left');
    var modo=padString('0','0',4,'left');
    if(v_indicador=='encendido'){
        if(v_modo=='frio'||v_modo=='deshumidicar'){
            modo ='0000';
        }else if(v_modo=='calor'){
            modo='0100';
        }
        v_indicador=='normal';
    }else if(v_modo=='frio'){
        modo = '1000';
    }else if(v_modo=='calor'){
        modo = '1100';
    }else if(v_modo=="deshumidicar"){
        modo = '1001';
    }
    var temperatura=padString((v_temperatura_actual-15).toString(2),'0',4,'left');
    var ventilador;
    if(v_ventilador=='maximo'){
        ventilador = '0100';
    }else if(v_ventilador=='medio'){
        ventilador = '0010';
    }else if(v_ventilador=='minimo'){
        ventilador = '0000';
    }else if(v_ventilador=='aireacion'){
        ventilador ='0101';
    }
    var bitsum = padString(((parseInt(indicador,2)+parseInt(modo,2)+parseInt(temperatura,2)+parseInt(ventilador,2))%16).toString(2),'0',4,'left');
    
    var mensaje=header+indicador+modo+temperatura+ventilador+bitsum;
    console.log(mensaje,parseInt(mensaje,2).toString(16));
    mensajeBin=mensaje;
	mensajeHex=parseInt(mensaje,2).toString(16);
    procesarComando();
}

function cabecera(){
    return '88';
}

function str2bin(str){
    var retorno="";
    for(var i=0;i<str.length;i++){
        retorno += parseInt(str[i]).toString(2);
    }
    return padString(retorno,'0',4,'left');
}

function padString(originalString,padChars,desiredLength,direction){
	var pendingLength = desiredLength - originalString.length ;
	if(pendingLength <=0){
		return originalString;
	}else{
		if(direction=='left'){
			return padString(padChars+originalString,padChars,desiredLength,direction);
		}else{
			return padString(originalString+padChars,padChars,desiredLength,direction);
		}
	}
}