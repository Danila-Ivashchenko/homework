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

function increment_decrement(arr){
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
			} 
			if (i + 1 < arr.length && typeof arr[i+1] === 'number'){
				arr[i+1]--;
				arr.splice(i, 1);
			}
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
	all = increment_decrement(all);
	alert(all);

}

start()