# ========================================================
# PART D: Concurrent UDP Echo Server (udp_server_concurrent.py)
# ========================================================
import socket
import threading
import time

# Create UDP server socket
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Allow immediate reuse of the socket address after shutdown
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

# Bind to all interfaces on port 5005
sock.bind(('0.0.0.0', 5005))
print("UDP Concurrent Server listening on port 5005...")

# Handler function that each new thread will run independently
def handle_request(data, addr):
    # Simulate a tiny processing delay (e.g., database lookup or log parsing)
    # This helps demonstrate how threads operate in parallel without blocking each other
    time.sleep(0.1) 
    
    print(f"[{threading.current_thread().name}] Received {data!r} from {addr}")
    
    # Send the echo back to the specific client address
    sock.sendto(data, addr)

try:
    while True:
        # Main thread blocks here waiting for any packet
        data, addr = sock.recvfrom(1024)
        
        # When data arrives, spawn a worker thread to execute handle_request
        # target: The function to execute
        # args: The arguments to pass to that function
        # daemon=True: Allows the program to exit cleanly even if threads are running
        client_thread = threading.Thread(
            target=handle_request, 
            args=(data, addr),
            daemon=True
        )
        
        # Kick off the thread execution
        client_thread.start()

except KeyboardInterrupt:
    print("\nShutting down concurrent server.")
    sock.close()