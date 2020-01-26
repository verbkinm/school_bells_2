class Days
{
	constructor(string_data)
	{
		let arr = string_data.split(",");
		if(!check_server_data(arr, 3)) //3 параметров блока настроек days
			return;
		if(!arr[0].startsWith("Days"))
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
		
		this.enable=getArg(arr[1], 1);
		this.number_shedule_of_day=getArg(arr[2], 1);
	}
	
	debug()
	{
		console.log("\tenable =", this.enable);
		console.log("\tnumber_shedule_of_day =", this.number_shedule_of_day);
	}
}