# coding: utf-8

from State import State
from copy import copy

class SearchAStar():
	def __init__(self, starte_state, actions):
		# inicializa a arvore e processos ativos
		self.root = NodeAStar(starte_state, 0, None)
		self.actions = actions
		self.activeProcesses = list()
		self.activeProcesses.append(self.root)

	def search(self, termine_state):
		visit_counter = 0
		while len(self.activeProcesses) > 0:
			print("Evaluation:")
			print(self.activeProcesses[0].evaluation)
			print("Status")
			print(self.activeProcesses[0].state.status)

			self.activateProcesses()
			self.activeProcesses.pop(0)
			visit_counter += 1
			if len(self.activeProcesses) > 0: 
				self.evaluateActiveProcesses()
				self.rankEvaluation()
				if self.activeProcesses[0].state.is_equal(termine_state):
					print 'Solution found'
					print '- Visited Nodes: '+str(visit_counter)
					self.show_route(self.activeProcesses[0])
					return None
			else:
				print 'No solution'
				return None

	def activateProcesses(self):
		cur_node = self.activeProcesses[0]
		for a in self.actions:
			new_state = cur_node.state.move(a)
			if new_state is not None:
				cur_node.addChild(new_state)

		for c in cur_node.childs:
			self.activeProcesses.append(c)

	def evaluateActiveProcesses(self):
		for node in self.activeProcesses:
			node.heuristic = 0

			for a in self.actions:
				new_state = node.state.move(a)
				if new_state is not None:
					node.heuristic += 1

			if node.depth < 12:
				node.evaluation = (6-node.state.status[0]-node.state.status[1])+\
				(node.heuristic) + node.depth
			else:
				node.evaluation = 999999 

	def rankEvaluation(self):
		self.activeProcesses.sort(reverse=False,key=lambda x: x.evaluation)

	def show_route(self,node):
		# a. initialising the route vector
		# and the current node
		route = []
		cur_node = copy(node)

		# b. building the route vector by
		# node's father backtracking
		while cur_node is not None:
			route.append(cur_node.state.status)
			cur_node = copy(cur_node.father)

		# c. showing the result
		print '- Steps:', len(route)-1,'\n- Route:', list(reversed(route))


class NodeAStar(State):
	def __init__(self, state=None, depth=0, father=None):
		# Estado pertencente ao nó
		self.state = state

		# Estrutura da Arvore de caminhos A*
		self.father = father
		self.childs = []

		# Função avaliação
		self.depth = depth  # Custo do caminho = profundidade

		# Heuristica => Quanto menos pessoas na margem de origem mais proximo do objetivo
		self.heuristic = 0  # Heuristic = Total de pessoas na margem origem
		self.evaluation = 0  # Função avaliadora >>> f(n) = g(n) + h(n)

	def addChild(self, state):
		# Criando nó filho
		child = NodeAStar(state, self.depth + 1, self)

		# Add compoor em filhos do pai
		self.childs.append(child)