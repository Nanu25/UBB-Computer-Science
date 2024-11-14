import socket

#Putem sa facem bind in client, dar nu este obligatoriu.
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.bind(("0.0.0.0", 5555))

buff, addr = s.recvfrom(10)
print(buff.decode())  # Decode bytes to string for printing

s.sendto(b"hello", addr)  # Send bytes, so prefix string with 'b'
