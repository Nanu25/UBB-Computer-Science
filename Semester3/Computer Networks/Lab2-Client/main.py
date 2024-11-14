import socket
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(("127.0.0.1", 7777))

s.send(b"Salut")  # Send bytes instead of string
print(s.recv(10).decode('utf-8'))  # Receive bytes and decode to string

s.close()
