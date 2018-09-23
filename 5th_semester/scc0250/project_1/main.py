import csv
import sys
import time
from circledraw import MidPointCirc,SphereCoordCirc, ImplEqCirc

NOTHING = -1
EXIT = 0
MIDPOINTCONV = 1
SPHERECOORD = 2
IMPLICITEQ = 3

def GoodBye():
	print("|        Thank you for use our program !! Obrigado :)            |")
	print("|          Sao Carlos, SP - April, 2018 - ICMC/USP               |")

def Report(n_pixels, time, method):
	print("------------------------------------------------")
	print("|    Running Report")
	print("| 1. Used Method  : %s" %method)
	print("| 2. Running Time : %.2lf s" %time)
	print("| 3. Number of used pixels : %d" %n_pixels)
	print("-----------------------------------------------\n")

def Welcome():
	print("|    Computer Graphics - Profa Agma Juci Machado Traina          |")
	print("| Students: Fernanda, Sylv, Micanga                              |")
	print("| Project 1 - Circunference Image  (Pixel Matrix Transformation) |")

def main():
	# Starting the user interface
	Welcome()

	choice = NOTHING
	while (choice != EXIT):
		# Initializing the variables
		radius = 0
		x = y = 1000
		choice = NOTHING

		# Requesting the inputs
		while(radius > 200 or radius < 1):
			radius = int( input('Enter the radius of the circumference: ') )
			if(radius > 200 or radius < 1): 
				print(":: invalid radius - expected integer between 1 to 200 ::")

		while(x + radius > 400 or x - radius < 0):	
			x = int( input('Enter the coordinate x of the circumference: ') )
			if(x + radius > 400 or x - radius < 0):	 
				print(":: invalid x coordinate - circumference out of bounds ::")

		while(y + radius > 400 or y - radius < 0):
			y = int( input('Enter the coordinate y of the circumference: ') )
			if(y + radius > 400 or y - radius < 0):	 
				print(":: invalid y coordinate - circumference out of bounds ::")

		# Requesting the transform method to draw the circumference
		while(choice > 3 or choice < 0):
			choice = int( input('Which conversion method you want to use? (Insert a Number)\n0 - Exit\n1 - Middle Point Conversion\n2 - Sphere Coordinate\n3 - Implicit Equation\n> ') )
			if(choice > 3 or choice < 0):
				print(":: invalid choice - expected integer between 0 to 3 ::")

		# Start the circumference draw
		if(choice == EXIT):
			break
		elif (choice == MIDPOINTCONV):
			method = "Middle Point Conversion"
			start_t = time.time()
			n_pixels = MidPointCirc(radius,x,y,(255,255,255))
			end_t = time.time()
		elif (choice == SPHERECOORD):
			method = "Sphere Coordinates Transform"
			start_t = time.time()
			n_pixels = SphereCoordCirc(radius,x,y,(255,255,255))
			end_t = time.time()
		elif (choice == IMPLICITEQ):
			method = "Implicit Equation Application"
			start_t = time.time()
			n_pixels = ImplEqCirc(radius,x,y,(255,255,255))
			end_t = time.time()

		# Printing the report
		Report(n_pixels,float( end_t - start_t ),method)

		choice = int( input("Do you want to continue? '0' to exit.\n> ") )

	# That's all folks :) ...
	GoodBye()
# Cya !!
if __name__ == '__main__':
    main()