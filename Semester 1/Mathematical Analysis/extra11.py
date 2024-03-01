import numpy as np

def f(point):
    x, y = point
    return 100 * (y - x*2)*2 + (1 - x)*2

def grad_f(point):
    x, y = point
    dfdx = -400 * x * (y - x**2) - 2 * (1 - x)
    dfdy = 200 * (y - x**2)
    return np.array([dfdx, dfdy])

def hessian_f(point):
    x, y = point
    dfdxx = 1200 * x**2 - 400 * y + 2
    dfdxy = -400 * x
    dfdyx = -400 * x
    dfdyy = 200
    return np.array([[dfdxx, dfdxy], [dfdyx, dfdyy]])

def newtons_method(start_point, max_iter=1000, tolerance=1e-6):
    point = start_point
    for i in range(max_iter):
        grad = grad_f(point)
        hess = hessian_f(point)
        point = point - np.linalg.inv(hess).dot(grad)
        if np.linalg.norm(grad) < tolerance:
            break
    return point, i+1

def gradient_descent(start_point, learning_rate=1e-3, max_iter=1000, tolerance=1e-6):
    point = start_point
    for i in range(max_iter):
        grad = grad_f(point)
        point = point - learning_rate * grad
        if np.linalg.norm(grad) < tolerance:
            break
    return point, i+1

start_point = np.array([-1.2, 1])

newton_point, newton_iters = newtons_method(start_point)
print(f"Newton's method: {newton_point} in {newton_iters} iterations")

gd_point, gd_iters = gradient_descent(start_point)
print(f"Gradient Descent: {gd_point} in {gd_iters} iterations")

newton_result = f(newton_point)
gd_result = f(gd_point)
print(f"Newton's method minimum value: {newton_result}")
print(f"Gradient Descent minimum value: {gd_result}")