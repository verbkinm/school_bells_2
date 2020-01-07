"use strict";

var websocket = null;
var protocol_type = "NONE";			
var session_id = 0;
	
function initWebSocket() 
{
	try 
	{
		if (typeof MozWebSocket == 'function')
			WebSocket = MozWebSocket;
        if ( websocket && websocket.readyState == 1 )
				websocket.close();
        var wsUri = "ws://localhost";
        websocket = new WebSocket( wsUri );
        websocket.onopen = function (evt) 
		{
			console.log("CONNECTED");
        };
        websocket.onclose = function (evt) 
		{
			console.log("DISCONNECTED");	
		};
        websocket.onmessage = function (evt) 
		{
			let data = evt.data;
			// console.log("Received data: " + data);
			if(data == "protocol")
			{
				console.log("Protocol request from server");
				sendProtocol_type(protocol_type);
			}
			if(data.startsWith("monitor_protocol_data"))
			{
				fill_shedule(data);
				addTables();
			}
			if(data.startsWith("manager_protocol_auth"))
			{
				auth();
			}
			if(data.startsWith("manager_protocol_auth_error"))
			{
				error_auth();
			}
			if(data.startsWith("manager_protocol_session_id"))
			{
				session_id = data.split(":")[1];
				// setCookie("session_id", session_id, 7);
				// alert(document.cookie);
				
			}
			if(data.startsWith("manager_protocol_data"))
			{
				main(data);
			}
		};
        websocket.onerror = function (evt) 
		{
			console.log('ERROR: ' + evt.data);
			let body = document.getElementById("body");
			let h1 = document.createElement("H1");
			h1.setAttribute("style", "color: red");	
			body.appendChild(h1);
			h1.innerHTML = "Сервер не доступен";
        };			
    }
	catch (exception) 
	{
		console.log('ERROR: ' + exception);
    }
}

function sendProtocol_type(protocol_type) 
{
	if ( websocket != null )
    {
		websocket.send(protocol_type);
        console.log("Sent to server: " + protocol_type);
    }
}

<!-- function stopWebSocket() { -->
<!-- if (websocket) -->
<!-- websocket.close(); -->
<!-- } -->

<!-- function checkSocket() { -->
<!-- if (websocket != null) { -->
<!-- var stateStr; -->
                    <!-- switch (websocket.readyState) { -->
                        <!-- case 0: { -->
                            <!-- stateStr = "CONNECTING"; -->
                            <!-- break; -->
                        <!-- } -->
                        <!-- case 1: { -->
                            <!-- stateStr = "OPEN"; -->
                            <!-- break; -->
                        <!-- } -->
                        <!-- case 2: { -->
                            <!-- stateStr = "CLOSING"; -->
                            <!-- break; -->
                        <!-- } -->
                        <!-- case 3: { -->
                            <!-- stateStr = "CLOSED"; -->
                            <!-- break; -->
                        <!-- } -->
                        <!-- default: { -->
                            <!-- stateStr = "UNKNOW"; -->
                            <!-- break; -->
                        <!-- } -->
                    <!-- } -->
                    <!-- console.log("WebSocket state = " + websocket.readyState + " ( " + stateStr + " )"); -->
                <!-- } else { -->
                    <!-- console.log("WebSocket is null"); -->
                <!-- } -->
            <!-- } -->
function setCookie(name,value,days) {
    var expires = "";
    if (days) {
        var date = new Date();
        date.setTime(date.getTime() + (days*24*60*60*1000));
        expires = "; expires=" + date.toUTCString();
    }
    document.cookie = name + "=" + (value || "")  + expires + "; path=/";
}
function getCookie(name) {
    var nameEQ = name + "=";
    var ca = document.cookie.split(';');
    for(var i=0;i < ca.length;i++) {
        var c = ca[i];
        while (c.charAt(0)==' ') c = c.substring(1,c.length);
        if (c.indexOf(nameEQ) == 0) return c.substring(nameEQ.length,c.length);
    }
    return null;
}
function eraseCookie(name) {   
    document.cookie = name+'=; Max-Age=-99999999;';  
}
		
