class Bus_routes:
    def __init__(self, route_code, length):
        self.__route_code = route_code
        self.__length = length

    def __str__(self):
        return f'Route {self.__route_code}, Length {self.__length}'

    @property
    def route_code(self):
        return self.__route_code

    @property
    def length(self):
        return self.__length


if __name__ == '__main__':
    bus = Bus_routes(1, 100)
    print(bus)