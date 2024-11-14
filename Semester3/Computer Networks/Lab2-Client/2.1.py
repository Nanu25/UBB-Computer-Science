import socket
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(("172.30.247.53", 6968))

words = ""
for i in range(3):
    word = input("Enter a word: ")
    words += word

s.send(str(words).encode())
print(s.recv(20).decode('utf-8'))
s.close()