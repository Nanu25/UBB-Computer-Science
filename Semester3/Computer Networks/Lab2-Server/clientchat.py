import socket
import select
import sys
import threading

def read_from_stdin(sock):
    """Read user input from stdin and send it to the server."""
    while True:
        msg = sys.stdin.readline().strip()
        if msg:
            sock.sendall(msg.encode())

def main():

    hostname = '127.0.0.1'
    port = 7777

    # Resolve hostname to IP address if necessary
    try:
        ip_address = socket.gethostbyname(hostname)
        print("Connecting to {} ...".format(ip_address))
    except socket.gaierror:
        print("Error getting the host address")
        sys.exit(1)

    # Create a TCP socket
    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    except socket.error as e:
        print("Socket creation error:", e)
        sys.exit(1)

    # Set up the server address and connect
    servaddr = (ip_address, port)
    try:
        sock.connect(servaddr)
    except socket.error as e:
        print("Connection error:", e)
        sock.close()
        sys.exit(1)

    print("Connected. Type messages to send:")

    # Start a thread to read from stdin
    threading.Thread(target=read_from_stdin, args=(sock,), daemon=True).start()

    # Main loop to listen for messages from the server
    try:
        while True:
            read_fds, _, _ = select.select([sock], [], [])
            for fd in read_fds:
                if fd == sock:
                    data = sock.recv(256) + b'\n'
                    if not data:
                        print("Server has closed connection... closing...")
                        sock.close()
                        sys.exit(1)
                    print("Server:", data.decode())

    except KeyboardInterrupt:
        print("\nConnection closed.")
    finally:
        sock.close()

if __name__ == "__main__":
    main()
