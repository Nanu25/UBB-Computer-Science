import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(("127.0.0.1", 7777))

# Use getsockname() to find the client's IP and port
client_ip, client_port = s.getsockname()
print(f"Client is using IP: {client_ip}, port: {client_port}")

name = input("Enter your name: ")

s.send(name.encode())

print(s.recv(10).decode('utf-8'))
