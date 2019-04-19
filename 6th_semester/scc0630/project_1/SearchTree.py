class Node(object):

	# node intialisation method
	def __init__(self, state, depth = 0, father = None):
		# node strutuctural parameters
		self.depth = depth
		self.father = father
		self.childs = []

		# node evaluation parameters
		self.state = state

	# add child method
	def add_child(self,child):
		# a. updating child parameters
		child.father = self
		child.depth = self.depth + 1

		# b. appending the child
		self.childs.append(child)

		return child

	# add child method by state
	def add_child_state(self,state):
		# a. creating a child node
		new_child = Node(state, depth = self.depth+1, father = self)

		# b. appending the child
		self.childs.append(new_child)

		return new_child

class SearchTree(object):
	
	# search tree initialisation method
	def __init__(self,root = None,max_depth = 10):
		self.root = root
		self.max_depth = max_depth
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

	# print tree method
	def show(self,node):
		print node.depth,node.state.status
		for child in node.childs:
			self.show(child)