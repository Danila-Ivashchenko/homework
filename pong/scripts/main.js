const canvas = document.getElementById('canvas')
canvas.width = (window.innerWidth) * 0.9
canvas.height = (window.innerHeight - document.querySelector(".header").offsetHeight) * 0.9
document.getElementById('canvas').width = canvas.width
document.getElementById('canvas').height = canvas.height
const context = canvas.getContext('2d')
console.log(canvas.height, canvas.width)
const game = new Game(canvas.height, canvas.width)
game.onCreate();


(() => {

    ;(() => {
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
        }

        main(performance.now())
    })()

 })()

 
 function togleLeftPlayer(who){
	document.activeElement.blur()
	if (who == "left"){
		document.querySelector("#left_ps").innerHTML = game.isBotLeft ? "Игрок" : "Бот"
		game.isBotLeft = game.isBotLeft ? false : true
		game.leftPlatform.velocity = new Vector2()
	}
	if (who == "right"){
		document.querySelector("#right_ps").innerHTML = game.isBotRight ? "Игрок" : "Бот"
		game.isBotRight = game.isBotRight ? false : true
		game.rightPlatform.velocity = new Vector2()
	}
}

function complexity_choose(who, complexity_id){
	game.complexity_choose(who, complexity_id)
}

function ball_speed_choose(complexity_id){
	game.ball_speed_choose(complexity_id)
}
 