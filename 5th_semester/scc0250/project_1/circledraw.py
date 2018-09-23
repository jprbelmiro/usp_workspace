import math
from pygame import gfxdraw as draw
import pygame
pygame.init()

#Set display configuration
disp = pygame.display.set_mode((401,401))  #resolution
disp.fill((1,1,1))						   #background color

myfont = pygame.font.SysFont("monospace", 15)
label = myfont.render("CIRCUMFERENCE DRAW", 1, (255,255,0))
disp.blit(label, (120, 10))

pygame.display.flip() 					   #update display

#Total of used pixels
n_pixels = 0

def ResetDisp():
	disp = pygame.display.set_mode((401,401))  #resolution
	disp.fill((1,1,1))						   #background color

	myfont = pygame.font.SysFont("monospace", 15)
	label = myfont.render("CIRCUMFERENCE DRAW", 1, (255,255,0))
	disp.blit(label, (120, 10))

	# drawning the screen center reference
	draw.pixel(disp, 200,  200, (255,0,0))
	draw.pixel(disp, 201,  200, (255,0,0))
	draw.pixel(disp, 200,  201, (255,0,0))
	draw.pixel(disp, 199,  200, (255,0,0))
	draw.pixel(disp, 200,  199, (255,0,0))

	pygame.display.flip() 					   #update display

#Simetric Points of a Circumference
def SimetricCirclePoints(x,y,offsetx,offsety,color):
	global n_pixels
	
	# drawning the  circle center reference
	draw.pixel(disp, offsetx,  offsety, (0,255,0))
	draw.pixel(disp, offsetx+2,  offsety, (0,255,0))
	draw.pixel(disp, offsetx,  offsety+2, (0,255,0))
	draw.pixel(disp, offsetx-2,  offsety, (0,255,0))
	draw.pixel(disp, offsetx,  offsety-2, (0,255,0))

	# Drawning the simetric points of a circle
	draw.pixel(disp, x + offsetx,  y + offsety, color)
	draw.pixel(disp, x + offsetx, -y + offsety, color)
	draw.pixel(disp, -x + offsetx,  y + offsety, color)
	draw.pixel(disp, -x + offsetx, -y + offsety, color)
	draw.pixel(disp,  y + offsety,  x + offsetx, color)
	draw.pixel(disp, y + offsety, -x + offsetx, color)
	draw.pixel(disp, -y + offsety,  x + offsetx, color)
	draw.pixel(disp, -y + offsety, -x + offsetx, color)
	n_pixels = n_pixels + 8 # counting the number of pixels
	
	# Updating the display
	pygame.display.flip()

#Draw Circumference (Implicit Equation)
def ImplEqCirc(r,cx,cy,color):
	# Initializing globals
	ResetDisp()
	global n_pixels
	n_pixels = 0

	# Initializing the local variables
	x = 0
	y = r
	
	# Starting the drawn
	SimetricCirclePoints(x, y, cx, cy, color)

	# Fitting the drawn with Implicit Equation
	while (y > x):
		x = x + 1
		y = int(math.sqrt(math.pow(r, 2) - math.pow(x, 2)))
		SimetricCirclePoints(x, y, cx, cy, color)
		pygame.display.flip()	

	return(n_pixels)

#Draw Circumference (Sphere Coordinates)
def SphereCoordCirc(r,cx,cy,color):
	# Initializing globals
	ResetDisp()
	global n_pixels
	n_pixels = 0

	# Initializing the local variables
	theta = 0.0
	x = r
	y = 0
	
	# Starting the drawn
	SimetricCirclePoints(x, y, cx, cy, color)
	
	# Fitting the drawn with Sphere Coordinates
	while (x > y):
		theta = theta + 0.1

		if(x != int(r*math.cos(math.radians(theta))) or y != int(r*math.sin(math.radians(theta)))):
			x = int(r*math.cos(math.radians(theta)))
			y = int(r*math.sin(math.radians(theta)))
			SimetricCirclePoints(x, y, cx, cy, color)

		pygame.display.flip()						#update display

	return(n_pixels)

#Middle Point Circumference
def MidPointCirc(r,cx,cy,color):
	# Initializing globals
	ResetDisp()
	global n_pixels
	n_pixels = 0

	# Initializing the local variables
	x = 0
	y = r
	d = 5 / 4 - r

	# Starting the drawn
	SimetricCirclePoints(x, y, cx, cy, color)

	# Fitting the drawn with Middle Point Transform
	while (y > x):
		if (d < 0):
			d = d + 2 * x + 3
			x = x + 1
		else:
			d = d + 2 * (x - y) + 5
			x = x + 1
			y = y - 1
		SimetricCirclePoints(x, y, cx, cy, color)

		pygame.display.flip()						#update display
	
	return(n_pixels)
