import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(("0.0.0.0", 7777))
s.listen(5)

cs, adress = s.accept()

n = int(cs.recv(10).decode())
print(n)
a = []
for i in range(n):
    data = cs.recv(10).decode()
    a.append(int(data))
print(a)

m = int(cs.recv(10).decode())
print(m)
b = []
for i in range(m):
    data = cs.recv(10).decode()
    b.append(int(data))
print(b)

i = 0
j = 0
c = []
while i < n and j < m:
    if a[i] < b[j]:
        c.append(a[i])
        i += 1
    else:
        c.append(b[j])
        j += 1

while i < n:
    c.append(a[i])
    i += 1

while j < m:
    c.append(b[j])
    j += 1

cs.send(str(c).encode())

cs.close()
