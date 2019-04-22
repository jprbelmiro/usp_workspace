from State import State


class NodeTreeAStar(State):
    def __init__(self, state=None, depth=0, father=None, actions=[]):
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

        self.functionEvaluation(actions)

    def addChild(self, state, actions):
        # Criando nó filho
        child = NodeTreeAStar(state, self.depth + 1, self)

        # Add conexão ao pai
        # child.father = self

        # Add compoor em filhos do pai
        self.childs.append(child)

        # depth do filho com baase no pai
        # child.depth = self.depth + 1

        # Avaliação permissiveel
        child.functionEvaluation(actions)

    # Modificação de Estado  -  depende das possibilidades do state
    def updateState(self, newstate):
        self.state = newstate

    # função Avaliadora
    def functionEvaluation(self, actions):
        self.heuristic = 0
        for a in actions:
            new_state = self.state.move(a)
            if new_state is not None:
                self.heuristic += 1


        self.evaluation = self.heuristic  - self.depth


    def expandChild(self, actions):
        for a in actions:
            new_state = self.state.move(a)
            if new_state is not None:
                self.addChild(new_state,actions)


class processesActive(NodeTreeAStar):
    def __init__(self, root):
        # referencia ao root
        self.root = root

        # lista de processos ativos e raank de aavaaliaçao
        self.rankEvaluationlist = list()
        self.processes = list()

        # Processo Corrente
        self.cur_processe = list()
        self.cur_processe.append(self.root)
        self.processes.append(self.cur_processe)

    def add_cur_processe(self, child):
        self.cur_processe.append(child)

    def addProcesse(self, child):
        # Add ccaminho do novo processo considerando o pai
        new_processe = list()
        new_processe.append(self.root)
        new_processe.append(child)

        # Update processo corrente
        self.processes.append(new_processe)
        self.cur_processe = new_processe

    def rankEvaluation(self, father):
        for child in father.childs:
            self.rankEvaluationlist.append(child)

        self.rankEvaluationlist.sort(reverse=True,key=lambda x: x.evaluation)

    def manageAssets(self, termine_state):
        # Inicializa processo corrente
        if not self.cur_processe:
            self.cur_processe.append(self.rankEvaluationlist[0])
            return 1
        # Confere se encontrou o objetivo
        elif self.rankEvaluationlist[0].state == termine_state:
            return 0
        else:
            # confere se Continua o processo (Caminho atual)
            if self.rankEvaluationlist[0].father == self.cur_processe[-1]:
                self.cur_processe.append(self.rankEvaluationlist[0])
                return 1
            # confere se o processo é filho da raiz (root)
            elif self.root == self.rankEvaluationlist[0].father:
                self.addProcesse(self.rankEvaluationlist[0])
                return 1
            # confere se existe um processo Ativo com este nó
            else:
                for a in self.processes:
                    if a[-1] == self.rankEvaluationlist[0].father:
                        self.cur_processe = a
                        self.cur_processe.append(self.rankEvaluationlist[0])

                return 1


class SearchAStar():
    def __init__(self, starte_state, actions):
        # inicializa a arvore e processos ativos
        self.root = NodeTreeAStar(starte_state, 0, None, actions)
        self.processes = processesActive(self.root)

    def initialize(self, termine_state, actions):
        # inicializa Arvore e processos
        self.root.expandChild(actions)
        self.processes.rankEvaluation(self.root)
        progress = self.processes.manageAssets(termine_state)

        while progress != 0:
            print("Evaluation:")
            print(self.processes.rankEvaluationlist[0].evaluation)
            print("Status")
            print(self.processes.rankEvaluationlist[0].state.status)

            self.processes.cur_processe[-1].expandChild(actions)
            self.processes.rankEvaluationlist.pop(0)
            self.processes.rankEvaluation(self.processes.cur_processe[-1])
            progress = self.processes.manageAssets(termine_state)
