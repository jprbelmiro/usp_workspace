import csv
import sys
import time
from circledraw import MidPointCirc,SphereCoordCirc, ImplEqCirc

def main():
	n = 100	#number of tests
	r = [5,10,20,50,70,100,120,150,170,200] #test vector

	# Running the tests
	for i in range(len(r)):
		print("-----\nRADIUS: %d" %r[i])

		#middle point
		sum = 0
		for ntests in range(0,n):
			start_t = time.time()
			n_pixels = MidPointCirc(r[i],200,200,(255,255,255))
			end_t = time.time()
			sum = sum + (end_t - start_t)

		print("MP: mean time = %.10lf" %float(sum/100))

		#implicit equation
		sum = 0
		for ntests in range(0,n):
			start_t = time.time()
			n_pixels = ImplEqCirc(r[i],200,200,(255,255,255))
			end_t = time.time()
			sum = sum + (end_t - start_t)

		print("IE: mean time = %.10lf" %float(sum/100))
		
		#sphere coordinate
		sum = 0
		for ntests in range(0,n):
			start_t = time.time()
			n_pixels = SphereCoordCirc(r[i],200,200,(255,255,255))
			end_t = time.time()
			sum = sum + (end_t - start_t)

		print("SP: mean time = %.10lf" %float(sum/100))

if __name__ == '__main__':
    main()