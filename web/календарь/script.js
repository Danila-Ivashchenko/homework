
let table = document.createElement('table')
document.body.appendChild(table)
const arr = new Array("Пн", "Вт", "Ср", "Чт", "Пт", "Сб", "Вс")

let now = new Date()
let month = now.getMonth()

let max_days_this_month = new Date(new Date().getFullYear(), month + 1, 0).getDate()
let max_days_last_month = new Date(new Date().getFullYear(), month, 0).getDate()

console.log(max_days_last_month)

const start_day = ((new Date(new Date().getFullYear(), month, 1)).getDay() + 6) % 7

let th = document.createElement('tr')
for (let j = 0; j < 7; j++){
	const td = document.createElement('td')
	td.innerText = arr[j]
	th.appendChild(td);
}

table.appendChild(th)
let day_insert = 0

for (let i = 0; i < 6; i++){
	const tr = document.createElement('tr')
	table.appendChild(tr);
	for (let j = 0; j < 7; j++){
		const td = document.createElement('td')
		if ((start_day == j || day_insert != 0) && day_insert < max_days_this_month){
			day_insert += 1;
			td.innerText = day_insert
			td.classList.add("this_month")
		} else if (day_insert >= max_days_this_month){
			day_insert += 1;
			td.innerText = day_insert % max_days_this_month
			td.classList.add("other_month")
		} else{
			td.innerText = max_days_last_month - (start_day - j) + 1
			td.classList.add("other_month")
		}
		tr.appendChild(td);
	}
	if (day_insert >= max_days_this_month){
		break
	}
}




