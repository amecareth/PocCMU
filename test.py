import socket

TCP_IP = '127.0.0.1'
TCP_PORT = 13
BUFFER_SIZE = 1024

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((TCP_IP, TCP_PORT))
message = "CREATE_DEVICE CMU200 172.23.240.105 10001\n"
s.send(message.encode())
message = 'CREATE_ID CMU200 5 7 555 05 1 2\n'
s.send(message.encode())
message = 'CREATE_BALIST CMU200\n'
s.send(message.encode())
message = 'ADD_BA CMU200 40\n'
s.send(message.encode())
message = 'CREATE_EMISSION CMU200 1 -50\n'
s.send(message.encode())
