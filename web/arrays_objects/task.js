let obj = {
    a : 1,
    b : 2,
    c : 3
}

let arr = []

for (i in obj){
    arr.push([i, obj[i]])
}

console.log(arr)