var select = document.getElementById("buyitens");
var botao_incluir = document.getElementById("include");
var botao_excluir = document.getElementById("remove-buy");
var data_input = document.getElementById("date");

//botao_incluir.disabled = true;

//criando objeto cotacao
var Cotacao = function(data, cotacaoVenda, cotacaoCompra) {
  this.data = data;
  this.cotacaoVenda = cotacaoVenda;
  this.cotacaoCompra = cotacaoCompra;
}


Cotacao.prototype.appendCotacao = function(){

	//populando a lista de data e cotacao com os dados
    option = document.createElement("option");

    dataSpan = document.createElement("span");
    dataSpan.textContent = this.data.getDate() + "/" + (this.data.getMonth()+1) + 
    		"/" + this.data.getFullYear() +"; ";
    option.appendChild(dataSpan);

    cotacaoCompraSpan = document.createElement("span");
    cotacaoCompraSpan.textContent = "R$ " + this.cotacaoCompra + "; ";
    option.appendChild(cotacaoCompraSpan);

    cotacaoVendaSpan = document.createElement("span");
    cotacaoVendaSpan.textContent = "R$ " + this.cotacaoVenda;
    option.appendChild(cotacaoVendaSpan);

    /*text = this.data.getDate() + "/" + (this.data.getMonth()+1) + 
    		"/" + this.data.getFullYear() +  
    		";" + this.cotacaoVenda + ";" + this.cotacaoCompra;
    option.textContent = text;*/
    select.appendChild(option);
}

function fetchCotacoes(){
	var url;
	var cotacao;
	//verifytextbox
	var data = new Date(data_input.value.replace(/-/g, '\/'));
	if(isNaN(data.getTime())){
		alert("Data Invalida\n");
		return;
	}
	url = 'https://olinda.bcb.gov.br/olinda/servico/PTAX/versao/v1/odata/CotacaoDolarDia(dataCotacao=@dataCotacao)?@dataCotacao=\''
			+ (data.getMonth()+1) + '-' + data.getDate() + '-' + data.getFullYear() 
			+'\'&$top=100&$format=json';
	console.log(url);
	fetch(url).then(function(response) {
		return response.json();
	}).then(function(json) {
		//atribuindo a cotacao o valor recuperado do fetch
		dados = json.value[0];
		cotacao = new Cotacao(data, Number(dados.cotacaoVenda), Number(dados.cotacaoCompra));
		
		var existe = false;
		for (var i = select.options.length - 1; i >= 0; i--) {
			if(select.options[i].text.split(';',1)[0] == cotacao.data.getDate() + "/" + (cotacao.data.getMonth()+1) + "/" +
			 cotacao.data.getFullYear()){
				alert("Essa data já foi inserida em sua tabela.");
				existe = true
			}
		}
		if(!existe){
			cotacao.appendCotacao();
		}
	}).catch(function(err) {
		alert("Não foi possível encontrar a cotação referete a esta data no banco de dados.");
		console.log('Fetch problem: ' + err.message);
	});
	
}

function removeCotacoes(){
	//vamos deletar da drop list enquanto nao ouver algo selecionado
	while(select.selectedIndex != -1){
		select.remove(select.selectedIndex);
	}
}

data_input.onchange = function(){
   botao_incluir.disabled = false;
}

botao_incluir.addEventListener("click", fetchCotacoes);

botao_excluir.addEventListener("click", removeCotacoes);