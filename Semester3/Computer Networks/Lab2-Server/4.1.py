import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(("0.0.0.0", 7777))
s.listen(5)

cs, addr = s.accept()

name = cs.recv(100)
print(name.decode('utf-8'))
print(addr[1])

s = 0
x = int(addr[1])
while x > 0:
    s += x % 10
    x = x // 10

cs.send(str(s).encode())

