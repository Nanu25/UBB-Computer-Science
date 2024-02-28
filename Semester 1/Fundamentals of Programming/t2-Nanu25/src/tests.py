import unittest

from src.bus_routes_repository import TextFileRepositoryRoute
from src.domain import Bus
from src.repository import TextFileRepositoryBus
from src.route_domain import Bus_routes
from src.route_service import RouteService
from src.services import BusService


class TestDistance(unittest.TestCase):
    def setUp(self):
        self.__bus_repository = TextFileRepositoryBus("buses.txt")
        self.__route_repository = TextFileRepositoryRoute("bus_routes.txt")
        self.__bus_service = BusService(self.__bus_repository, self.__route_repository)
        self.__route_service = RouteService(self.__bus_repository, self.__route_repository)

    def test_distance(self):
        route_code = 4
        length = 20
        route = Bus_routes(route_code, length)
        self.__route_service.add_route(route)

        bus_id = 5
        model = "Mercedes"
        times = 15
        bus = Bus(bus_id, route.route_code, model, times)
        self.__bus_service.add_bus(bus)

        print(self.__bus_service.compute_distance(5))
        print(self.__bus_service.find(5))

