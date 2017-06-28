import socket
import json

m = '{"name" : "cmu200", "connection": "172.23.240.105 10001", "requests":[{"action" : "ID", "args" : "5 7 777 05 1 2"},{"action" : "BAList", "args" : "40"},{"action" : "Emission", "args" : "1 -50"}]}'
#jsonObj = json.loads(m)
TCP_IP = '127.0.0.1'
TCP_PORT = 13
BUFFER_SIZE = 1024

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((TCP_IP, TCP_PORT))
s.sendall(m.encode())
