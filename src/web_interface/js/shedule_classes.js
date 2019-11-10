class Lesson
{
    constructor(begin_time, end_time)
    {
        this.begin = begin_time;
        this.end = end_time;
        this.begin_in_minutes = Number(this.begin.split(":")[0]) * 60 + Number(this.begin.split(":")[1])
        this.end_in_minutes = Number(this.end.split(":")[0]) * 60 + Number(this.end.split(":")[1])
	}

	print()
    {
        console.log(this.begin + "(" + this.minutes(this.begin_in_minutes) + ") - " + this.end + "(" + this.minutes(this.end_in_minutes) + ")");
	}
	
	minutes(value)
	{
		if(isNaN(value))
			return "Урок выключен";
		else
			return value;
	}
	
	time_in_lesson(time_in_minutes)
	{
		if( 
            ((time_in_minutes > this.begin_in_minutes || time_in_minutes === this.begin_in_minutes) && time_in_minutes < this.end_in_minutes)
			||
            ((time_in_minutes < this.end_in_minutes || time_in_minutes === this.end_in_minutes) && time_in_minutes > this.begin_in_minutes)
		)
			return true;
		else
			return false;
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
        this.shifts_array = [];
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

function current_timer()
{
	let current_date = new Date();
	let current_time_in_minutes = current_date.getHours() + current_date.getMinutes();
	let timer_body = document.getElementById("timer");
	let options = {
		hour: 'numeric',
		minute: 'numeric',
		second: 'numeric'
	};
	timer_body.innerHTML = "Текущее время: " + current_date.toLocaleString("ru", options);
}
function twoDigit(digit)
{
	if(digit < 10)
		return "0" + digit;
	return digit;
}
function time_less(shift_number, shift, html_block)
{
	let current_date = new Date();
	let current_time_in_minute = current_date.getHours() * 60 + current_date.getMinutes();
	let current_time_in_seconds = current_date.getHours() * 3600 + current_date.getMinutes() * 60 + current_date.getSeconds();
	
	let found = false;
	shift.lesson_array.forEach(function(lesson, lesson_number) 	
	{
		if(found)
			return;
		
		if(lesson.time_in_lesson(Math.floor(current_time_in_seconds/60)))
		{
			let difference_in_second = lesson.end_in_minutes * 60 - current_time_in_seconds;
			let h = Math.floor(difference_in_second / 3600);
			let m = Math.floor((difference_in_second - h*3600) / 60);
			let s = difference_in_second - h * 3600 - m * 60;
			let result = twoDigit(h) + ":" + twoDigit(m) + ":" + twoDigit(s);			
			html_block.innerHTML = "До конца урока №" + Number(Number(lesson_number) + Number(shift.start_lesson)) + " осталось " + result;;
/* 			let table = document.getElementById("table" + shift_number);
			console.log(table.innerHTML ); */
			//let cell = table.row[lesson_number].cell[0];
			//cell.setAttribute("id", "current_lesson");
			found = true;
		}
        else if(lesson.begin !== "-- : --" && current_time_in_minute < lesson.begin_in_minutes)
		{
			let difference_in_second = lesson.begin_in_minutes * 60 - current_time_in_seconds;
			let h = Math.floor(difference_in_second / 3600);
			let m = Math.floor((difference_in_second - h*3600) / 60);
			let s = difference_in_second - h * 3600 - m * 60;
			let result = twoDigit(h) + ":" + twoDigit(m) + ":" + twoDigit(s);
			html_block.innerHTML = "До начала урока №" + Number(Number(lesson_number) + Number(shift.start_lesson)) + " осталось " + result;
			found = true;
        }
    });

    if(!found)
    {
        let first_enabled_lesson;

        shift.lesson_array.forEach(function(lesson, lesson_number)
        {
            if(lesson.begin !== " -- : --")
                first_enabled_lesson = lesson_number;
        });

        let difference_in_second = 24 * 3600 + shift.lesson_array[first_enabled_lesson].begin_in_minutes * 60 - current_time_in_seconds;
        let h = Math.floor(difference_in_second / 3600);
        let m = Math.floor((difference_in_second - h*3600) / 60);
        let s = difference_in_second - h * 3600 - m * 60;
        let result = twoDigit(h) + ":" + twoDigit(m) + ":" + twoDigit(s);
        html_block.innerHTML = "До начала урока №" + Number(Number(first_enabled_lesson) + Number(shift.start_lesson)) + " осталось " + result;
    }
}
function addTable(shift, shift_number)
{
	let body = document.getElementById("body");
	let table = document.createElement("TABLE");
	table.setAttribute("id", "table" + shift_number);
	
	let caption = document.createElement("caption");
	table.appendChild(caption);
    ++shift_number;
    caption.innerHTML = "Смена №" + shift_number;
	
	body.appendChild(table);
	
	addThead(table);
	
	shift.lesson_array.forEach(function(lesson, lesson_number) 	
	{
		addRow(table, Number(lesson_number)+Number(shift.start_lesson), lesson.begin, lesson.end);
	});
	
	let tfoot = document.createElement("tfoot");
	tfoot.setAttribute("id", "tfoot"+shift_number);
	table.appendChild(tfoot);
	let tr = document.createElement("tr");
	tfoot.appendChild(tr);
	let td = document.createElement("td");
	td.setAttribute("colspan", 3);
	tr.appendChild(td);
	
	time_less(shift_number, shift, td);
	setInterval(time_less, 1000, shift_number, shift, td);
}
function addTables()
{
	shedule.print();
	
	let current_date = new Date();
	let current_time_in_minutes = current_date.getHours() * 60 + current_date.getMinutes();
	console.log(current_time_in_minutes);

	shedule.shifts_array.forEach(function(shift, shift_number) 	
	{
		addTable(shift, shift_number);
	});
	
	current_timer();
	setInterval(current_timer, 1000);
}

function addThead(table)
{
	let row = document.createElement("THEAD");
	table.appendChild(row);

	let td1 = document.createElement("TD");
	let td2 = document.createElement("TD");
	let td3 = document.createElement("TD");

	row.appendChild(td1);
	row.appendChild(td2);
	row.appendChild(td3);

	td1.innerHTML = "№ <br>урока";
	td2.innerHTML = "начало урока";
	td3.innerHTML = "окончание урока";
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
