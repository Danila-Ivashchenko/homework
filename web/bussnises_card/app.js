
const settings_block = document.querySelector(".settings_block")

let inp_title_company = ""
let inp_p_name = ""
let inp_position = ""
let inp_phone_number = ""
let inp_email = ""
let inp_addres = ""



const card = document.querySelector(".card")

const title_company = card.querySelector(".title_company")
const p_name = card.querySelector(".name")
const position = card.querySelector(".position")
const phone_section = card.querySelector(".phone_section")
const email = card.querySelector(".email")
const addres = card.querySelector(".addres")

function extract_values(){
	inp_title_company = settings_block.querySelector("#inp_title_company").value
	inp_p_name = settings_block.querySelector("#inp_name").value
	inp_position = settings_block.querySelector("#inp_position").value
	// inp_phone_number = settings_block.querySelector("#inp_phone_number").value
	inp_email = settings_block.querySelector("#inp_email").value
	inp_addres = settings_block.querySelector("#inp_addres").value
}

function add_phone(){
	let counter = phone_section.querySelectorAll(".phone_number").length + 1
	if (counter > 3){
		alert("Максимальное количество номером - 3")
		return
	}
	const phone = document.createElement("DIV")
	phone.classList.add("phone_number")
	phone.id = "phone_number_" + counter
	phone_section.appendChild(phone)
	const inp_phone = document.createElement("input")
	inp_phone.id = "inp_phone_number_" + counter
	inp_phone.type = "text"
	settings_block.querySelector(".inp_phone_section").appendChild(inp_phone)
}

function generate(){
	extract_values()
	title_company.innerText = inp_title_company
	p_name.innerText = inp_p_name
	p_name.style.textAlign = document.querySelector('input[name="inp_name_align"]:checked').value
	p_name.style.fontSize = document.querySelector('input[name="inp_name_size"]:checked').value
	position.innerText = inp_position
	position.style.textAlign = document.querySelector('input[name="inp_position_align"]:checked').value
	position.style.fontSize = document.querySelector('input[name="inp_position_size"]:checked').value
	for (let i = 1; i < phone_section.querySelectorAll(".phone_number").length + 1; i++){
		phone_section.querySelector(`#phone_number_${i}`).innerText = settings_block.querySelector(`#inp_phone_number_${i}`).value
	}
	email.innerText = inp_email
	if (document.querySelector('#inp_show_email').checked){
		email.style.display = "block"
	} else {
		email.style.display = "none"
	}
	addres.innerText = inp_addres
	if (document.querySelector('#inp_show_addres').checked){
		email.style.display = "block"
	} else {
		email.style.display = "none"
	}
}