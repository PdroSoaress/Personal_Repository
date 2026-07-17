alert("Olá mundo!");

let nome = "Predo";
let idade = 18;

let jogo = "god of war 2018";

const aula = "Introdução a JavaScript";

console.log("Script 100% carregado");

console.log(nome);
console.log(idade);
console.log(`${nome} quer o jogo ${jogo}`);


function mostrarMensagem() {
 let paragrafo = document.getElementById("resultado");
 paragrafo.textContent = "Você clicou no botão!";
}

function cadastrar() {
 let nome = document.getElementById("nome").value;
 let idade = document.getElementById("idade").value;
 let mensagem = `Nome: ${nome} - Idade: ${idade}`;
 document.getElementById("saida").textContent = mensagem;
}