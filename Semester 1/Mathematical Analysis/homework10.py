import numpy as np
import matplotlib.pyplot as plt

# Define the function
def f(x, y):
    return x*2 + y*2

# Define the gradient of the function
def gradient(x, y):
    return np.array([2*x, 2*y])

# Gradient descent function
def gradient_descent(starting_point, learning_rate, iterations):
    points = [starting_point]
    for _ in range(iterations):
        grad = gradient(*points[-1])
        new_point = points[-1] - learning_rate * grad
        points.append(new_point)
    return np.array(points)

# Parameters
learning_rates = [1, 0.5, 0.2, 0.1]
iterations = 10
starting_point = np.array([1.0, 1.0])  # starting point (x0, y0)

# Plotting
x = np.linspace(-1.5, 1.5, 400)
y = np.linspace(-1.5, 1.5, 400)
X, Y = np.meshgrid(x, y)
Z = f(X, Y)

plt.figure(figsize=(12, 8))

# Plot contour lines
contour = plt.contour(X, Y, Z, levels=50, cmap='viridis')

# Perform gradient descent and plot the iterations for each learning rate
for b in learning_rates:
    points = gradient_descent(starting_point, b, iterations)
    plt.plot(points[:, 0], points[:, 1], 'o-', label=f'b = {b}')

plt.title('Gradient Descent Paths on Contour Plot')
plt.xlabel('x')
plt.ylabel('y')
plt.legend()
plt.colorbar(contour)
plt.show()