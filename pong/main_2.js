
const canvas = document.getElementById('canvas')
canvas.width = (window.innerWidth) * 0.9
canvas.height = (window.innerHeight - 200) * 0.9
document.getElementById('canvas').width = canvas.width
document.getElementById('canvas').height = canvas.height
const context = canvas.getContext('2d')
console.log(canvas.height, canvas.width)
const game = new Game(canvas.height, canvas.width)
game.onCreate()

function togleLeftPlayer(){
	leftPlayer = game.isBotLeft ? Player : Bot
	console.log(leftPlayer)
	// game.isBotLeft = game.isBotLeft ? false : true
}

function main(tFrame) {
	requestAnimationFrame(main)
	const nextTick = game.lastTick + Game.TickLength
	let numTicks = 0

	if (tFrame > nextTick) {
		const timeSineTick = tFrame - game.lastTick
		numTicks = Math.floor(timeSineTick / Game.TickLength)
	}
	for (let i = 0; i < numTicks; i++) {
		// В onUpdate lastTick обновляется.
		game.onUpdate(game.lastTick + Game.TickLength)
	}
	game.onRender(context)
	main(performance.now())
}

main(performance.now())

