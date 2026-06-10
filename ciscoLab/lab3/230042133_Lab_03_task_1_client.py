import socket
import time
import struct

UDP_IP = "127.0.0.1"
UDP_PORT = 5005
server_addr = (UDP_IP, UDP_PORT)

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.settimeout(1.0)  

messages = ["Hello UDP", "Testing Reliability", "IUT CSE 4512", "Concurrent Threading", "End of Lab"]
rtts = []

print("Starting Reliable UDP Client Transmissions...\n")

for i, text in enumerate(messages):
    header = struct.pack("!BI", 0, i)
    packet = header + text.encode('utf-8')
    
    attempts = 0
    acked = False
    
    while attempts < 3:
        start_time = time.time()
        sock.sendto(packet, server_addr)
        print(f"Sending Packet {i} (Attempt {attempts + 1}): '{text}'")
        
        try:
            ack_data, _ = sock.recvfrom(1024)
            elapsed = time.time() - start_time
            
            ack_type, ack_seq = struct.unpack("!BI", ack_data[:5])
            
            if ack_type == 1 and ack_seq == i:
                rtts.append(elapsed)
                print(f"-> Success: Received ACK for Packet {i} (RTT={elapsed:.3f}s)\n")
                acked = True
                break
                
        except socket.timeout:
            attempts += 1
            print(f"-> Timeout! No ACK for Packet {i}. Retrying {attempts}/3...")
            time.sleep(0.5)  
            
    if not acked:
        print(f"Critical Error: Failed to reliably deliver Packet {i} after 3 attempts.\n")

if rtts:
    avg_rtt = sum(rtts) / len(rtts)
    print(f"Transmission Complete. Average RTT for acknowledged packets: {avg_rtt:.4f}s")