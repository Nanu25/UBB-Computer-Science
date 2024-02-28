from src.bus_routes_repository import TextFileRepositoryRoute
from src.repository import TextFileRepositoryBus
from src.route_service import RouteService
from src.services import BusService
from src.ui import Ui

if __name__ == '__main__':
    bus_repository = TextFileRepositoryBus("buses.txt")
    route_repository = TextFileRepositoryRoute("bus_routes.txt")

    bus_service = BusService(bus_repository, route_repository)
    route_service = RouteService(bus_repository, route_repository)

    ui = Ui(bus_service, route_service)
    ui.start()