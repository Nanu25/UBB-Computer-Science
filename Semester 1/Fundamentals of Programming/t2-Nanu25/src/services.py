from src.repository import TextFileRepositoryBus
from src.bus_routes_repository import TextFileRepositoryRoute

class BusService:
    def __init__(self, bus_repository : TextFileRepositoryBus, routes_repository : TextFileRepositoryRoute):
        self.__bus_repository = bus_repository
        self.__routes_repository = routes_repository

    def compute_distance(self, bus_id : int):
        bus = self.__bus_repository.find(bus_id)
        route = self.__routes_repository.find(bus.route_id)
        distance = bus.times_used * route.length
        return distance
    def add_bus(self, bus):
        self.__bus_repository.add(bus)

    def get_all(self):
        return list(self.__bus_repository.get_data())

    def find(self, _id):
        return self.__bus_repository.find(_id)
