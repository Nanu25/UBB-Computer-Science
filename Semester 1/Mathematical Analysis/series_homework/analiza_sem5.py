import numpy as np
import matplotlib.pyplot as plt

def convex_function(x):
    return x**2

def convex_derivative(x):
    return 2 * x

def non_convex_function_2(x):
    return x**4 - x**3 - x**2 + x

def non_convex_derivative_2(x):
    return 4*x**3 - 3*x**2 - 2*x + 1

def gradient_descent(eta, x0, iterations, derivative):
    graph = []
    x = x0
    for i in range(iterations):
        graph.append(x)
        x = x - eta * derivative(x)
    return graph

def plot_function_and_path(x, func, path, title):
    plt.plot(x, func(x), label='Function')
    plt.scatter(path, [func(xi) for xi in path], color='yellow', label='Gradient Descent Path')
    plt.xlabel('x')
    plt.ylabel('f(x)')
    plt.legend()
    plt.title(title)
    plt.show()


# Main
while True:
    print("Chose the option:")
    print("1.Convergence to minimum for small η (Convex Function)")
    print("2.Converge faster by increasing η (Convex Function)")
    print("3.Divergence with too large η(Convex Function)")
    print("4.Getting Stuck in a local minimum (Non-Convex Function)")
    print("5.Exit")

    option = input("Enter your option: ")

    if option == '1':
        x0 = 5
        iterations = 25
        path = gradient_descent(0.1, x0, iterations, convex_derivative)
        plot_function_and_path(np.linspace(-7, 7, 100), convex_function, path, "Convergence to minimum (Small η), Made by Grancea Alexandru")

    elif option == '2':
        x0 = 5
        iterations = 25
        path = gradient_descent(0.9, x0, iterations, convex_derivative)
        plot_function_and_path(np.linspace(-7, 7, 100), convex_function, path, "Converge faster by increasing η, Made by Grancea Alexandru")

    elif option == '3':
        x0 = 2
        iterations = 5
        path = gradient_descent(1.2, x0, iterations, convex_derivative)
        plot_function_and_path(np.linspace(-10, 10, 100), convex_function, path, "Divergence with too large η, Made by Grancea Alexandru")

    elif option == '4':
        x0 = 0.9
        iterations = 200
        path = gradient_descent(0.1, x0, iterations,  non_convex_derivative_2)
        plot_function_and_path(np.linspace(-1, 2, 100), non_convex_function_2, path, "Getting stuck in a local minimum (Non-Convex Function),\n Made by Grancea Alexandru")

    elif option == '5':
        print("Bye.")
        break