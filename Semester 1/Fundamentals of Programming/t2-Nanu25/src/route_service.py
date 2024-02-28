from src.route_domain import Bus_routes


class RouteService:
    def __init__(self, bus_repository, route_repository):
        self.__bus_repository = bus_repository
        self.__route_repository = route_repository

    def add_route(self, route : Bus_routes):
        self.__route_repository.add(route)

    def get_all(self):
        return self.__route_repository.get_data()

    def find(self, _id):
        return self.__route_repository.find(_id)

    def sort_routes(self):
        number_of_miles = {}
        for bus in self.__bus_repository.get_data():
            if bus.route_id not in number_of_miles:
                number_of_miles[bus.route_id] = bus.times_used * self.__route_repository.find(bus.route_id).length
            else:
                number_of_miles[bus.route_id] += bus.times_used * self.__route_repository.find(bus.route_id).length

        number_of_miles = sorted(number_of_miles.items(), key=lambda x : x[1], reverse=True)
        return number_of_miles