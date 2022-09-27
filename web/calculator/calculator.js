function is_operator(char_to_check){
	switch(char_to_check){
		case '+':
		case '-':
		case '*':
		case '/':
		case '^':
			return true;
		default:
			return false;
	}
}

function is_double_char_operator(char_to_check){
	switch(char_to_check){
		case '+':
		case '-':
			return true;
		default:
			return false;
	}
}

function increment_decrement_perform(arr){
	for (let i = 0; i < arr.length; i++){
		if (arr[i] == "++"){
			if (arr[i-1] >= 0 && typeof arr[i-1] === 'number'){
				arr[i-1]++;
				arr.splice(i, 1);
				i--;
			} 
			if (i + 1 < arr.length && typeof arr[i+1] === 'number'){
				arr[i+1]++;
				arr.splice(i, 1);
				i--;
			}
		}
		if (arr[i] == "--"){
			if (arr[i-1] >= 0 && typeof arr[i-1] === 'number'){
				arr[i-1]--;
				arr.splice(i, 1);
				i--;
			} 
			if (i + 1 < arr.length && typeof arr[i+1] === 'number'){
				arr[i+1]--;
				arr.splice(i, 1);
				i--;
			}
		}
	}
	return arr;
}

function sqrt_pow_perform(arr){
	for (let i = 0; i < arr.length; i++){
		if (arr[i] == "sqrt"){
			if (i + 1 < arr.length && typeof arr[i+1] === 'number'){
				arr[i+1] = Math.sqrt(arr[i+1]);
				arr.splice(i, 1);
				i--;
			}
			else document.write("Ошибка ", arr[i+1], " Не число<br>");
		}
		if (arr[i] == "^"){
			if (i + 1 < arr.length && i - 1 >= 0 && typeof arr[i+1] === 'number' && typeof arr[i-1] === 'number'){
				arr[i-1] = Math.pow(arr[i-1], arr[i+1]);
				arr.splice(i, 2);
				i--;
			}
			else document.write("Ошибка ", arr[i+1], " Не число<br>");
		}
	}
	return arr;
}

function multi_division_perform(arr){
	for (let i = 0; i < arr.length; i++){
		if (arr[i] == "*"){
			if (i + 1 < arr.length && i - 1 >= 0 && typeof arr[i+1] === 'number' && typeof arr[i-1] === 'number'){
				arr[i-1] *= arr[i+1];
				arr.splice(i, 2);
				i--;
			}
			else document.write("Ошибка ", arr[i+1], " Не число<br>");
		}
		if (arr[i] == "/"){
			if (i + 1 < arr.length && i - 1 >= 0 && typeof arr[i+1] === 'number' && typeof arr[i-1] === 'number'){
				arr[i-1] /= arr[i+1];
				arr.splice(i, 2);
				i--;
			}
			else document.write("Ошибка ", arr[i+1], " Не число<br>");
		}
	}
	return arr;
}

function plus_minus_perform(arr){
	for (let i = 0; i < arr.length; i++){
		if (arr[i] == "+"){
			if (i + 1 < arr.length && i - 1 >= 0 && typeof arr[i+1] === 'number' && typeof arr[i-1] === 'number'){
				arr[i-1] += arr[i+1];
				arr.splice(i, 2);
				i--;
			}
			else document.write("Ошибка ", arr[i+1], " Не число<br>");
		}
		if (arr[i] == "-"){
			if (i + 1 < arr.length && i - 1 >= 0 && typeof arr[i+1] === 'number' && typeof arr[i-1] === 'number'){
				arr[i-1] -= arr[i+1];
				arr.splice(i, 2);
				i--;
			}
			else document.write("Ошибка ", arr[i+1], " Не число<br>");
		}
	}
	return arr;
}

function start(){
	var string = prompt ("Введите выражение");
	var operators = new Array();
	var operants = new Array();
	var all = new Array();
	var buf = "";

	for (let i = 0; i < string.length ; i++){
		let char = string[i];
		if (char >= '0' && char <= '9' || char == '.'){	
			buf += char;
			//operators.push(parseFloat(string[i]));
			
		} else if (buf != ""){
			all.push(parseFloat(buf));
			buf = "";
		}
		if (is_operator(char)){
			if (is_double_char_operator(string[i + 1]) && i + 1 < string.length){
				buf += char + string[i + 1];
				all.push(buf);
				buf = "";
				i++;
			} else {
				operants.push(char);
				all.push(char);
			}
		}
		if (char == "s"){
			buf += char + string[i + 1] + string[i + 2] + string[i + 3];
			all.push(buf);
			buf = "";
			i += 3;
		}
	}
	if (buf != ""){
		all.push(parseFloat(buf));
	}
	all = plus_minus_perform(multi_division_perform(sqrt_pow_perform(increment_decrement_perform(all))));
	alert(all);

}

start()