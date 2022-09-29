let str = prompt()
let weather = []

let buf = ""

for (let i = 0; i < str.length; i++){
    let char = str[i]
	if (char >= '0' && char <= '9' || char == '.'){	
			buf += char
	} else if (buf != ""){
			weather.push(parseFloat(buf))
			buf = ""
	}
}
weather.push(parseFloat(buf))
/*for (let i = 0; i < weather.length; i++){
    if (i == 0 || i == weather.length - 1){
        new_weather[i] = weather[i]
    } else{
    new_weather[i] = (weather[i-1] + weather[i] + weather[i+1]) / 3
    }
}*/

let new_weather = weather.map((i, idx, arr) => {
    if (idx == 0 || idx == arr.length - 1){
        return i
    } else {
        return (arr[idx - 1] + arr[idx] + arr[idx + 1]) / 3
    }
})

let string = ""
for (const item of new_weather){
    string += item + " "
}

alert(string)
