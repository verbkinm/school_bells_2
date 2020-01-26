class General
{
	constructor(string_data)
	{
		let arr = string_data.split(",");
		if(!check_server_data(arr, 8)) //8 параметров блока настроек General
			return;
		if(arr[0] != "General")
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
		
		this.manual_call=getArg(arr[1], 1);
		this.sound_dir_path=getArg(arr[2], 1);
		this.call_before_lesson=getArg(arr[3], 1);
		this.sound_before_lesson=getArg(arr[4], 1);
		this.number_of_minutes_to_call_before_lesson=getArg(arr[5], 1);
		this.programs_before_bell=getArg(arr[6], 1);
		this.programs_after_bell=getArg(arr[7], 1);
	}
	
	debug()
	{
		console.log("Generals:");
		console.log("\tmanualcall =", this.manual_call);
		console.log("\tsound_dir =", this.sound_dir_path);
		console.log("\tcall_before_lesson =", this.call_before_lesson);
		console.log("\tsound_Before_lesson =", this.sound_before_lesson);
		console.log("\tnumber_of_minutes_to_call_before_lesson =", this.number_of_minutes_to_call_before_lesson);
		console.log("\tprograms_before_bell =", this.programs_before_bell);
		console.log("\tprograms_after_bell =", this.programs_after_bell);
	}
}