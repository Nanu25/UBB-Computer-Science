from Scramble.Ui.ui import Ui
from Scramble.repository.repository import Repository
from Scramble.service.service import Service

#swap cuvant litera - cuvant litera

if __name__ == '__main__':
    repository = Repository("input.txt")
    service = Service(repository)
    ui = Ui(service)

    ui.Start()