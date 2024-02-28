DISPLAY_ALL_BUSES = 1
COMPUTE_DISTANCE = 2
DISPLAY_ROUTES_DEACREASING_ORDER = 3
class Ui:
    def __init__(self, bus_service, route_service):
        self.__bus_service = bus_service
        self.__route_service = route_service

    def print_menu(self):
        print("1 for display all the buses travel across a certain given route")
        print("2 for compute how many km the bus travel")
        print("3 for display all the buses routes in decreasing order of the total mileage of all buses travel on them")

    def display_all_buses_for_a_given_route(self, route_id):
        for bus in self.__bus_service.get_all():
            if bus.route_id == route_id:
                print(bus)

    def start(self):
        while True:
            self.print_menu()
            choice = int(input(">"))
            if choice  == DISPLAY_ALL_BUSES:
                route_id = int(input("Enter the route id"))
                self.display_all_buses_for_a_given_route(route_id)
            elif choice == COMPUTE_DISTANCE:
                bus_id = int(input("Enter the bus id"))
                distance = self.__bus_service.compute_distance(bus_id)
                print(distance)
                print(self.__bus_service.find(bus_id))
            elif choice == DISPLAY_ROUTES_DEACREASING_ORDER:
                sorted_list = self.__route_service.sort_routes()

                for route in sorted_list:
                    print("Route id", route[0], "Total length", route[1])
                    print("Buses for this route: ")
                    self.display_all_buses_for_a_given_route(route[0])
                    print("")
            else:
                break
