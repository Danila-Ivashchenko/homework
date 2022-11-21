const W = 64 // Ширина поля (в клетках)
const H = 36 // Высота поля (в клетках)

/**
 * Прямоугольник на позиции x, y
 * С размерами w, h
 * Обозначаем область в которой будут спавниться враги
 */
const CLOUD_SIZE = { x: W / 4, y: 3, w: W / 2, h: 3 }

let invaders = []

let direction = 1

let timeId

// Индекс игрока внутри поля tiles
let shooterIdx = W * (H - 2) + W / 2
/**
 * Игровое поле размерами W * H
 */
let tiles = []

function createBoard() {
    const grid = document.querySelector('.grid')
    const html = document.querySelector('html')
    // grid.replaceChildren()

    const width = Math.ceil(html.clientWidth / W)
    const height = Math.ceil(html.clientHeight / H)
    const min = Math.min(width, height)
    // Ширина в пикселях одной клетки
    const side = `${min}px`
    
    grid.style.width = `${min * W}px`
    grid.style.height = `${min * H}px`

    for (let i = 0; i < (W * H); i++) {
        const tile = document.createElement('div')
        const row = parseInt(i / W) // y
        const column = parseInt(i % W) // x

        tile.style.width = side
        tile.style.height = side

        if (column >= CLOUD_SIZE.x &&
            column <= CLOUD_SIZE.x + CLOUD_SIZE.w &&
            row >= CLOUD_SIZE.y &&
            row <= CLOUD_SIZE.y + CLOUD_SIZE.h    
        ) {
            tile.classList.add('invader')
            invaders.push(i)
        }

        if (i === shooterIdx) {
            tile.classList.add('shooter')
        }
        tiles.push(tile)
        grid.appendChild(tile)
    }
}

function moveShooter(e){
    tiles[shooterIdx].classList.remove('shooter')
    switch(e.keyCode){
        case 37:
            if (shooterIdx % W > 0){
                shooterIdx--
            }
            break
        case 39:
            if (shooterIdx % W < W - 1){
                shooterIdx++
            }
            break
        case 38:
            if (shooterIdx >= W){
                    shooterIdx -= W
                }
            break
        case 40:
            if (shooterIdx / W < H - 1){
                shooterIdx += W
            }
            break
    }
    tiles[shooterIdx].classList.add('shooter')
}

function shoot(e){
    let bulletId
    let bulletIdx = shooterIdx

    const moveBullet = () => {
        tiles[bulletIdx].classList.remove('bullet')
        bulletIdx -= W
        if (bulletIdx <= 0){
            clearInterval(bulletId)
            return
        }
        tiles[bulletIdx].classList.add('bullet')
        if (tiles[bulletIdx].classList.contains('invader', 'bullet')){
            tiles[bulletIdx].classList.remove('invader')
            tiles[bulletIdx].classList.remove('bullet')
            clearInterval(bulletId)
            
            const index = invaders.indexOf(bulletIdx)
            invaders.splice(index, 1)

            tiles[bulletIdx].classList.add('explosion')
            setTimeout(() => tiles[bulletIdx].classList.remove('explosion'), 256)
        }
    }

    if (e.keyCode === 32){
        console.log('shoot')
        bulletId = setInterval(moveBullet, 100)
    }
}

function moveInvaders(){
    const isLeftEdge = invaders[0] % W <= 0

    let rightIdx = 0

    invaders.forEach(idx => {
        rightIdx = Math.max(rightIdx, idx % W)
    })
    const isRightEdge = rightIdx === W - 1
    if ((isLeftEdge && direction === -1) ||
        (isRightEdge && direction === 1)){
            direction = W
        }
    else if (direction === W){
        if (isLeftEdge){
            direction = 1
        } else {
            direction = -1
        }
    }

    for (let i = 0; i < invaders.length; i++){
        tiles[invaders[i]].classList.remove('invader')
    }
    for (let i = 0; i < invaders.length; i++){
        invaders[i] += direction
    }
    for (let i = 0; i < invaders.length; i++){
        tiles[invaders[i]].classList.add('invader')
    }
}


function start() {
    createBoard()
    document.addEventListener('keydown', moveShooter)
    document.addEventListener('keyup', shoot)
    timeId = setInterval(moveInvaders, 300)
}

document.addEventListener('DOMContentLoaded', start)