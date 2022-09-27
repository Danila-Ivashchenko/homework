function nod(num1, num2){
	if (num1 == 0 || num2 == 0){
		return num1 + num2;
	}
	if (num1 > num2)
		return nod(num2, parseInt(num1 % num2));
	else
		return nod(num1, parseInt(num2 % num1));
}

function execute(){
	num1 = parseInt(prompt("Введите первое чилсо"));
	num2 = parseInt(prompt("Введите второе чилсо"));
	
	if (nod(num1, num2) == 1){
		alert("Числа взаимо простые");
	}
	else{
		alert("Числа не взаимо простые");
	}
}

execute()