import socket

SERVER_HOST = '127.0.0.1'
SERVER_PORT = 54321

SERVER_SOCKET = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

SERVER_SOCKET.bind((SERVER_HOST, SERVER_PORT))
SERVER_SOCKET.listen()

INCOMING_CONNECTION, CLIENT_ADDRESS = SERVER_SOCKET.accept()

while True:
    INCOMING_MESSAGE = INCOMING_CONNECTION.recv(4096)
    if not INCOMING_MESSAGE:
        break
    INCOMING_MESSAGE = INCOMING_MESSAGE.decode()
    LENGTH = len(INCOMING_MESSAGE) # use build in function len to get characters including spaces. 
    WORDS = len((INCOMING_MESSAGE).split()) #calculate number of words
    WORDS = str(WORDS) #convert from int to string
    WORDS = bytes(WORDS, 'utf-8') #convert string to bytes
    INCOMING_CONNECTION.sendall(WORDS) #can now be sent as it's in bytes
    LENGTH = str(LENGTH) #repeat conversion process described above but for number of characters integer rather than number of words 
    LENGTH = bytes(LENGTH,'utf-8')
    INCOMING_CONNECTION.sendall(LENGTH)
    