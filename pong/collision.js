class Game {
    checkCollisions() {
        const isRightField = this.ball.position.x > innerWidth / 2
        let pX // Platform X
        let pY // Platform Y
        let bXo // Ball x offset
        if (isRightField) {
            pX = this.rightPlatform.position.x
            pY = this.rightPlatform.position.y
            bXo = Ball.R
        } else {
            pX = this.leftPlatform.position.x + Platform.W
            pY = this.leftPlatform.position.y
            bXo = -Ball.R
        }
        const triggerWidth = 10
        let isInTrigger

        const bX = this.ball.position.x + bXo
        const bY = this.ball.position.y
        if (isRightField) {
            isInTrigger = bX >= pX && bX <= pX + triggerWidth
        } else {
            isInTrigger = bX <= pX && bX >= pX - triggerWidth
        }
        if (isInTrigger && bY >= pY && bY <= pY + Platform.H) {
            // В зоне действия триггера платформы
            this.ball.velocity.x *= -1
        }
    }
}
