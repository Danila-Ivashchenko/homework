function func(n) {
	let fact = 1
	let value = 1
	for (let i = 1; i < n + 1; i++){
		value = value * (i + n)
		fact *= i
	}
	return value / fact / (n+1)
}