let date = new Date()

function daysInMonth(date){
	const month = date.getMonth()
	if (date.getMonth() == 0){
		return date.getDate()
	}
	let days = 31 + date.getDate()
	for (let i = 1; i < month; i++){
		let buf_day = new Date(date.getFullYear(), i + 1, 0)
		days += buf_day.getDate()
	}
	return days
}

const selectID = "mySelect"
const inputID = "myInput"
const infoP = "infoP"
const subinfoP = "subinfoP"

function creatSelect(form){
	const select = document.createElement('select')
	form.appendChild(select)
	select.setAttribute('id', 'mySelect')
	select.onchange = prosess
	for (let i = 0; i < 12; i++){
		const date = new Date
		date.setMonth(i)
		creatOption(select, date, i)
	}
}

function get_week(date){
	const first_january = new Date(date.getFullYear(), 0, 1)
	return Math.ceil(((daysInMonth(date) - (7 - (first_january.getDay() + 6) % 7)) / 7))
}

function right_month_word(n){
	switch (n){
		case 1:
			return ""
		case 2:
		case 3:
		case 4:
			return "месяца"
		default:
			return "месяцев"
	}
}

function right_day_word(n){
	switch (n % 10){
		case 1:
			return "день"
		case 2:
		case 3:
		case 4:
			return "дня"
		default:
			return "ней"
	}
}

function creatInput(form){
	const input = document.createElement('input')
	input.setAttribute('type', 'text')
	input.setAttribute('id', 'myInput')
	input.onblur = prosess
	form.appendChild(input)
}
function creatOption(select, month, value){
	const option = document.createElement('option')
	option.text = month.toLocaleString("ru-Ru",{ month: 'long'})
	option.setAttribute('value', value + 1)
	select.appendChild(option)
}
function creatSubmit(form){
	const submit = document.createElement('input')
	submit.setAttribute('type', 'submit')
	submit.setAttribute('value', "Расчитать")
	form.appendChild(submit)
}

function createParagraph(id, class_name) {
	const p = document.createElement('p')
	p.classList.add(class_name)
	p.id = id
	if (id == infoP){
		mouseEvents(p)
	}
	document.body.appendChild(p)
}

function mouseEvents(p){
	p.onmouseover = function(e) {
		document.getElementById(subinfoP).style.display = "block"
	
	}
	p.onmouseout = function(e) {
		document.getElementById(subinfoP).style.display = ""
	}
}

function this_week(weekday_birth, weekday_now){

}

function prosess(){
	const input = document.getElementById(inputID)
	const select = document.getElementById(selectID)

	if (document.getElementById(infoP) == null){
		createParagraph(infoP, "info")
	}

	if (input.value == ""){
		document.getElementById(infoP).innerHTML = "День не введён"
		return
	}
	const day = +input.value
	if (isNaN(day)){
		document.getElementById(infoP).innerHTML = "День не введён"
		if (document.getElementById(subinfoP) != null){
			document.getElementById(subinfoP).remove()
		}
		return 
	}

	const month = +select.value
	let max = new Date(new Date().getFullYear(), month, 0).getDate()
	if (day > max || day < 0 || !Number.isInteger(day)){
		document.getElementById(infoP).innerHTML = "Некорректно введён день"
		if (document.getElementById(subinfoP) != null){
			document.getElementById(subinfoP).remove()
		}
		return
	}
	
	if (document.getElementById(subinfoP) == null){
		createParagraph(subinfoP, "sub_info")
	}

	let isSameYear = false
	const now = new Date()
	const now_day = now.getDate()
	if (month - 1 === now.getMonth()){
		isSameYear = day >= now.getDate()
	} else {
		isSameYear = month > now.getMonth()
	}
	const year = isSameYear ? now.getFullYear() : now.getFullYear() + 1
	const birthday = new Date(year, month - 1, day)

	const seconds = parseInt((birthday - now) / 1000)
	const minutes = parseInt(seconds / 60)
	const hours = parseInt(minutes / 60)
	const days = parseInt(hours / 24)

	let mess = ""
	if (isSameYear && birthday.getMonth() == now.getMonth() && birthday.getDate() == now.getDate()){
		mess = "День Рождения сегодня!!!"
		document.getElementById(infoP).innerHTML = mess
		document.getElementById(subinfoP).remove()
		return
	} else if (isSameYear){
		if (birthday.getMonth() == now.getMonth() && birthday.getDate() == now.getDate() + 1){
			mess = `Др завтра!`
		} else if (get_week(birthday) == get_week(now)){
			mess = `Др на этой неделе`
		} else if (get_week(birthday) == get_week(now) + 1) {
			mess = `Др на следующей неделе`
		} else if (birthday.getMonth() == now.getMonth()){
			mess = `Др через ${birthday.getDate() - now.getDate()} ${right_day_word(birthday.getDate() - now.getDate())}`
		} else if (birthday.getMonth() == now.getMonth() + 6) {
			mess = `Через полгода`
		}
	} else {
		if (birthday.getMonth() == now.getMonth()){
			mess = `Др через год`
		} else if (birthday.getMonth() == (now.getMonth() + 6) % 12){
			mess = `Др через пол года`
		} else if (birthday.getMonth() == (now.getMonth() + 1) % 12) {
			mess = `Через месяц`
		} else {
			mess = `Др через ${(birthday.getMonth() + 1) + (now.getMonth() + 1) % 12} ${right_month_word((birthday.getMonth() + 1) + (now.getMonth() + 1) % 12)}`
		}
	}
	document.getElementById(subinfoP).innerHTML = `Осталось до Дня Рождения: <b>${days != 0 ? days + 'д, ' : ''}</b> ${hours != 0 || days != 0 ? hours % 24 + 'ч.' : ''} ${minutes % 60}м. ${seconds % 60}сек.`
	document.getElementById(infoP).innerHTML = mess
}

const form = document.querySelector('form')

creatInput(form)
creatSelect(form)

const input = document.querySelector('myInput')

//creatSubmit(form)




