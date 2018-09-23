import java.io.IOException;

public class TerceiroPrograma {

	public static void main(String[] args) throws IOException {
		double x1, x2, delta, a, b, c;
		
		System.out.println("-- RESOLVEDOR DE EQUACOES DE SEGUNDO GRAU --");
		System.out.println("Bem vindo ao programa que resolve equacoes de segundo grau.");
		System.out.println("Digite os valores de cada coeficiente da equcao do tipo a*x² + b*x + c.");
		
		System.out.printf("a = ");
		a = EntradaTeclado.leDouble();
		
		System.out.printf("b = ");
		b = EntradaTeclado.leDouble();
		
		System.out.printf("c = ");
		c = EntradaTeclado.leDouble();
		
		delta = (b*b) - (4*a*c);
		
		if(a != 0){
			if (delta > 0){
				x1 = ((-b) + Math.sqrt(delta))/(2*a);
				x2 = ((-b) - Math.sqrt(delta))/(2*a);
				System.out.printf("\nExistem duas raizes para estes coeficientes. Resultado:\nx1 = %.3f;\nx2 = %.3f;\n",x1,x2);
			}
			else if (delta == 0){
				x1 = (-b)/(2*a);
				System.out.printf("\nExiste uma unica solucao para estes coeficientes. Resultado:\nx = %.3f;\n",x1);
			}
			else{
				System.out.printf("\nNao existe raiz para estes coeficientes.\n");
			}
		}
		else{
			System.out.printf("Esta equacao nao e uma equacao de segundo grau...");
			if(b != 0){
				System.out.printf(" (Mas a resposta e: ");
				x1 = (-c)/b;
				System.out.printf("x = %.3f c: )\n",x1);
			}
			else
				System.out.printf("\n");
		}
			
		System.out.printf("Finalizando o programa. Micanga agradece sua  preferencia...");
		return;
	}

}
