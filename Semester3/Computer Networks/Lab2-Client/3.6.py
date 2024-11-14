import socket
import struct

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(("127.0.0.1", 7777))

n = int(input("Enter the number of elements: "))
s.send(struct.pack('>H', n))  # '>H' means big-endian unsigned short (2 bytes)

for i in range(n):
    x = int(input("Enter a number: "))
    s.send(struct.pack('>H', x))  # Send each number as a 2-byte unsigned short

result = s.recv(2)  # Expecting a 2-byte response
print("The maxnumber is:", struct.unpack('>H', result)[0])  # Unpack the result

s.close()
