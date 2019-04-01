densityf <- function(x,k){
    if( x >= 0 && x <= 1){
        return(k*(x**4)*(1-	x))
    }
    else{
        return(0)
    }
 }
 densityf2 <- function(x,k){
    if( x >= 0 && x <= 1){
        return(k*(x)*(1-x)**4)
    }
    else{
        return(0)
    }
 }

densityplot <- function(start,end,by){
	# generating x and plotting
	# k = 30
	x <-seq(start,end,by)
	y <- c()
	for(i in 1:length(x)){
		y <- c(y,densityf(x[i],30))
	}
	plot(x,y,xlab="x",ylab="density: f(x)") 
}


densityplot2 <- function(start,end,by){
	# generating x and plotting
	# k = 30
	x <-seq(start,end,by)
	y <- c()
	for(i in 1:length(x)){
		y <- c(y,densityf2(x[i],30))
	}
	plot(x,y,xlab="x",ylab="density: f(x)",) 
}

densitycalc <- function(start, end, by){
	# generating x and plotting
	# k = 30
	x <-seq(start,end,by)

	y <- c()
	color <- c()
	for(i in 1:length(x)){
		y <- c(y,densityf(x[i],30))
		if(x[i] > 0.4 && x[i] < 0.8){
			color <- c(color,'red')
		}
		else{
			color <- c(color,'grey')
		}
	}
	barplot(y,col=color,xlab="x",ylab="density: f(x)",main="P(0.4 < X < 0.8) = 0.6144") 
}

densitycalc2 <- function(start, end, by){
	# generating x and plotting
	# k = 30
	x <-seq(start,end,by)

	y <- c()
	color <- c()
	for(i in 1:length(x)){
		y <- c(y,densityf2(x[i],30))
		if(x[i] > 0.4 && x[i] < 0.8){
			color <- c(color,'red')
		}
		else{
			color <- c(color,'grey')
		}
	}
	barplot(y,col=color,xlab="x",ylab="density: f(x)",main="P(0.4 < X < 0.8) = 0.23168") 
}

compdensityplot <- function(start,end,by){
	# generating x and setting plot
	x <-seq(start,end,by)
	y1 <- c()
	for(i in 1:length(x)){
		y1 <- c(y1,densityf(x[i],30))
	}
	y2 <- c()
	for(i in 1:length(x)){
		y2 <- c(y2,densityf2(x[i],30))
	}
	
	# ploting
	plot(x,y1,xlab="x",ylab="y",col="blue",pch="o",main="Density function comparision")

	points(x, y2, col="red",pch="+")
	lines(x, y2, col="red", lty=3) 

	legend("topleft",legend=c("f1(x)","f2(x)"), 
		col=c("blue","red"), pch=c("o","*"),lty=c(1,2,3), ncol=1)
}