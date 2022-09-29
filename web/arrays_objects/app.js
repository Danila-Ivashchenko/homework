let arr = ["Ангарск", "Залари", "Иркутск"]

document.write(arr.at(-1), "<br>") //Индексация с конца

arr.push("Москва"); arr[arr.length] = "Владивосток" // Добавление двумя способами

let a = arr.shift() // Удаление и возвращение первого элемента
let b = arr.pop() // Удаление и возвращение последнего элемента массива

document.write(a, "<br>")
document.write(b, "<br>")

let c = arr.unshift("Новосибирск") // Добавление элемента в начало массива, возвращает длину массива с учётом добавдения
let v = arr.push("Красноярск", "Екатеринбург") // Дабавление элементов в конец массива, возвращает длину массива с учётом добавдения

document.write(c, "<br>")
document.write(v, "<br>")

for (const item of arr){    //Ввод всех элементов через for
    document.write(item, "<br>") 
}

for (const item in arr){    //Ввод индексов элементов через for
    document.write(item, "<br>") 
}

//document.write(arr)

const my_name = "Данила"
const key = "name"
let obj = {
    [key] : my_name,
    age : 19
}

console.log(obj)