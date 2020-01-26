class TCP_Server
{
	constructor(string_data)
	{
		let arr = string_data.split(",");
		if(!check_server_data(arr, 3)) //3 параметров блока настроек tcp_server без логина и пароля
			return;
		if(arr[0] != "TCP_Server")
		{
			error_server_data();
			return;
		}
		// console.log(arr);
		for(let i = 1; i < arr.length; i++)
		{
			if(getArg(arr[i], 1) === false)
				return;
		}
		
		this.addr=getArg(arr[1], 1);
		this.port=getArg(arr[2], 1);
		this.enable=getArg(arr[3], 1);
	}
	
	debug()
	{
		console.log("TCP_Server");
		console.log("\taddr =", this.addr);
		console.log("\tport =", this.port);
		console.log("\tenable =", this.enable);
	}
}