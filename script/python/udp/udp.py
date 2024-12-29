###################################
# @ filename    : udp.py
# @ author      : yyrwkk
# @ create time : 2024/12/29 14:58:17
# @ version     : v1.0.0
###################################
import socket

remote_ip   = '192.168.19.108'
remote_port = 33333 

def hansdshake():
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    message = "hello,imuonfeet!"
    sock.sendto(message.encode(), (remote_ip, remote_port))

    data, _ = sock.recvfrom(1024)
    if( data.decode() == "hi,imuonfeet!" ):
        print("handshake success!")
    return sock 
def running(sock):
    while True:
        data, _ = sock.recvfrom(1024)
        print(data.hex(),end="")

     

if __name__ == '__main__':
    sock = hansdshake()
    running(sock)