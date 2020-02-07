class Shedule
{
	constructor(string_data)
	{
		let arr = string_data.split(",");
		if(!check_server_data(arr, 3)) 
			return;
		if(!arr[0].startsWith("Shedules"))
		{
			error_server_data();
			console.log("data=" + arr);
			return;
		}
		
		this.name = getArg(arr[1], 1);
		this.shifts = [];
		
		let arr_n = string_data.split("\n");
		for(let i = 1;  i < arr_n.length - 1 ; i++) 
		{
			this.shifts.push(new Shift(arr_n[i]));
		}
		
		if(debug)
			this.debug();
	}
	
	debug()
	{
		console.log("\tname =", this.name);
		for(let i = 0;  i < this.shifts.length ; i++) 
		{
			console.log("\t\tSHIFT #", i, ":");
			this.shifts[i].debug();
		}
	}
}