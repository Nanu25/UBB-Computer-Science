import socket
import struct
import threading

def handle_client(cs, addr):
    print(f"Connected to {addr}")

    n = cs.recv(10)
    n = struct.unpack('>H', n)[0]
    print("Received n:", n)

    numbers = []
    for i in range(n):
        b = cs.recv(5)
        number = struct.unpack('>H', b)[0]
        print("Recived from {addr} \n", number)
        numbers.append(number)

    maxim = max(numbers)
    response = struct.pack('>H', maxim)
    cs.send(response)

    cs.close()
    print(f"Connection with {addr} closed.")

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(("0.0.0.0", 7777))
s.listen(5)

print("Server listening on port 7777...")

while True:  # Loop to accept multiple connections
    cs, addr = s.accept()
    # Create a new thread to handle the client
    client_thread = threading.Thread(target=handle_client, args=(cs, addr))
    client_thread.start()  # Start the thread
