import socket

SERVER_PORT = 12345

SERVER_SOCKET = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

SERVER_SOCKET.bind(('localhost', SERVER_PORT))
print ('The server is ready')

NUM1, CLIENT_ADDRESS = SERVER_SOCKET.recvfrom(2048)
NUM1 = int(NUM1)
NUM2, CLIENT_ADDRESS = SERVER_SOCKET.recvfrom(2048)
NUM2 = int(NUM2)
NUM3, CLIENT_ADDRESS = SERVER_SOCKET.recvfrom(2048)
NUM3 = int(NUM3)

if NUM3 == 1:
    OUTGOING_MESSAGE = NUM1+NUM2 
elif NUM3 == 2:
    OUTGOING_MESSAGE = NUM1-NUM2
elif NUM3 == 3:
    OUTGOING_MESSAGE = NUM1*NUM2
elif NUM3 == 4:
    OUTGOING_MESSAGE = NUM1/NUM2

print('First Number:  ', NUM1)
print('Second Number:  ', NUM2)
print("Action chosen: ",end='')
if NUM3 == 1: #purely for aestetics really, if you want to check your operations have worked. 
    print("Addition",) 
elif NUM3 == 2:
    print("Subtract")
elif NUM3 == 3:
    print("Multiply")
elif NUM3 == 4:
    print("Divide")

OUTGOING_MESSAGE = str(OUTGOING_MESSAGE)
print("Outgoing Message:  ", OUTGOING_MESSAGE)
OUTGOING_MESSAGE = bytes(OUTGOING_MESSAGE,'utf-8') #convert outgoing message from int to bytes so it can be sent 
SERVER_SOCKET.sendto(OUTGOING_MESSAGE, CLIENT_ADDRESS)
SERVER_SOCKET.close()
input("Press enter to close program") #Keeping this here so that if you run via python it doesn't close as soon as it's completed

