function User(forename, username, password){
	this.forename = forename
	this.username = username
	this.password = password

	this.showUser = function(){
		document.write("Имя: " + this.forename + "<br>")
		document.write("Пользовательское имя: " + this.username + "<br>")
		document.write("Пароль: " + this.password + "<br>")
	}
}




