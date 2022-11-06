
let table = document.createElement('table')

let now = new Date()
let month = now.getMonth()
let days = new Date(new Date().getFullYear(), month + 1, 0).getDate()
console.log(month, days)