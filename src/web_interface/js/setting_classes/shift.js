class Shift
{
	constructor(string_data)
	{
		// console.log(string_data);
		let arr = string_data.split(",");
		if(!check_server_data(arr, 7)) 
			return;
		if(!arr[0].startsWith("shift"))
		{
			error_server_data();
			console.log("data=" + arr);
			return;
		}
		
		this.enable = getArg(arr[0], 1);
		this.start_number_of_lesson = getArg(arr[1], 1);

		this.lessons = [];
		
		if( ((arr.length - 2 - 1) % 5) != 0) // 2-а первые параметра - это относиться к классу Shedule и последний - пустой
		{
			error_server_data();
			console.log("data=" + arr);
			return;
		}
		let number_of_lessons = (arr.length - 2 - 1) / 5; 
		
		let new_arr = arr.slice(2, -1);
		// console.log(new_arr);
		
		let current_pos = 0;
		for(let i = 0;  i < number_of_lessons; i++) 
		{
			this.lessons.push(new Lesson(new_arr[0], new_arr[1], new_arr[2], new_arr[3], new_arr[4]));		
			new_arr = new_arr.slice(5);
		}
	}
	
	debug()
	{
		console.log("\t\t\tshift enable = ", this.enable);
		console.log("\t\t\tshift_start_number_of_lesson = ", this.start_number_of_lesson);
		for(let i = 0;  i < this.lessons.length; i++) 
		{
			console.log("\t\t\t\tlesson #", i + Number(this.start_number_of_lesson), ":");
			this.lessons[i].debug();
		}
	}
}
