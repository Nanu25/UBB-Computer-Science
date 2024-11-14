import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(("0.0.0.0", 7777))
s.listen(5)

cs, addr = s.accept()
b = cs.recv(100)
print(b.decode('utf-8'))

words = b.decode('utf-8').split()

maxim = 0
cuvant = ""
for word in words:
    if len(word) > maxim:
        maxim = len(word)
        cuvant = word


cs.send(cuvant.encode())
cs.close()

