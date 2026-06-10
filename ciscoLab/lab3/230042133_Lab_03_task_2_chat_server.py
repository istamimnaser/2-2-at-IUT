import socket
import threading
import struct
import logging

logging.basicConfig(
    filename='chat_server.log',
    level=logging.INFO,
    format='%(asctime)s - [CHAT_SERVER] - %(levelname)s - %(message)s',
    datefmt='%Y-%m-%d %H:%M:%S'
)

UDP_IP = "0.0.0.0"
UDP_PORT = 5005

server_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
server_sock.bind((UDP_IP, UDP_PORT))

active_clients = {}
clients_lock = threading.Lock()

print(f"Reliable Chat Server running on port {UDP_PORT}...")
logging.info("Chat Server initialized.")

def handle_client_message(data, addr):
    with clients_lock:
        if addr not in active_clients:
            active_clients[addr] = 0
            # print(f"\n[JOIN] Client {addr} entered the chat room.")
            logging.info(f"New client registered: {addr}")

    try:
        pkt_type, seq_num = struct.unpack("!BI", data[:5])
        payload = data[5:].decode('utf-8')

        if pkt_type == 0:  
            ack_packet = struct.pack("!BI", 1, seq_num)
            server_sock.sendto(ack_packet, addr)
            
            if seq_num == active_clients[addr]:
                active_clients[addr] += 1
                print(f"\r[Broadcast] {payload}")
                logging.info(f"Received message from {addr}: {payload}")

                with clients_lock:
                    for client_addr in list(active_clients.keys()):
                        if client_addr != addr:
                            broadcast_pkt = struct.pack("!BI", 0, 0) + payload.encode('utf-8')
                            server_sock.sendto(broadcast_pkt, client_addr)
    except Exception as e:
        logging.error(f"Error handling message from {addr}: {str(e)}")

try:
    while True:
        data, addr = server_sock.recvfrom(1029)
        threading.Thread(target=handle_client_message, args=(data, addr), daemon=True).start()
except KeyboardInterrupt:
    print("\nShutting down Chat Server.")
    server_sock.close()