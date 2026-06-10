import socket
import struct
import threading
import time
import sys

UDP_IP = "127.0.0.1"
UDP_PORT = 5005
server_addr = (UDP_IP, UDP_PORT)
TIMEOUT = 1.0

client_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

username = input("Enter your chat room username: ")
seq_num = 0

ack_received = threading.Event()
last_ack_seq = -1

def receive_handler():
    global last_ack_seq
    while True:
        try:
            data, _ = client_sock.recvfrom(1029)
            if len(data) < 5:
                continue
                
            pkt_type, incoming_seq = struct.unpack("!BI", data[:5])
            payload = data[5:].decode('utf-8')
            
            if pkt_type == 1: 
                last_ack_seq = incoming_seq
                ack_received.set()
            elif pkt_type == 0:  
                print(f"\r{payload}\n{username}> ", end="")
                sys.stdout.flush()
        except Exception:
            break

threading.Thread(target=receive_handler, daemon=True).start()

print(f"Welcome to the chat room, {username}! Type messages below.\n")

while True:
    msg = input(f"{username}> ")
    if not msg.strip():
        continue
        
    formatted_msg = f"{username}: {msg}"
    packet = struct.pack("!BI", 0, seq_num) + formatted_msg.encode('utf-8')
    
    attempts = 0
    acked = False
    
    while attempts < 3:
        ack_received.clear()
        client_sock.sendto(packet, server_addr)
        
        if ack_received.wait(timeout=TIMEOUT) and last_ack_seq == seq_num:
            acked = True
            seq_num += 1
            break
        else:
            attempts += 1
            print(f"\r[System: No ACK received. Retrying message {attempts}/3...]")
            time.sleep(0.3)
            
    if not acked:
        print("\r[System Error: Message failed to broadcast. Server may be down.]")