class TCP_Server
{
	constructor(string_data)
	{
		this.arr = string_data.split(",");
		if(!check_server_data(this.arr, 3)) //3 параметров блока настроек tcp_server без логина и пароля
			return;
		if(this.arr[0] != "TCP_Server")
		{
			error_server_data();
			return;
		}
		// console.log(this.arr);
		for(let i = 1; i < this.arr.length; i++)
		{
			if(getArg(this.arr[i], 1) === false)
				return;
		}
		
		this.addr=getArg(this.arr[1], 1);
		this.port=getArg(this.arr[2], 1);
		this.enable=getArg(this.arr[3], 1);
	}
	
	debug()
	{
		console.log(this.addr);
		console.log(this.port);
		console.log(this.enable);
	}
}