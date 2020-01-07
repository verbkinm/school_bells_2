class Shift
{
	constructor(string_data)
	{
		this.arr = string_data.split(",");
		if(!check_server_data(this.arr, 3)) 
			return;
		if(!this.arr[0].startsWith("Shedule"))
		{
			error_server_data();
			return;
		}
		// console.log(this.arr);
		// for(let i = 1; i < this.arr.length; i++)
		// {
			// if(getArg(this.arr[i], 1) === false)
				// return;
		// }
		this.name=getArg(this.arr[1], 1);
		
		this.shifts = string_data.substring(this.arr[0].length + this.arr[1].length + 2);
	}
	
	debug()
	{
		console.log(this.name);
		console.log(this.shifts);
	}
}