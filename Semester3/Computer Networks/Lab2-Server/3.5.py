import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(("0.0.0.0", 7777))
s.listen(5)

cs, addr = s.accept()

b = cs.recv(10)
print(b.decode('utf-8'))
nr1 = int(b.decode('utf-8'))

b = cs.recv(10)
print(b.decode('utf-8'))
nr2 = int(b.decode('utf-8'))

cs.send(str(min(nr1, nr2)).encode())

cs.close()
