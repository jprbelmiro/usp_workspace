var periodoTextBox = document.getElementById("input-days");
var vendasCheckBox = document.getElementById("sells");
var comprasCheckBox = document.getElementById("buy");
var descCheckBox = document.getElementById("gt");
var ascCheckBox = document.getElementById("lt");

var botao = document.querySelector("Button");
var body = document.querySelector("body");
var div_table = null;

//criando objeto cotacao
var Cotacao = function(data, cotacao) {
  this.data = data;
  this.cotacao = cotacao;
}

var Cotacoes = function(){
	this.cotacoes = [];
}

//metodo que le cotacoes de acordo com o  
//tipo que o usuario solicitou e adciona na lista
Cotacoes.prototype.addCotacoes = function(cotacao){
	var novaCotacao;
	for(i = 0; i < cotacao.length; i++){
		if(comprasCheckBox.checked){
			novaCotacao = new Cotacao(cotacao[i].dataHoraCotacao, cotacao[i].cotacaoCompra); 
		}
		else if(vendasCheckBox.checked){
			novaCotacao = new Cotacao(cotacao[i].dataHoraCotacao, cotacao[i].cotacaoVenda);
		}
		if(novaCotacao != undefined) {
			this.cotacoes.push(novaCotacao);
		}
	}
}

//Metodo que ordena as cotacoes de acordo com
// a ordem que o usuario solicitou
Cotacoes.prototype.ordenarCotacoes = function (){
	if(ascCheckBox.checked){
		this.cotacoes.sort(function(a, b){return a.cotacao-b.cotacao})
	}else if(descCheckBox.checked){
		this.cotacoes.sort(function(a, b){return b.cotacao-a.cotacao})
	}
}

//metodo que insere as cotacoes na pagina
Cotacoes.prototype.appendCotacoes = function(){
	//caso existir uma retira-lá para nao acumular tabelas
	if(div_table != null) div_table.parentNode.removeChild(div_table);
	//Adicionando nova Div para inserir dados
	div_table = document.createElement("div");
	body.appendChild(div_table);
	//Criando center para inserir Titulo da tabela
	var center = document.createElement("center");
	center.textContent = "COTAÇÕES SELECIONADAS PARA VISUALIZAÇÃO";
	div_table.appendChild(center);
	//Caixa da div
	var div_box = document.createElement("div");
	div_box.setAttribute('class', 'myBox');
	div_table.appendChild(div_box);
	//Como ela se dispoem
	var div_row = document.createElement("div");
	div_row.setAttribute('class', 'row');
	div_box.appendChild(div_row);
	//coluna de datas
	var div_col_data = document.createElement("div");
	div_col_data.setAttribute('class', 'column-list');
	div_row.appendChild(div_col_data);
	//nomeando e setando uma lista cotacoes
	var label_data = document.createElement("label");
	label_data.setAttribute("for", "data-list");
	label_data.innerHTML = "<b>Datas</b>";
	div_col_data.appendChild(label_data);
	var ul_data = document.createElement("ul");
	ul_data.setAttribute('id', 'data-list');
	ul_data.setAttribute('style', 'list-style-type:none;');
	div_col_data.appendChild(ul_data);
	//coluna de cotacoes
	var div_col_cotacao = document.createElement("div");
	div_col_cotacao.setAttribute('class', 'column-list');
	div_row.appendChild(div_col_cotacao);
	//nomeando e setando uma lista para cotacoes
	var label_cot = document.createElement("label");
	label_cot.setAttribute("for", "cot-list");
	label_cot.innerHTML = "<b>Cotações</b>";
	div_col_cotacao.appendChild(label_cot);
	var ul_cotacao = document.createElement("ul");
	ul_cotacao.setAttribute('id', 'cot-list');
	ul_cotacao.setAttribute('style', 'list-style-type:none;');
	div_col_cotacao.appendChild(ul_cotacao);
	
	var li_data;
	var li_cot;	
	//populando a lista de data e cotacao com os dados
    for (var i = 0; i < this.cotacoes.length; i++) {
        li_data = document.createElement("li");
        li_cot = document.createElement("li");
        li_data.textContent = this.cotacoes[i].data.toString();
		li_cot.textContent += this.cotacoes[i].cotacao;
        ul_data.appendChild(li_data);
        ul_cotacao.appendChild(li_cot);
    }
}

function fetchCotacoes(){
	var cotacoes = new Cotacoes();
	var url;
	var cotacao;

	//ler o periodo que o usuario pediu e setar datas do dia de hoje até
	//o dia de hoje menos o numero de dias que o usuario inseriu
	var dias = Number(periodoTextBox.value);
	var dataInicial = new Date()
	dataInicial.setDate(dataInicial.getDate() - dias);
	var dataFinal = new Date();
	
	//verificando se os text está correto
	if(dias < 10 || dias > 90){
		alert("fornecer um período de 10 (min) a 90 (max) dias para o qual solicita cotação.");
		return;
	}
	if(periodoTextBox.checkValidity() == false){
		alert("Insira o numero de dias.")
		return;
	}

	//criando URL para consultar o JSOn
	url = 'https://olinda.bcb.gov.br/olinda/servico/PTAX/versao/v1/odata/CotacaoDolarPeriodo(dataInicial=@dataInicial,dataFinalCotacao=@dataFinalCotacao)?@dataInicial=\''
			+ (dataInicial.getMonth()+1) + '-' + dataInicial.getDate() + '-' + dataInicial.getFullYear() 
			+'\'&@dataFinalCotacao=\''
			+ (dataFinal.getMonth()+1) + '-' + dataFinal.getDate() + '-' + dataFinal.getFullYear()
			+ '\'&$top=100&$format=json';

	fetch(url).then(function(response) {
		return response.json();
	}).then(function(json) {
		//atribuindo a cotacao o valor recuperado do fetch
		cotacao = json.value;
		//
		cotacoes.addCotacoes(cotacao);
		cotacoes.ordenarCotacoes();
		cotacoes.appendCotacoes();
	}).catch(function(err) {
		console.log('Fetch problem: ' + err.message);
	});
		
	
	return cotacoes;
}

//Procurar Cotacoes quando clicar no botao
botao.addEventListener("click", fetchCotacoes);

//nao deixar checkar dois eventos checkados ao mesmo tempo
descCheckBox.addEventListener("click", function(){ 
	ascCheckBox.checked = false;});

ascCheckBox.addEventListener("click", function(){ 
	descCheckBox.checked = false;});

vendasCheckBox.addEventListener("click", function(){ 
	comprasCheckBox.checked = false;});

comprasCheckBox.addEventListener("click", function(){ 
	vendasCheckBox.checked = false;});
