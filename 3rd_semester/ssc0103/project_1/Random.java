package poo;
import java.util.Calendar;

public class Random {
	private long p = 2147483648l;
	private long m = 843314861;
	private long a = 453816693;

	private long xi = 1023;
	
	public double getRand() {
		xi = (a + m*xi) % p;
		double d = xi;
		return d / p;
	}
	
	public float getFloatRand(float max){
		double d = getRand() * max;
		return (float) d;
	}
	
	public int getIntRand(int max){
		double d = getRand() * max;
		return (int) d;
	}
	
	public String getNameRand(int max){
		String str = "Micanga";
		int index = getIntRand(max);
		
		switch(index){
			case 0:
				str = "Joao";
				break;
			case 1:
				str = "Maria";
				break;
			case 2:
				str = "Pedro";
				break;
			case 3:
				str = "Lara";
				break;
			case 4:
				str = "Geovani";
				break;
			case 5:
				str = "Lucia";
				break;
			case 6:
				str = "Camila";
				break;
			case 7:
				str = "Matheus";
				break;
			case 8:
				str = "Danilo";
				break;
			case 9:
				str = "Felipe";
				break;
			case 10:
				str = "Ines";
				break;
			case 11:
				str = "Dito";
				break;
			case 12:
				str = "Clovis";
				break;
			case 13:
				str = "Karnal";
				break;
			case 14:
				str = "Emilia";
				break;
			case 15:
				str = "Fernanda";
				break;
		}
		
		return str;
	}
	
	public void setSeed(int k){
		xi = k;
		return;
	}
	
	public Random(int k){
		xi = k;
	}
	
	public Random(){
		xi = Calendar.getInstance().getTimeInMillis();
	}
}
