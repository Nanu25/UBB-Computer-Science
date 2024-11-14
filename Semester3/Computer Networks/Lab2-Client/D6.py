import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(("127.0.0.1", 7777))

sentence = input("Enter a sentence:")
s.send(sentence.encode())

letter = input("Enter a letter:")
s.send(letter.encode())

print(s.recv(100).decode('utf-8'))

s.close()
