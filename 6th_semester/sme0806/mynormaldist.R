normplot <- function(start,end,by){
	# generating x and setting plot
	x <-seq(start,end,by)

	# X ~ N(100,64)
	y1 <- dnorm(x,100,64)
	
	# X ~ N(80,64)
	y2 <- dnorm(x,80,64)
	
	# X ~ N(80,225)
	y3 <- dnorm(x,80,225)
	
	
	# ploting
	plot(x,y1,xlab="x",ylab="y",col="blue",pch="o",main="Normal Distribution Analysis")

	points(x, y2, col="red", pch="*")
	lines(x, y2, col="red",lty=2)

	points(x, y3, col="green",pch="+")
	lines(x, y3, col="green", lty=3) 

	legend("topleft",legend=c("X ~ N(100,64)","X ~ N(80,64)","X ~ N(80,225)"), 
		col=c("blue","red","green"), pch=c("o","*","+"),lty=c(1,2,3), ncol=1)
}