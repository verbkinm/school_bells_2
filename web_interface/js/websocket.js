"use strict";

var websocket = null;
var protocol_type = "NONE";			
var shedule = new Shedule();
	
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
			if(data == "protocol")
			{
				console.log("Protocol request from server");
				sendProtocol_type(protocol_type);
			}
			if(data.startsWith("monitor_protocol_data"))
			{
				console.log("Received monitor data: " + data);
				fill_shedule(data);
				// shedule.print();
				addTables();
			}
		};
        websocket.onerror = function (evt) 
		{
			console.log('ERROR: ' + evt.data);
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
			
function reading_recieved_data()
{
	
}	
			
			
			
