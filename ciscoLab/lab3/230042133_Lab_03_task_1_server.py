import socket
import threading
import struct
import logging

logging.basicConfig(
    filename='server.log',
    level=logging.INFO,
    format='%(asctime)s - [UDP_SERVER] - %(levelname)s - %(message)s',
    datefmt='%Y-%m-%d %H:%M:%S'
)

UDP_IP = "0.0.0.0"  
UDP_PORT = 5005

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
sock.bind((UDP_IP, UDP_PORT))

print(f"Reliable UDP server listening on port {UDP_PORT}... ")
logging.info(f"Server started on port {UDP_PORT}")

def handle_request(data, addr):
    try:
        if len(data) < 5:
            logging.warning(f"Malformed packet received from {addr}")
            return

        pkt_type, seq_num = struct.unpack("!BI", data[:5])
        payload = data[5:].decode('utf-8')

        if pkt_type == 0:  
            print(f"Received Packet {seq_num}: {payload!r} from {addr}")
            logging.info(f"Received Packet {seq_num} from {addr} containing: {payload}")

            ack_header = struct.pack("!BI", 1, seq_num)
            
            sock.sendto(ack_header, addr)
            logging.info(f"Sent ACK for Packet {seq_num} to {addr}")

    except Exception as e:
        logging.error(f"Error handling request from {addr}: {str(e)}")

try:
    while True:
        data, addr = sock.recvfrom(1029)
        
        threading.Thread(target=handle_request, args=(data, addr), daemon=True).start()

except KeyboardInterrupt:
    print("\nShutting down reliable server.")
    logging.info("Server shut down via KeyboardInterrupt.")
    sock.close()