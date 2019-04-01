densityf <- function(x,lambda){
    if( x >= 0){
        return(lambda**(-lambda*x))
    }
    else{
        return(0)
    }
 }

plota <- function(start,end,by){
	# generating x and setting plot
	x <-seq(start,end,by)
	par(mfrow=c(2,2))

	# labda = 0.5
	y <- c()
	for(i in 1:length(x)){
		y <- c(y,densityf(x[i],0.5))
	}
	plot(x,y,xlab="x",ylab="density: f(x)",main="lamda = 0.5") 

	# labda = 1
	y <- c()
	for(i in 1:length(x)){
		y <- c(y,densityf(x[i],1))
	}
	plot(x,y,xlab="x",ylab="density: f(x)",main="lamda = 1") 

	# labda = 3
	y <- c()
	for(i in 1:length(x)){
		y <- c(y,densityf(x[i],3))
	}
	plot(x,y,xlab="x",ylab="density: f(x)",main="lamda = 3") 

	# labda = 10
	y <- c()
	for(i in 1:length(x)){
		y <- c(y,densityf(x[i],10))
	}
	plot(x,y,xlab="x",ylab="density: f(x)",main="lamda = 10") 
}

plotb <- function(start,end,by){
	# generating x and setting plot
	x <-seq(start,end,by)

	# labda = 0.5
	y1 <- c()
	for(i in 1:length(x)){
		y1 <- c(y1,densityf(x[i],0.5))
	}
	# labda = 1
	y2 <- c()
	for(i in 1:length(x)){
		y2 <- c(y2,densityf(x[i],1))
	}
	# labda = 3
	y3 <- c()
	for(i in 1:length(x)){
		y3 <- c(y3,densityf(x[i],3))
	}
	# labda = 10
	y4 <- c()
	for(i in 1:length(x)){
		y4 <- c(y4,densityf(x[i],10))
	}

	# ploting
	plot(x,y1,xlab="x",ylab="density: f(x)",col="blue",pch="o",main="Impact of Lambda Value over a Density Function")

	points(x, y2, col="red", pch="*")
	lines(x, y2, col="red",lty=2)

	points(x, y3, col="green",pch="+")
	lines(x, y3, col="green", lty=3) 

	points(x, y3, col="yellow",pch="x")
	lines(x, y3, col="yellow", lty=3) 

	legend("topleft",legend=c("lamda = 0.5","lamda = 1.0","lamda = 3.0","lamda = 10.0"), 
		col=c("blue","red","green","yellow"), pch=c("o","*","+","x"),lty=c(1,2,3,4), ncol=1)
}

plotc <- function(start,end,by){
	# generating x and setting plot
	x <-seq(start,end,by)

	# labda = 1
	y <- c()
	for(i in 1:length(x)){
		y <- c(y,densityf(x[i],1))
	}
	# ploting
	plot(x,y,xlab="x",ylab="density: f(x)",col="blue",pch="o",main="Impact of Lambda Value over a Density Function")
}

