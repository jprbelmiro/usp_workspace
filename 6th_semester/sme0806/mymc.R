mcgamma <- function(n,a,b,alpha,beta){
	x = runif(n,a,b)

	k = (beta**alpha)/(gamma(alpha))
	w = (b-a)*k*(x**(alpha-1))*(exp(1)**(-beta*x))
	i = (1/n)*(sum(w))
	print(i)

	p <- (1:n)/n
	print(mean(pgamma(alpha,x)))
}