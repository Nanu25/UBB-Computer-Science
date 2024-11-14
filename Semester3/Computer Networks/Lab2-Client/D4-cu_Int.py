import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(("172.30.247.53", 7777))

n = int(input("Enter the number of elements: "))
s.send(str(n).encode())
print("Enter an sorted array")

for i in range(n):
    x = int(input("Enter a number: "))
    s.send(str(x).encode()) #trebuie sa trimit la citire. Daca creez lista o sa mi concateneze elementele.

m = int(input("Enter the number of elements: "))
s.send(str(m).encode())
print("Enter an sorted array")
for i in range(m):
    x = int(input("Enter a number: "))
    s.send(str(x).encode())

print(s.recv(100).decode('utf-8'))



