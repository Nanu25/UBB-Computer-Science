from src.domain import Bus


class TextFileRepositoryBus:
    def __init__(self, file_name):
        self.__file_name = file_name
        self.__data = {}
        self.__load_file()

    def __load_file(self):
        with open(self.__file_name, 'r') as file:
            for line in file.readlines():
                line = line.strip()
                elements_from_line = line.split(',')
                _id = int(elements_from_line[0])
                route_code = int(elements_from_line[1])
                model = elements_from_line[2]
                times = int(elements_from_line[3])
                self.add(Bus(_id, route_code, model, times))
        file.close()

    def __save_file(self):
        with open(self.__file_name, 'w') as file:
            for bus in self.get_data():
                file.write(str(bus.id) + ',' + str(bus.route_id) + ',' + str(bus.model) + ',' + str(bus.times_used) + '\n')
        file.close()


    def add(self, object : Bus):
        if not isinstance(object, Bus):
            raise TypeError('Object must be of type Bus.')
        if object.id in self.__data.keys():
            return TypeError("Id must be unique")

        self.__data[object.id] = object
        self.__save_file()

    def find(self, _id):
        if _id not in self.__data.keys():
            return None
        return self.__data[_id]

    def get_data(self):
        return list(self.__data.values())
