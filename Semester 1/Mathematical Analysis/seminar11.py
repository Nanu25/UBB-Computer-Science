import matplotlib.pyplot as plt
import numpy as np

def quadratic_function_grid(X1, X2, A):
    return 0.5 * (A[0, 0] * X1*2 + 2 * A[0, 1] * X1 * X2 + A[1, 1] * X2*2)

def gradient(x, A):
    return np.dot(A, x)

def plot_quadratic(A, title):
    fig = plt.figure(figsize=(14, 7))

    x1 = np.linspace(-5, 5, 100)
    x2 = np.linspace(-5, 5, 100)
    X1, X2 = np.meshgrid(x1, x2)


    Z = quadratic_function_grid(X1, X2, A)

    ax1 = fig.add_subplot(1, 2, 1, projection='3d')
    ax1.plot_surface(X1, X2, Z, cmap='viridis', alpha=0.7)
    ax1.set_title(f'3D Surface Plot: {title}')
    ax1.set_xlabel('x1')
    ax1.set_ylabel('x2')
    ax1.set_zlabel('f(x)')

    ax2 = fig.add_subplot(1, 2, 2)
    contour = ax2.contour(X1, X2, Z, levels=3, colors='black')
    ax2.clabel(contour, inline=True, fontsize=8)
    ax2.set_title(f'Contour Lines: {title}')
    ax2.set_xlabel('x1')
    ax2.set_ylabel('x2')

    points = np.array([[2, 2], [-2, -2], [1, -1]])
    for point in points:
        grad = gradient(point, A)
        ax2.quiver(point[0], point[1], grad[0], grad[1], scale=20, color='red')

    plt.tight_layout()
    plt.show()

A_min = np.array([[2, 0], [0, 2]])
plot_quadratic(A_min, 'Unique Minimum')

A_max = np.array([[-2, 0], [0, -2]])
plot_quadratic(A_max, 'Unique Maximum')

A_saddle = np.array([[2, 0], [0, -2]])
plot_quadratic(A_saddle, 'Unique Saddle Point')

from termcolor import colored

class Circle:

    def __init__(self, color):
        """
        Initializer for the Circle class.
        Input: color of the circle
        """
        self.color = color

    def __str__(self):
        """
        Returns a circle of the color specified.
        """
        return colored('●', self.color)

if __name__ == '__main__':
    C = Circle("blue")
    print(C)
