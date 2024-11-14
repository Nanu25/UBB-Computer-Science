import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(("0.0.0.0", 7777))
s.listen(5)

cs, adress = s.accept()

sentence = cs.recv(100).decode()
print(sentence)
letter = cs.recv(1).decode()
print(letter)

pos = []
for i in range(len(sentence)):
    if sentence[i] == letter:
       pos.append(i)

cs.send(str(pos).encode())

s.close()
