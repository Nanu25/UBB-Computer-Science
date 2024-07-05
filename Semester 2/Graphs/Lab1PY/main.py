from Graph import *

def print_menu():
    print();
    print("1 for print the graph")
    print("2 for add a edge")
    print("3 for add a vertex")
    print("4 for remove a edge")
    print("5 for remove a vertex")
    print("6 for update a edge")
    print("7 for copy the graph")
    print("8 for print the number of vertices")
    print("9 for print the number of edges")
    print("10 for print the inner edges of a vertex")
    print("11 for print the outer edges of a vertex")
    print("12 for print the cost of an edge")
    print("13 for print the edges")
    print("14 for print the in-degree of a vertex")
    print("15 for print the out-degree of a vertex")
    print("16 for print if exists an edge between two vertices")
    print("0 for exit")

def choose_file():
    print("1 for choose the file with 1k vertices")
    print("2 for choose the file with 10k vertices")
    print("3 for choose the file with 100k vertices")
    print("4 for choose the file with 1M vertices")
    print("5 for generate a random graph")

def lab1():
    choose_file()
    choise = int(input("Choose the file or generate a random graph: "))

    graph = Graph()
    if choise == 1:
        graph = read_graph("graph1k.in")
    elif choise == 2:
        graph = read_graph("graph10k.in")
    elif choise == 3:
        graph = read_graph("graph100k.in")
    elif choise == 4:
        graph = read_graph("graph1m.txt")
    else:
        n = int(input("Enter the number of vertices: "))
        m = int(input("Enter the number of edges: "))
        graph = generate_random_graph(n, m)
        write_graph(graph, "my_graph")

    copy_graph = graph.copy_graph()
    while True:
        print_menu()

        option = int(input("Enter an option: "))
        if option == 1:
            graph.print_graph()
        elif option == 2:
            x = int(input("Enter the first vertex: "))
            y = int(input("Enter the second vertex: "))
            z = int(input("Enter the cost of the edge: "))
            try:
                graph.add_edge(x, y, z)
            except ValueError as ve:
                print(ve)

        elif option == 3:
            try:
                graph.add_vertex()
            except ValueError as ve:
                print(ve)

        elif option == 4:
            x = int(input("Enter the first vertex: "))
            y = int(input("Enter the second vertex: "))
            try:
                graph.remove_edge(x, y)
            except ValueError as ve:
                print(ve)
        elif option == 5:
            x = int(input("Enter the vertex: "))
            try:
                graph.remove_vertex(x)
            except ValueError as ve:
                print(ve)
        elif option == 6:
            x = int(input("Enter the first vertex: "))
            y = int(input("Enter the second vertex: "))
            z = int(input("Enter the new cost of the edge: "))
            try:
                graph.update_edge(x, y, z)
            except ValueError as ve:
                print(ve)
        elif option == 7:
            new_graph = graph.copy_graph()
            new_graph.print_graph()
        elif option == 8:
            print(graph.vertices)
        elif option == 9:
            print(graph.edges)
        elif option == 10:
            x = int(input("Enter the vertex: "))
            try:
                print(graph.get_inner_edges(x))
            except ValueError as ve:
                print(ve)
        elif option == 11:
            x = int(input("Enter the vertex: "))
            try:
                print(graph.get_outer_edges(x))
            except ValueError as ve:
                print(ve)
        elif option == 12:
            x = int(input("Enter the first vertex: "))
            y = int(input("Enter the second vertex: "))
            try:
                print(graph.get_cost(x, y))
            except ValueError as ve:
                print(ve)
        elif option == 13:
            for edges in graph.edge_iterator():
                print(edges)
        elif option == 14:
            x = int(input("Enter the vertex: "))
            try:
                print(graph.get_inner_degree(x))
            except ValueError as ve:
                print(ve)
        elif option == 15:
            x = int(input("Enter the vertex: "))
            try:
                print(graph.get_outer_degree(x))
            except ValueError as ve:
                print(ve)
        elif option == 16:
            x = int(input("Enter the first vertex: "))
            y = int(input("Enter the second vertex: "))

            edge = graph.find_edge(x, y)
            if edge != None:
                print("The edge exists")
            else:
                print("The edge does not exist")
        elif option == 0:
            break

    write_graph(graph, "graph1k_modif.txt")
    print("Do you want to print the initial graph?")
    print("1 for yes")
    print("2 for no")
    choise = int(input("Enter the choise: "))
    if choise == 1:
        print("The graph before the operations is: ")
        copy_graph.print_graph()


def path_between_two_nodes():
    #choose_file()
    #choise = int(input("Choose the file or generate a random graph: "))

    graph = Graph()
    graph = read_graph("graflab2")
    # if choise == 1:
    #     graph = read_graph("graph1k.in")
    # elif choise == 2:
    #     graph = read_graph("graph10k.in")
    # elif choise == 3:
    #     graph = read_graph("graph100k.in")
    # elif choise == 4:
    #     graph = read_graph("graph1m.txt")
    # else:
    #     n = int(input("Enter the number of vertices: "))
    #     m = int(input("Enter the number of edges: "))
    #     graph = generate_random_graph(n, m)
    #     write_graph(graph, "my_graph")

    while True:
        x = int(input("Tell the first vertex "))
        y = int(input("Tell the second vertex "))
        path = graph.bfs(x ,y)
        if path == None:
            print("There is no path")
        else:
            print("The length of the path is: ", len(path) - 1)
            print("The path is: ")
            for node in path:
                print(node, end=" ")

        print("")
        print("Do you want to continue?")
        print("0 for exit")
        print("1 for continue")
        option = int(input(">"))
        if option == 0:
            break

if __name__ == '__main__':
    print("1 for the graph class")
    print("2 for bfs backwards function")
    option = int(input(">"))

    if option == 1:
        lab1()
    elif option == 2:
        path_between_two_nodes()    #let's say 1,10