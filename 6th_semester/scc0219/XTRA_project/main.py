# IMPORT PACKAGES
from os.path import isfile
from re import match

# HTML TREE
class HTML_Tree:

	def __init__(self,file):
		# tree parameters
		self.root = None

		# building the tree
		build_tree(file,self.root)

	def build_tree(file,node):
		fline = file.readline()
		if node is None:
			node = HTML_Node(fline)
		else:
			child = HTML_Node(fline)
			node.childs.append(child)

class HTML_Node:

	def __init__(self,code):
		self.code = code
		self.childs = None

# MAIN PROCEDURE
# 1. Reading the file name
filename = None
while filename is None:
	# a. reading the filename
	filename = raw_input("Enter your file name: ")

	# b. checking if it is a html file
	if match("^[a-zA-Z1-9]+.html$",filename) is None:
		filename = None
		print ":: Invalid input format.\n:: Try another file in the current directory."
		print "-- Valid format: '.html'"

	# c. checking if the file exists
	elif isfile(filename) is False:
		filename = None
		print ":: The file doesn't exist.\n:: Try another file in the current directory."

# 2. Starting the html element extraction
# a. opening the file
file = open(filename,'r')

# b. building the HTML Tree from the file
html_tree = HTML_Tree(file)

# c. printing the html elements
html.print_elements() 
file.close()