import numpy as np
from scipy.integrate import quad

def f(x):
    return np.exp(-x**2)

integral_results = []

for a in np.linspace(1, 10, 10):
    result, _ = quad(f, -a, a)
    integral_results.append((a, result, result / np.sqrt(np.pi)))

for a, integral, ratio in integral_results:
    print(f"a={a}, Integral={integral}, Ratio to sqrt(pi)={ratio}")