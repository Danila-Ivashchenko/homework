let ROW_NUM = 10
let COL_NUM = 10
let BOMB_NUM = 10

function resize(){
	const rows = document.querySelector('#row_num').value
	const cols = document.querySelector('#col_num').value
	const bombs = document.querySelector('#bomb_num').value
	if (rows < 2 ){
		alert ('Количество рядов меньше 2')
		return
	} else if (cols < 2){
		alert ('Количество колонок меньше 2')
		return
	} else if (bombs >= rows * cols){
		alert ('Количесиво бомб слишком велико')
		return
	}
	if (rows > 20 ){
		alert ('Количество рядов слишком большое')
		return
	} else if (cols > 20){
		alert ('Количество колонок слишком большое')
		return
	} else if (bombs < 1){
		alert ('Бомб слишком мало')
	}
	ROW_NUM = rows
	COL_NUM = cols
	BOMB_NUM = bombs

	restart()
}

function compareNumeric(a, b) {
	if (a > b) return 1;
	if (a == b) return 0;
	if (a < b) return -1;
  }

//const field = document.createElement('div')
const field = document.querySelector('.field')
field.classList.add('field')
const bomb_display = document.querySelector('.bomb_display')

document.body.appendChild(field)

let set_cells = []
let real_cells = []
let bombs_positions = []
let defused_cells = []

function get_randomInt(max) {
	return Math.floor(Math.random() * max);
}

function generate_bombs(count, field_size){
	let positions = []
	for (let i = 0; i < field_size; i++)
		positions.push(i)
	//console.log(positions)
	let len = field_size - 1
	while (count){
		let rand_pos = get_randomInt(len)
		//console.log(rand_pos)
		//console.log(count, len)
		bombs_positions.push(positions[rand_pos])
		let buf = positions[rand_pos]
		positions[rand_pos] = positions[len]
		positions[len] = buf
		//console.log(positions)
		//bombs_positions.push(rand_pos)
		count -= 1
		len -= 1
		//console.log(bombs_positions)
	}
}

field.addEventListener('contextmenu', (e) => {
	e.preventDefault()
	if (e.target.tagName != 'DIV') return
	let target = e.target
	if (target.classList.contains('Opened')) return
	let i = parseInt(target.getAttribute('i'))
	let j = parseInt(target.getAttribute('j'))
	if (target.classList.contains('Defused')){
		target.classList.remove('Defused')
		defused_cells.splice(defused_cells.indexOf(i * (COL_NUM) + j), 1)
		if (defused_cells.length < 10) bomb_display.innerText = parseInt(bomb_display.innerText) + 1
	} else{
		target.classList.add('Defused')
		defused_cells.push(i * COL_NUM + j)
		if (parseInt(bomb_display.innerText) != 0) bomb_display.innerText = parseInt(bomb_display.innerText) - 1
	}

	// bombs_positions.sort(compareNumeric)
	// defused_cells.sort(compareNumeric)
	// console.log(bombs_positions, defused_cells)
	if (bombs_positions.length == defused_cells.length)
		check_end()
}, false)

function check_end(){
	//console.log('sds')
	bombs_positions.sort(compareNumeric)
	defused_cells.sort(compareNumeric)
	//console.log(bombs_positions, defused_cells)

	for (let i = 0; i < BOMB_NUM; i++){
		if (bombs_positions[i] != defused_cells[i]){
			//console.log(bombs_positions[i], defused_cells[i])
			return false
		}
	}
	for (let i = 0; i < ROW_NUM; i++){
		for (let j = 0; j < COL_NUM; j++){
			let cell = document.querySelector(`[i="${i}"][j="${j}"]`)
			if (cell.classList.contains('Defused') && bombs_positions.indexOf(j + i * COL_NUM) == -1){
				//console.log(cell, bombs_positions.indexOf(j + i * COL_NUM))
				return false
			}
			if (cell.innerHTML == "" && !cell.classList.contains('Defused')){
				//console.log(cell, 'ыы')
				return false
			}
		}
	}
	//restart()
	show_bombs()
	alert('Победа')
}

function show_bombs(){
	for (let i = 0; i < ROW_NUM; i++){
		for (let j = 0; j < COL_NUM; j++){
			let cell = document.querySelector(`[i="${i}"][j="${j}"]`)
			if (bombs_positions.indexOf(i * COL_NUM + j) != -1){
				cell.classList.add('bomb')
				console.log(cell)
				if (cell.classList.contains('Defused')) cell.classList.remove('Defused')
			} else {
				if (cell.classList.contains('Defused')){
					cell.classList.remove('Defused')
					cell.classList.add('Bad_defused')
				}
			}
		}
	}
}

field.addEventListener('click', function(e){
	if (e.target.tagName != 'DIV') return
	let target = e.target
	if (target.classList.contains('Defused')){
		return
	}
	let i = parseInt(target.getAttribute('i'))
	let j = parseInt(target.getAttribute('j'))
	//console.log(i, j, target)
	open_cell(i, j)
	if (bombs_positions.length == defused_cells.length)
		check_end()
})

function open_cell(i, j){
	//console.log(i, j)
	let target = document.querySelector(`[i="${i}"][j="${j}"]`)
	if (target.classList.contains('Opened')) return
	if (set_cells[i][j] == '*'){
		target.classList.add('boom')
		show_bombs()
		//restart()
	}
	target.innerHTML = '<span>' + set_cells[i][j] + '</span>'
	target.classList.add('Opened')

	if (set_cells[i][j] == 0){
		if (i > 0){
			open_cell(i - 1, j)
		}
		if (i < ROW_NUM - 1){
			open_cell(i + 1, j)
		}
		if (j > 0){
			open_cell(i, j - 1)
		}

		if (j < COL_NUM - 1){
			open_cell(i, j + 1)
		}

		if (i > 0 && j > 0){
			open_cell(i - 1, j - 1)
		}

		if (i > 0 && j < COL_NUM - 1){
			open_cell(i - 1, j + 1)
		}

		if (i < ROW_NUM - 1 && j > 0){
			open_cell(i + 1, j - 1)
		}

		if (i < ROW_NUM - 1 > 0 && j < COL_NUM - 1){
			open_cell(i + 1, j + 1)
		}
	}
}

function define_cells(row_num, col_num){
	for (let i = 0; i < row_num; i++){
		for (let j = 0; j < col_num; j++){
			//console.log(set_cells[i][j])
			if (set_cells[i][j] == 0){
				//console.log(set_cells)
				if (i > 0) 
					if (set_cells[i - 1][j] == '*')
						set_cells[i][j] += 1
				if (i < row_num - 1)
					if (set_cells[i + 1][j] == '*')
						set_cells[i][j] += 1
				if (j > 0)
					if (set_cells[i][j - 1] == '*')
						set_cells[i][j] += 1
				if (j < col_num - 1)
					if (set_cells[i][j + 1] == '*')
						set_cells[i][j] += 1
				if (i > 0 && j > 0)
					if (set_cells[i - 1][j - 1] == '*')
						set_cells[i][j] += 1
				if (i > 0 && j < col_num - 1)
					if (set_cells[i - 1][j + 1] == '*')
						set_cells[i][j] += 1
				if (i < row_num - 1 && j > 0)
					if (set_cells[i + 1][j - 1] == '*')
							set_cells[i][j] += 1
				if (i < row_num - 1 > 0 && j < col_num - 1)
					if (set_cells[i + 1][j + 1] == '*')
						set_cells[i][j] += 1
			}
			//if (set_cells[i][j] != '*')
			//real_cells[i][j].innerHTML = '<span>' + set_cells[i][j] + '</span>'
		}
	}
	//console.log(set_cells)
}

function fill_field(row_num, col_num, bombs){
	generate_bombs(bombs, row_num * col_num)
	//console.log(bombs_positions)
	let counter = 0
	for (let i = 0; i < row_num; i++){
		let buf = []
		//let bufr = []
		for (let j = 0; j < col_num; j++){
			let pos = -1
			const cell = document.createElement('div')
			cell.classList.add('cell')
			if (bombs_positions.indexOf(j + i * COL_NUM, 0) >= 0){
				//cell.classList.add('bomb')
				buf[j] = '*'
			} else {
				buf[j] = 0
			}
			cell.setAttribute('i', i)
			cell.setAttribute('j', j)
			//cell.addEventListener('click', open_cell())
			field.appendChild(cell)
			//bufr.push(cell)
			counter += 1
		}
		set_cells.push(buf)
		//real_cells.push(bufr)
	}
	define_cells(row_num, col_num)
	//console.log(set_cells)
	//console.log(real_cells)
	field.style.height = `${row_num * 50}px`
	field.style.width = `${col_num * 50}px`
}


function start(){
	fill_field(ROW_NUM, COL_NUM, BOMB_NUM)
	bomb_display.innerText = BOMB_NUM
}

function restart(){
	field.replaceChildren()
	set_cells = []
	real_cells = []
	bombs_positions = []
	defused_cells = []
	start()
}

start()