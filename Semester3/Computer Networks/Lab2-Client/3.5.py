import socket
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(("127.0.0.1", 7777))

nr1 = int(input("Enter first number: "))
nr2 = int(input("Enter second number: "))
s.send(str(nr1).encode())  # Send bytes instead of string
s.send(str(nr2).encode())  # Send bytes instead of string

print(s.recv(10).decode('utf-8'))  # Receive bytes and decode to string

s.close()
