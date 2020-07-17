import socket
from struct import *
from random import *

n = int(input("Give the number: "))
c = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
r = pack('>i ', n)
c.sendto(r, ('172.30.113.167', 4444))
chunk = c.recvfrom(4)[0]
chunk = unpack('<i', chunk)
n = chunk[0]
for i in range(n):
    chunk = c.recvfrom(4)[0]
    chunk = unpack('<i', chunk)
    print(chunk[0])
c.close()