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
const P_ID = "P_ID"

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

function createParagraph() {
    const p = document.createElement('p')
    p.id = P_ID
    p.onmouseover = () => {
        // console.log('1010');
    }
    document.body.appendChild(p)
}

function this_week(weekday_birth, weekday_now){

}

function prosess(){
    const input = document.getElementById(inputID)
    const select = document.getElementById(selectID)

	if (input.value == ""){
		document.getElementById(P_ID).innerHTML = "День не введён"
		return
	}
    const day = +input.value
    if (isNaN(day)){
		document.getElementById(P_ID).innerHTML = "День не введён"
        return 
    }

    const month = +select.value
    let max = new Date(new Date().getFullYear(), month, 0).getDate()
    if (day > max || day < 0 || !Number.isInteger(day)){
		document.getElementById(P_ID).innerHTML = "Некорректно введён день"
        return
    }
    
    let isSameYear = false
    const now = new Date()
	const now_day = now.getDate()
    if (month === now.getMonth()){
        isSameYear = day > now.getDate()
    } else {
        isSameYear = month > now.getMonth()
    }
    const year = isSameYear ? now.getFullYear() : now.getFullYear() + 1
    const birthday = new Date(year, month - 1, day)

    const seconds = (birthday - now) / 1000
    const minutes = parseInt(seconds / 60)
    const hours = parseInt(minutes / 60)
    const days = parseInt(hours / max)

	if (isSameYear){
		if (get_week(birthday) == get_week(now)){
			document.getElementById(P_ID).innerHTML = `Др на этой неделе`
			return
		} else if (get_week(birthday) == get_week(now) + 1) {
			document.getElementById(P_ID).innerHTML = `Др на следующей неделе`
			return
		} else if (birthday.getMonth() == now.getMonth() + 1) {
			document.getElementById(P_ID).innerHTML = `Через месяц`
			return
		} else if (birthday.getMonth() == now.getMonth() + 6) {
			document.getElementById(P_ID).innerHTML = `Через полгода`
			return
		}
	} else {
		if (birthday.getMonth() == (now.getMonth() + 6) % 12){
			document.getElementById(P_ID).innerHTML = `Др через пол года`
			return
		} else {
			document.getElementById(P_ID).innerHTML = `Др через ${birthday.getMonth() + (now.getMonth() + 6) % 12} ${right_month_word(birthday.getMonth() + (now.getMonth() + 6) % 12)}`
			return
		}
	}

	document.getElementById(P_ID).innerHTML = `Осталось до ДР: <b>${days}</b>, ${hours % 24}ч. ${minutes % 60}м. ${seconds % 60}сек.`
}

const form = document.querySelector('form')
const input = document.querySelector('myInput')


creatInput(form)
creatSelect(form)
createParagraph()
//creatSubmit(form)




