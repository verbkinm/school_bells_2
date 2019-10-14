class Lesson
{
	constructor(begin_time, end_time)
	{
		this.begin = begin_time;
		this.end = end_time;
	}

	print()
	{
		console.log(this.begin + " - " + this.end);
	}
}		
class Shift
{
	constructor(number_of_shift, number_of_first_lesson, lessons)
	{
		this.number = number_of_shift;
		this.start_lesson = number_of_first_lesson;
		this.lesson_array = lessons;
	}

	print()
	{
		console.log("№ Смены:" + this.number);
		console.log("Номер первого урока: " + this.start_lesson);
		console.log("Список уроков:");	
		this.lesson_array.forEach(function(lesson, i, arr) 	
		{
			lesson.print();
		});
	}
}

class Shedule
{
	constructor()
	{
		this.shifts_array = new Array();	
	}

	print()
	{
		this.shifts_array.forEach(function(shift, shift_number, arr) 	
		{
			// console.log(shift);
			shift.print();
		});
	}
}

function fill_shedule(data)
{
	let data_without_protocol = data.slice(data.indexOf(",")+1);
	let shift_data = data_without_protocol.split(";");
	for(let shift_number = 0; shift_number < shift_data.length-1; ++shift_number)
	{
		let array_data = shift_data[shift_number].split(",");
		let lessons = [];
		for(let lesson_number = 2; lesson_number < array_data.length - 1; lesson_number+=2)
		{
			let lesson = new Lesson(array_data[lesson_number], array_data[lesson_number+1]);
			lessons.push(lesson);
		}
		let shift = new Shift(array_data[0], array_data[1], lessons);
		shedule.shifts_array.push(shift);
	}
}
function addTable(shift, shift_number)
{
	let tbody = document.getElementById("body");
	let table = document.createElement("TABLE");
	
	let caption = document.createElement("caption");
	table.appendChild(caption);
	
	caption.innerHTML = "Смена №" + ++shift_number;
	
	tbody.appendChild(table);
	
	addRow(table, "№ урока", "начало урока", "окончание урока");

	
	shift.lesson_array.forEach(function(lesson, lesson_number, arr) 	
	{
		addRow(table, Number(lesson_number)+Number(shift.start_lesson), lesson.begin, lesson.end);
	});
}
function addTables()
{
	shedule.print();
	shedule.shifts_array.forEach(function(shift, shift_number, arr) 	
	{
		addTable(shift, shift_number);
	});
}

function addRow(table, number, begin, end)
{
	let row = document.createElement("TR");
	table.appendChild(row);

	let td1 = document.createElement("TD");
	let td2 = document.createElement("TD");
	let td3 = document.createElement("TD");

	row.appendChild(td1);
	row.appendChild(td2);
	row.appendChild(td3);

	td1.innerHTML = number;
	td2.innerHTML = begin;
	td3.innerHTML = end;
}