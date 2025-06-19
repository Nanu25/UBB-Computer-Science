import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Define the Cross-in-Tray function
def cross_in_tray(x, y):
    term = np.abs(100 - np.sqrt(x**2 + y**2) / np.pi)
    return -0.0001 * (np.abs(np.sin(x) * np.sin(y) * np.exp(term)) + 1) ** 0.1

# Define the Eggholder function
def eggholder(x, y):
    return -(y + 47) * np.sin(np.sqrt(np.abs(x / 2 + y + 47))) - x * np.sin(np.sqrt(np.abs(x - (y + 47))))

# Define domains
x1 = np.linspace(-10, 10, 400)
y1 = np.linspace(-10, 10, 400)
X1, Y1 = np.meshgrid(x1, y1)
Z1 = cross_in_tray(X1, Y1)

x2 = np.linspace(-512, 512, 400)
y2 = np.linspace(-512, 512, 400)
X2, Y2 = np.meshgrid(x2, y2)
Z2 = eggholder(X2, Y2)

# Plot Cross-in-Tray - Contour
plt.figure(figsize=(6, 5))
cont1 = plt.contourf(X1, Y1, Z1, levels=100, cmap='viridis')
plt.title('Cross-in-Tray Function - Contour')
plt.xlabel('x')
plt.ylabel('y')
plt.colorbar(cont1)
plt.show()

# Plot Cross-in-Tray - Surface
fig = plt.figure(figsize=(7, 5))
ax = fig.add_subplot(111, projection='3d')
surf1 = ax.plot_surface(X1, Y1, Z1, cmap='viridis', edgecolor='none')
ax.set_title('Cross-in-Tray Function - Surface')
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('f(x,y)')
plt.show()

# Plot Eggholder - Contour
plt.figure(figsize=(6, 5))
cont2 = plt.contourf(X2, Y2, Z2, levels=100, cmap='plasma')
plt.title("Eggholder Function - Contour")
plt.xlabel('x')
plt.ylabel('y')
plt.colorbar(cont2)
plt.show()

# Plot Eggholder - Surface
fig = plt.figure(figsize=(7, 5))
ax2 = fig.add_subplot(111, projection='3d')
surf2 = ax2.plot_surface(X2, Y2, Z2, cmap='plasma', edgecolor='none')
ax2.set_title('Eggholder Function - Surface')
ax2.set_xlabel('x')
ax2.set_ylabel('y')
ax2.set_zlabel('f(x,y)')
plt.show()
