class Days
{
	constructor(string_data)
	{
		this.arr = string_data.split(",");
		if(!check_server_data(this.arr, 3)) //3 параметров блока настроек days
			return;
		if(!this.arr[0].startsWith("Days"))
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
		
		this.enable=getArg(this.arr[1], 1);
		this.number_shedule_of_day=getArg(this.arr[2], 1);
	}
	
	debug()
	{
		console.log(this.enable);
		console.log(this.number_shedule_of_day);
	}
}