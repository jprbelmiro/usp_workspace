package poo;

import java.util.Calendar;

public class Dado {
	int lados;
	int ultimoLado;
	Random r;
	
	public Dado(){
		//inicializacao de um dado de 6 lados
		lados = 6;
		r = new Random((int)Calendar.getInstance().getTime().getTime());
		try{ Thread.sleep(100);}catch(Exception e){}
	}
	
	public Dado(int n){
		//inicializacao de um dado de n lados
		lados = n;
		r = new Random((int)Calendar.getInstance().getTime().getTime());
		try{ Thread.sleep(100);}catch(Exception e){}
	}
	
	public int getLado(){
		//retorno do ultimo valor obtido quando rolou o dado
		return ultimoLado;
	}
	
	public int rolar(){
		//rola o dado e retorna o valor obtido
		ultimoLado = r.getIntRand(lados)+1;
		return ultimoLado;
	}
	
@Override
	public String toString(){
		//transformaca de um dado em String
		String s = new String();
		s = "+-----+\n|";
		s += ultimoLado == 1?"    ":"*   ";
		s += ultimoLado == 4||ultimoLado == 5||ultimoLado == 6?"*|\n|":" |\n|";
		s += ultimoLado == 6?"* ":"  ";
		s += ultimoLado == 2|| ultimoLado == 4 || ultimoLado == 6?"  ":"* ";
		s += ultimoLado == 6?"*|\n|":" |\n|";
		s += ultimoLado == 4|| ultimoLado == 5 || ultimoLado == 6?"*   ":"    ";
		s += ultimoLado == 1?" ":"*";
		s += "|\n+-----+";
		return s;
	}
}