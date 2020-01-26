class Lesson
{
	constructor(_enable, sound_begin, sound_end, time_begin, time_end)
	{
		this.enable = getArg(_enable, 1);
		this.sound_begin = getArg(sound_begin, 1);
		this.sound_end = getArg(sound_end, 1);
		this.time_begin = getArg(time_begin, 1);
		this.time_end = getArg(time_end, 1);
	}
	
	debug()
	{
		console.log("\t\t\t\t\tenable =", this.enable);
		console.log("\t\t\t\t\tsound_begin =", this.sound_begin);
		console.log("\t\t\t\t\tsound_end =", this.sound_end);
		console.log("\t\t\t\t\ttime_begin =", this.time_begin);
		console.log("\t\t\t\t\ttime_end =", this.time_end);
	}
}
