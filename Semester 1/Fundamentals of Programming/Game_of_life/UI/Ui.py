from Game_of_life.service.service import Service


class Ui:
    def __init__(self, service : Service):
        self.__service = service

    def Start(self):
        while True:
            print(self.__service.get_board())
            comand = input("> ")

            comand.strip()
            comand = comand.split(" ")

            if comand[0] == "place":
                try:
                    x = int(comand[2])
                    y = int(comand[3])

                    self.__service.place_pattern(comand[1], x, y)
                except TypeError as te:
                    print(te)
            elif comand[0] == "tick":
                length = 0
                if len(comand) == 1:
                    length = 1
                else:
                    length = int(comand[1])

                self.__service.tick_generation(length)


            elif comand[0] == "save":
                file_name = comand[1]
                self.__service.save_file(file_name)
            elif comand[0] == "load":
                pass
            else:
                break