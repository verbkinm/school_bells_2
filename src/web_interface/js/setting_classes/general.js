class General
{
	constructor(string_data)
	{
		this.arr = string_data.split(",");
		if(!check_server_data(this.arr, 8)) //8 параметров блока настроек General
			return;
		if(this.arr[0] != "General")
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
		
		this.manual_call=getArg(this.arr[1], 1);
		this.sound_dir_path=getArg(this.arr[2], 1);
		this.call_before_lesson=getArg(this.arr[3], 1);
		this.sound_before_lesson=getArg(this.arr[4], 1);
		this.number_of_minutes_to_call_before_lesson=getArg(this.arr[5], 1);
		this.programs_before_bell=getArg(this.arr[6], 1);
		this.programs_after_bell=getArg(this.arr[7], 1);
	}
	
	debug()
	{
		console.log(this.manual_call);
		console.log(this.sound_dir_path);
		console.log(this.call_before_lesson);
		console.log(this.sound_before_lesson);
		console.log(this.number_of_minutes_to_call_before_lesson);
		console.log(this.programs_before_bell);
		console.log(this.programs_after_bell);
	}
}