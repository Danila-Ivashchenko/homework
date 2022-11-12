const N_MAX = 12 // Макс. кол-во пар
let SIZE = 12 // <= 24 (N_MAX * 2), кол-во карточек
const score = document.querySelector(".score")

let selected = []
let cards = []

let openedPairs = 0
let clicked = 0

function resize(){
	const input_size = document.getElementById('size')
	let size = parseInt(input_size.value)
	console.log(size)
	if (size > N_MAX){
		alert("Количество пар не должно быть больше 12")
		return
	} else if (size <= 0){
		alert("Количество пар должно быть больше 0")
		return
	}
	SIZE = size * 2
	restart()
}

function shuffle(array) {
	for (let i = array.length - 1; i > 0; i--) {
		const j = Math.floor(Math.random() * (i + 1))
		buf = array[i]
		array[i] = array[j]
		array[j] = buf
	}
	//console.log(array)
}

function generateCards() {
	let indices = Array.from( Array(N_MAX + 1).keys()).slice(1)
	shuffle(indices)
	//console.log(indices)
	const pairs = SIZE / 2
	indices = indices.slice(0, pairs)
	indices = indices.concat(indices)
	shuffle(indices)
	console.log(indices)
	cards = indices
}

function flip() {
	if (selected.length === 2){
		return
	}
	if (this.classList.contains('checking')){
		this.classList.remove('checking')
		this.setAttribute('src', `images/blank.png`)
		selected.pop();
		return
	}
	if (this.classList.contains('checked')){
		return
	}
	clicked += 1
	const cardIdx = this.getAttribute('data-idx')
	this.classList.add('checking')
	selected.push(cardIdx)
	this.setAttribute('src', `./images/${cards[cardIdx]}.png`)
	if (selected.length === 2) {
		setTimeout(check, 500)
	}
}

function victory(){
	let vins = parseInt(score.innerText);
	vins += 1;
	score.innerText = vins
	alert('Поздравляем вы открыли все карточки!!!\nСовершено переворотов ' + clicked)
	console.log(clicked)
	restart()
}

function check() {
	const card1 = document.querySelector(`[data-idx="${selected[0]}"]`)
	const card2 = document.querySelector(`[data-idx="${selected[1]}"]`)
	if (cards[selected[0]] === cards[selected[1]]) {
		card1.classList.add('checked')
		card2.classList.add('checked')
		card1.classList.remove('checking')
		card2.classList.remove('checking')
		openedPairs++
		if (openedPairs === SIZE / 2) {
			victory()
		}
	} else {
		card1.setAttribute('src', './images/blank.png')
		card2.setAttribute('src', './images/blank.png')
		card1.classList.remove('checking')
		card2.classList.remove('checking')
	}
	selected = []
}

function createBoard(grid) {
	if (!grid) return
	for (let i = 0; i < SIZE; i++) {
		const stash = document.createElement('div')
		const card = document.createElement('img')
		card.setAttribute('src', './images/blank.png')
		card.setAttribute('data-idx', i)
		card.addEventListener('click', flip)
		stash.appendChild(card)
		stash.classList.add('stash')
		grid.appendChild(stash)
	}
	generateCards()
}

function start() {
	const grid = document.querySelector('.grid')
	grid.replaceChildren()
	openedPairs = 0
	score.innerText = 0;
	createBoard(grid)
}

function restart(){
	const grid = document.querySelector('.grid')
	grid.replaceChildren()
	openedPairs = 0
	selected = []
	cards = []
	openedPairs = 0
	clicked = 0
	createBoard(grid)
}

start()