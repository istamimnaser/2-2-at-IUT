# ==========================================
# PART B: UDP Client (udp_client.py)
# ==========================================
# Import socket for networking and time for RTT measurements
import socket
import time

# Create a UDP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Set a 1 second timeout for blocking socket operations
# This is the time which we will wait for the echo
sock.settimeout(1.0)

# Define server address as localhost on port 5005
# localhost -> own machine -> 127.0.0.1
server_addr = ('127.0.0.1', 5005)

# ---- Single message exchange ----
print("--- Sending Single Message ---")
message = 'Hello, UDP Server'

# Encode the string to bytes and send to the server
sock.sendto(message.encode('utf-8'), server_addr)

try:
    # Wait for up to 1024 bytes response
    data, _ = sock.recvfrom(1024)
    print("Echo:", data.decode('utf-8'))
except socket.timeout:
    print("No response, server may be down.")

print("\n--- Sending Multiple Messages with Retry & RTT ---")
# ---- Multiple messages with retry and RTT ----
rtts = []  # to store round-trip times

# Sending 5 messages with max 3 retries
for i in range(5):
    text = f"Msg {i}".encode('utf-8')
    attempts = 0
    while attempts < 3:
        start = time.time()  # start RTT timer
        sock.sendto(text, server_addr)  # send datagram
        try:
            data, _ = sock.recvfrom(1024)  # wait for echo
            elapsed = time.time() - start
            rtts.append(elapsed)
            print(f"Response {i}: {data.decode('utf-8')} (RTT={elapsed:.3f}s)")
            break
        except socket.timeout:
            attempts += 1
            print(f"Retry {attempts} for message {i}")
            time.sleep(0.5)  # brief pause between messages
            
    if attempts == 3:
        print(f"Message {i} failed completely after 3 attempts.")

# Close socket configuration closing the client
sock.close()