package poo;

public class RolaDados {
	
	int nd6;
	Dado[] d6;

	static public java.lang.String gerarL3D(Dado[] d6, int n){
		java.lang.String s = null;
		for(int i = 0 ; i < n ; i++){
			if(i == 0){
				if(d6[i].getLado() > 3)
					s = "|*   *|   ";
				else if(d6[i].getLado() != 1)
					s = "|    *|   ";
				else
					s = "|     |   ";
			}
			else{
				if(d6[i].getLado() > 3)
					s += "|*   *|   ";
				else if(d6[i].getLado() != 1)
					s += "|    *|   ";
				else
					s += "|     |   ";
			}
		}
		return s;
	}
	
	static public java.lang.String gerarL2D(Dado[] d6, int n){
		java.lang.String s = null;
		for(int i = 0 ; i < n ; i++){
			if(i == 0){
				if(d6[i].getLado() % 2 == 1)
					s = "|  *  |   ";
				else if(d6[i].getLado() == 6)
					s = "|*   *|   ";
				else
					s = "|     |   ";
			}
			else{
				if(d6[i].getLado() % 2 == 1)
					s += "|  *  |   ";
				else if(d6[i].getLado() == 6)
					s += "|*   *|   ";
				else
					s += "|     |   ";
			}
		}
		return s;
	}
	
	static public java.lang.String gerarL1D(Dado[] d6, int n){
		java.lang.String s = null;
		for(int i = 0 ; i < n ; i++){
			if(i == 0){
				if(d6[i].getLado() > 3)
					s = "|*   *|   ";
				else if(d6[i].getLado() != 1)
					s = "|*    |   ";
				else
					s = "|     |   ";
			}
			else{
				if(d6[i].getLado() > 3)
					s += "|*   *|   ";
				else if(d6[i].getLado() != 1)
					s += "|*    |   ";
				else
					s += "|     |   ";
			}
		}
		return s;
	}
	
	//Retorna um vetor de inteiros informando os numeros existentes em cada Dado
	public int[] getDados(){
		int[] d6result = new int[5];
		for(int count = 0 ; count < 5 ; count++){
			d6result[count] = d6[count].getLado();
		}
		return d6result;
	}
	
	
	//Imprime todos os dados na tela
	@Override
	public java.lang.String toString(){
		java.lang.String s = "   1         2         3         4         5\n"
						   + "+-----+   +-----+   +-----+   +-----+   +-----+\n"
						   +  gerarL1D(d6,5) + "\n"
						   +  gerarL2D(d6,5) + "\n"
						   +  gerarL3D(d6,5) + "\n"
						   + "+-----+   +-----+   +-----+   +-----+   +-----+\n";
		return s;
	}
	
	//Rola os dados que foram escritos em uma string
	public int[] rolar(java.lang.String s){
		int[] resultado = new int[nd6];
		for(int i = 0 ; i < s.length() ; i++){
			if(Character.isDigit(s.charAt(i)) && 
			Character.getNumericValue(s.charAt(i)) <= nd6 &&
			Character.getNumericValue(s.charAt(i)) > 0){
				d6[Character.getNumericValue(s.charAt(i))-1].rolar();
			}
		}
		return resultado;	
	}
	
	//Rola os dados que foram selecionados em um vetor de indicacao
	public int[] rolar(boolean quais[]){
		int[] resultado = new int[nd6];
		for(int i = 0 ; i < nd6 ; i++){
			if(quais[i])
				resultado[i] = d6[i].rolar();
			else
				resultado[i] = d6[i].getLado();
		}
		return resultado;	
	}
	
	//Rola todos os dados
	public int[] rolar(){
		int[] resultado = new int[nd6];
		for(int i = 0 ; i < nd6 ; i++){
			resultado[i] = d6[i].rolar();
		}
		return resultado;	
	}
	
	//Cria n objetos da classe Rola Dados
	public RolaDados(int n){
		nd6 = n;
		d6 = new Dado[n];
		for(int i = 0 ; i < n ; i++)
			d6[i] = new Dado();
	}
}
