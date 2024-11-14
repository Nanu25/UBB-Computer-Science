import socket
import struct

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(("127.0.0.1", 7777))
for i in range(3):
    suffle_word = s.recv(1024).decode('utf-8')
    while(True):
        word = input("Enter a word:")
        s.send(word.encode('utf-8'))

        response = s.recv(1024).decode('utf-8')
        print(response)
        if response == "correct":
            break

        points = s.recv(1024).decode('utf-8')
        print(points)



s.close()
