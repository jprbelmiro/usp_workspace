package poo;

public class Placar {
	private int posicoes[] = new int[10];

	public Placar(){
		//inicializacao das posicoes no placar
		for(int i = 0; i < 10; i++)
			posicoes[i] = -1;
	}
	
	public void add(int posicao, int[]dados){
		int aux1 = 0, aux2 = -1;
		if(posicao <= 6 ){
			//verificacao de quantos sao os valores passados no Array que sao iguais as posicoes passadas
			for(int i = 0; i < 5; i++)
				if(dados[i] == posicao)aux1++;
			posicoes[posicao-1] = aux1*posicao;
		}else if(posicao == 10){
			//verificacao se sao 5 numeros iguais
			aux1 = 1;
			for(int i = 1; i < 5; i++)
				if(dados[i] == dados[0])aux1++;
			if(posicao == 10 && aux1 == 5) posicoes[9] = 40;
			else posicoes[posicao-1] = 0;
		}else if(posicao == 9){
			//verificacao se tem 4 numeros iguais
			aux1 = 0;
			for(int i = 1; i < 5; i++)
				if(dados[i] != dados[0])aux1++;
			if(aux1 == 1)
				posicoes[8] = 30;
			else
				for(int i = 2; i < 5;i++)
					posicoes[8] = dados[i] != dados[1]?0:30;
		}else if(posicao == 7){
			//verificacao se sao um full hand (2 iguais + 3 iguais(diferentes dos inicias))
			aux1 = dados[0];
			for(int i = 1; i < 5; i++){
				if(dados[i] != aux1 && aux2 == -1) aux2 = dados[i];
				else if(dados[i] != aux1 && dados[i] != aux2) aux1 = 0;
			}
			posicoes[6] = aux1 == 0?0:15;
		}else{
			//verificacao se formam uma sequencia
			for(int i = 1 ; i < 5; i++)
				for(int j = 0; j < 5-i; j++)
					if(dados[j+1] < dados[j]){
						aux1 = dados[j];
						dados[j] = dados[j+1];
						dados[j+1] = aux1;
					}
			aux1 = 0;
			for(int i = 0; i < 4;i++)
				if(dados[i]+1 != dados[i+1]){
					aux1 = 1;
					break;
				}
			posicoes[7] = aux1==1?0:20;
		}
		
	}
	
	public int getScore( ){
		//retorno da soma do valor total dos dados
		int soma = 0;
			for(int i = 0; i < 10; i++)
				if(posicoes[i] > 0) soma += posicoes[i];
		return soma;
	}
	
@Override
	public String toString(){
		//transformacao do placar em um String
		String s = new String();
		s = posicoes[0] == -1?"(1)":" "+posicoes[0]+" ";
		s += "    |   ";
		s += posicoes[6] == -1?"(7)":posicoes[6] == 0?" "+posicoes[6]+" ":posicoes[6]+" ";
		s += "    |   ";
		s += posicoes[3] == -1?"(4)":posicoes[3]>9?posicoes[3]+" ":" "+posicoes[3]+" ";
		s += " \n--------------------------\n";
		s += posicoes[1] == -1?"(2)":posicoes[1] == 10?posicoes[1]+" ":" "+posicoes[1]+" ";
		s += "    |   ";
		s += posicoes[7] == -1?"(8)":posicoes[7] == 0?" "+posicoes[7]+" ":posicoes[7]+" ";
		s += "    |   ";
		s += posicoes[4] == -1?"(5)":posicoes[4]>9?posicoes[4]+" ":" "+posicoes[4]+" ";
		s += " \n--------------------------\n";
		s += posicoes[2] == -1?"(3)":posicoes[2]>9?posicoes[2]+" ":" "+posicoes[2]+" ";
		s += "    |   ";
		s += posicoes[8] == -1?"(9)":posicoes[8] == 0?" "+posicoes[8]+" ":posicoes[8]+" ";
		s += "    |   ";
		s += posicoes[5] == -1?"(6)":posicoes[5]>9?posicoes[5]+" ":" "+posicoes[5]+" ";
		s += " \n--------------------------\n       |   ";
		s += posicoes[9] == -1?"(10)":posicoes[9]== 0?" "+posicoes[9]+"  ":posicoes[9]+"  ";
		s +="   |\n       +----------+\n";
		return s;
	}
}
