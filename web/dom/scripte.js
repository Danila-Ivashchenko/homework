let date = new Date()

const selectID = "mySelect"
const inputID = "myInput"

function creatSelect(form){
    const select = document.createElement('select')
    form.appendChild(select)
    select.setAttribute('id', 'mySelect')
    for (let i = 0; i < 12; i++){
        const date = new Date
        date.setMonth(i)
        creatOption(select, date, i)
    }
    
}
function creatInput(form){
    const input = document.createElement('input')
    input.setAttribute('type', 'text')
    input.setAttribute('id', 'myInput')
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


function prosess(){
    const input = document.getElementById(inputID)
    const select = document.getElementById(selectID)

    const day = +input.value
    if (isNaN(day)){
        return 
    }
    const month = +select.value
    let max = new Date(new Date().getFullYear(), month + 1, 0)
    if (day > max){
        return
    }
    
    let isSameYear = false
    const now = new Date()
    if (month === now.getMonth()){
        isSameYear = day > now.getDate()
    } else {
        isSameYear = month > now.getMonth()
    }
    const year = isSameYear ? now.getFullYear() : now.getFullYear() + 1
    const dirthday = new Date(year, month, day)
    const seconds = (dirthday - now) / 1000
    const minutes = parseInt(seconds / 60)
    const hours = parseInt(minutes / 60)
    const days = parseInt(hours / max)

    document.write(days , " " , hours % 24, " ", minutes % 60, " ", seconds % 60, "<br>")
    document.write(now)

}

const form = document.querySelector('form')
const input = document.querySelector('myInput')

creatInput(form)
creatSelect(form)
creatSubmit(form)

//creatSubmit(form)


