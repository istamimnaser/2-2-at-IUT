# ==========================================
# PART A: UDP Echo Server (udp_server.py)
# ==========================================
# Import the socket module to create UDP sockets
import socket

# Create a UDP socket (AF_INET = IPv4, SOCK_DGRAM = UDP)
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Bind the socket to all interfaces on port 5005
# '0.0.0.0' makes the server reachable from any network it is attached to
sock.bind(('0.0.0.0', 5005))
print("UDP server listening on port 5005...")

try:
    # Enter an infinite loop to receive and echo packets
    while True:
        # recvfrom(1024) waits for up to 1024 bytes from any client
        data, addr = sock.recvfrom(1024)
        
        # Print the raw data and the client address (IP, port)
        print(f"Received {data!r} from {addr}")
        
        # Send the exact same data back to the sender
        sock.sendto(data, addr)

except KeyboardInterrupt:
    print("\nShutting down server.")
    sock.close()