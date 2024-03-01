import matplotlib.pyplot as plt
import numpy as np

def p_norm(x, y, p):
    return (abs(x) ** p + abs(y) ** p) ** (1 / p)

num_points = 10000
p_values = [1.25, 1.5, 3, 8]

plt.figure(figsize=(12, 3))

for i, p in enumerate(p_values, 1):

    points = np.random.uniform(-1, 1, (num_points, 2))

    norms = np.array([p_norm(x, y, p) for x, y in points])

    inside_points = points[norms <= 1]


    plt.subplot(1, len(p_values), i)
    plt.scatter(inside_points[:, 0], inside_points[:, 1], alpha=0.5)
    plt.title(f'p = {p}')
    plt.xlabel('x')
    plt.ylabel('y')
    plt.axis('equal')

plt.tight_layout()
plt.show()