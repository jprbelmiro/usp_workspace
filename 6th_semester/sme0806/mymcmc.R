estimate.invar <- function(){
	t = 0
	x = 1
	pi_ = c()

	while(t < 10000){
		u = runif(1,0,1)
		if(x == 1){
			if(u < 0.75){
				x = 1
			}
			else{
				x = 2
			}
		}
		else{
			if(u < 0.125){
				x = 1
			}
			else{
				x = 2
			}
		}
		pi_ = c(pi_,x)
		t = t+1
	}

	print(length(pi_[2000:10000]))
	print(sum(pi_[2000:10000] == 1)/length(pi_[2000:10000]))
	print(1-(sum(pi_[2000:10000] == 1)/length(pi_[2000:10000])))
}

gibbs.norm.bivar <- function(x0,y0,rho=0.75,niter=1000) {
	x = y = rep(0, niter)
	x[1] = x0
	y[1] = y0
	for (i in 2:niter) {
		x[i] = rnorm(1,mean=rho*y[i-1],sd=sqrt(1-rho^2))
		y[i] = rnorm(1,mean=rho*x[i],sd=sqrt(1-rho^2))
	}
	return(cbind(x,y))
}