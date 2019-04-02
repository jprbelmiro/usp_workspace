class Node():

	# node intialisation method
	def __init__(depth = 0, childs = list(), father = None,\
	 visit_count = 0, state = None,value = 0):
		# node strutuctural parameters
		self.depth = depth
		self.childs = childs
		self.father = father

		# node evaluation parameters
		self.visit_count = 0
		self.state = state
		self.value = value

	# value calculation method
	def update_value():
		self.value = self.state.reward

	# reset visit count method
	def reset_visit()
		self.visit_count = 

	# add child method
	def add_child(self,child):
		# a. updating child parameters
		child.father = self
		child.depth = self.depth + 1

		# b. appending the child
		self.childs.append(child)

class SearchTree():
	
	# search tree initialisation method
	def __init__(self,root = None):
		self.root = root
		self.update_depths(self.root,0)

	# update the depths from a node method
	def update_depths(self,node,depth):
		if node is None:
			return

		node.depth = depth
		for child in node.childs:
			self.update_depths(child,depth+1)

	# depth-first search algorithm
	def dfs(self,node,state):
		if node.state.is_equal(state):
			return node

		for child in node.childs:
			self.dfs(child,state)

	# breadth-first search algorithm (initialisation)
	def bfs(self,node,state):
		# a. initialising the bfs queue
		self.bfs_queue = list()

		# b. starting the search
		self.recursive_bfs(node,state)

	# breadth-first search algorithm (recursive search)
	def recursive_bfs(self,node,state):
		# a. checking the stop condition
		if node.state.is_equal(state):
			return node
		# b. removing the current node from the queue
		elif len(self.bfs_queue) != 0:
			self.bfs_queue.pop(0)

		# c. adding the childs to the queue
		for child in node.childs:
			self.bfs_queue.append(child)

		# d. searching
		if len(self.bfs_queue) != 0:
			return self.recursive_bfs(self.bfs_queue[0],state)
		else:
			return None
