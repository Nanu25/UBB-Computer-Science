from src.route_domain import Bus_routes


class TextFileRepositoryRoute:
    def __init__(self, file_name : str):
        self.__file_name = file_name
        self.__data = {}
        self.__load_file()

    def add(self, object : Bus_routes):
        if not isinstance(object, Bus_routes):
            raise TypeError("Object must be of type Bus_routes")
        if object.route_code in self.__data.values():
            raise TypeError("Duplicate route code")

        self.__data[object.route_code] = object
        self.__save_file()

    def find(self, route_code):
        if route_code not in self.__data.keys():
            return None
        return self.__data[route_code]

    def __save_file(self):
        with open(self.__file_name, 'w') as file:
            for bus in self.__data.values():
                file.write(str(bus.route_code) + "," + str(bus.length) + "\n")
        file.close()

    def __load_file(self):
        with open(self.__file_name, 'r') as file:
            for line in file.readlines():
                line = line.strip()
                elements_from_line = line.split(',')
                route_code = int(elements_from_line[0])
                length = int(elements_from_line[1])
                self.add(Bus_routes(route_code, length))
        file.close()

    def get_data(self):
        return list(self.__data.values())