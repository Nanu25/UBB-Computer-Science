class Bus:
    def __init__(self, _id, route_id, model, times_used):
        self.__id = _id
        self.__route_id = route_id
        self.__model = model
        self.__times_used = times_used
    def __str__(self):
        return f'Bus id: {self.id}, route id: {self.route_id}, model: {self.model}, times used the route: {self.times_used}'

    @property
    def id(self):
        return self.__id

    @property
    def route_id(self):
        return self.__route_id

    @property
    def model(self):
        return self.__model
    @property
    def times_used(self):
        return self.__times_used
