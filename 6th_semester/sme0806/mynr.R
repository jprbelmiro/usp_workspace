NR.gama <- function(x,start=c(1,1),eps=0.001,niter=50){
	# 1. Initialising the variables
	n = length(x)
	alpha= start[1]
	beta = start[2]

	grad = c(0,0)
	hessian = matrix(0,2,2)

	z = start
	theta = matrix(start,ncol=2, dimnames=list(NULL,c("alpha","beta")))

	# 2. Starting the NR iteration
	for (i in 1:niter) {
		# a. calculating the gradient vector
		grad[1] = n*log(beta) - n*digamma(alpha)+sum(log(x))
		grad[2] = n*alpha/beta- sum(x)

		# b. calculating the hessian matrix
		hessian[1,1]= -n*trigamma(alpha)
		hessian[2,2]= -n*alpha/beta^2
		hessian[1,2]= hessian[2,1]= n/beta

		# c. updating the variables
		znew = z - grad %*% solve(hessian)
		alpha= znew[1]
		beta = znew[2]
		theta= rbind(theta,znew)

		# d. checking stop condition 
		if (sum(abs(znew-z) < eps)==2) 
			return(theta) 
		else [
			z = znew
	}
	return(theta)
}