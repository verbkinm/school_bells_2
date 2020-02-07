function auth()
{
	session_id = get_cookie("id");
	websocket.send("manager_protocol_session:" + session_id);
	console.log("Send to server: " + "manager_protocol_session:" + session_id);
	
	let form = document.createElement("form");
	form.setAttribute("id", "auth");

	let login = document.createElement("input");
	login.setAttribute("type", "text");
	login.setAttribute("id", "login");

	let passwd = document.createElement("input");
	passwd.setAttribute("type", "password");
	passwd.setAttribute("id", "password");

	let btn = document.createElement("input");
	btn.setAttribute("type", "button");
	btn.setAttribute("id", "button");
	btn.setAttribute("value", "Войти");
	btn.setAttribute("onclick", "submit_auth()");

	form.appendChild(login);
	form.appendChild(passwd);
	form.appendChild(btn);

	let body = document.getElementById("body");
	clear(body);

	body.appendChild(form);
}

function clear(element)
{
	while (element.firstChild)
	{
		element.removeChild(element.firstChild);
	}
}

function error_auth()
{
	auth();
	let body = document.getElementById("body");
	let p = document.createElement("p");
	p.setAttribute("class", "error_msg");
	p.innerHTML = "Неверный логин или пароль!";
	body.appendChild(p);
}

function submit_auth()
{
	let login = document.getElementById("login").value;
	let passwd = document.getElementById("password").value;

	websocket.send("manager_protocol_auth:"+login+"@"+passwd);
	console.log("Send to server: " + "manager_protocol_auth:"+login+"@"+passwd);
}

function check_server_data(arr, length)
{
	if(arr.length < length)
	{
		error_server_data();
		return false;
	}
	return true;
}

function error_server_data()
{
	let body = document.getElementById("body");
	clear(body);
	let p = document.createElement("p");
	p.setAttribute("class", "error_msg");
	p.innerHTML = "Некорректные данные сервера!";
	body.appendChild(p);
}

function getArg(data_string, arg_number)
{
	// console.log(data_string);
	let arr = data_string.split(":=");
	if(arr.length < 1)
	{
		error_server_data();
		return false;
	}

	let result = arr[arg_number];
	if(result.length == 0)
		return "";

	return result;
}

function main_table()
{
	var lesson = new UI_Lesson();
	lesson.number = 1;
	lesson.show();
	lesson.debug();
}

function main(data)
{
	data = data.substring(data.indexOf(":") + 1); //manager_protocol_XXX:
	let arr = data.split(";");
	if(!check_server_data(arr, 10)) //10 параметров минимальное значение для всех настроек
		return;

	let body = document.getElementById("body");
	clear(body);

	var general = new General(arr[0]);
	var tcp_server = new TCP_Server(arr[1]);

	if(debug)
		console.log("Days:");	
	var days = [];
	for(let i = 0; i < 7; i++) //7 - количество дней в седмице
	{
		if(debug)
			console.log("\tday #", i);
		days.push(new Days(arr[i+2]));
	}
	
	var shedules = [];
	if(debug)
		console.log("Shedules:");
	for(let i = 9;  i < arr.length - 1 ; i++) // 9 = general + tcp_server + 7 дней
	{
		shedules.push(new Shedule(arr[i]));
	}
	
	main_table();
}

