function is_operator(char_to_check){
	switch(char_to_check){
		case '+':
		case '-':
		case '*':
		case '/':
			return true;
		default:
			return false;
	}
}

function start(){
	var string = prompt ("Введите выражение");
	var operators = new Array();
	var operants = new Array();

	for (let i = 0; i < string.length ; i++){
		if (string[i] >= '0' && string[i] <= '9'){	
			operators.push(parseFloat(string[i]));
		}
		if (is_operator(string[i])){
			operants.push(string[i]);
		}
	}
	alert(operators);
	alert(operants);
	

}

start()