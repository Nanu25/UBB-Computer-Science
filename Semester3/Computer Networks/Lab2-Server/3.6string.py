import socket
import struct
import threading

def handle_client(cs, addr):
    print(f"Connected to {addr}")

    n = cs.recv(10)
    n = struct.unpack('>H', n)[0]
    print("Received n:", n)

    words = ''
    for i in range(n):
        #len_data = cs.recv(2)
        #length = struct.unpack('>H', len_data)[0]
        string_data = cs.recv(100).decode('utf-8')
        print(f"Received string {i + 1}: {string_data}")
        words += string_data

    cs.send(words.encode())

    cs.close()
    print(f"Connection with {addr} closed.")

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(("0.0.0.0", 7777))
s.listen(5)

print("Server listening on port 7777...")

while True:  # Loop to accept multiple connections
    cs, addr = s.accept()
    client_thread = threading.Thread(target=handle_client, args=(cs, addr))
    client_thread.start()  # Start the thread
