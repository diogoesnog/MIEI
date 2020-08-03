from multiprocessing import Pipe, Process


class SyncPipe(object):
    def __init__(self, esquerda, direita, timeout=None):
        """
        esquerda : a função que vai ligar ao lado esquerdo do Pipe
        direita: a função que vai ligar ao outro lado (direito)
        timeout: (opcional) numero de segundos que aguarda pela terminação do processo
        """
        left_end, right_end = Pipe()
        self.timeout = timeout
        self.procE = Process(target=esquerda, args=(left_end,))  # os processos ligados ao Pipe
        self.procD = Process(target=direita, args=(right_end,))
        self.esquerda = lambda: esquerda(left_end)  # as funções ligadas já ao Pipe
        self.direita = lambda: direita(right_end)

    def auto(self, proc=None):
        if proc is None:  # corre os dois processos independentes
            self.procE.start()
            self.procD.start()
            self.procE.join(self.timeout)
            self.procD.join(self.timeout)
        else:  # corre só o processo passado como parâmetro
            proc.start()
            proc.join()

    def manual(self):  # corre as duas funções no contexto de um mesmo processo Python
        self.esquerda()
        self.direita()
