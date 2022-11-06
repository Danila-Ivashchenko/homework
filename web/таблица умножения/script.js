function create_table(a, b){
	const table = document.createElement('table');
	document.body.appendChild(table);
	let zero_row = document.createElement('tr')
	let cell = document.createElement('td')
	cell.classList.add('zero_cell')
	zero_row.appendChild(cell)
	for (let j = 0; j < b; j++){
		let cell = document.createElement('td')
		cell.innerText = (j + 1)
		cell.classList.add('zero_cell')
		zero_row.appendChild(cell)
	}
	table.appendChild(zero_row)
	for (let i = 0; i < a; i++){
		let row = document.createElement('tr')
		table.appendChild(row);
		let zero_cell = document.createElement('td')
		zero_cell.classList.add('zero_cell')
		zero_cell.innerText = (i + 1)
		row.appendChild(zero_cell)
		for (let j = 0; j < b; j++){
			let cell = document.createElement('td')
			cell.innerText = (j + 1) * (i + 1)
			row.appendChild(cell)
		}
	}
}


create_table(10, 10)