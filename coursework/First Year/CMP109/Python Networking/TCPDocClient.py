import socket

SERVER_HOST = '127.0.0.1'
SERVER_PORT = 54321

CLIENT_SOCKET = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

CLIENT_SOCKET.connect((SERVER_HOST, SERVER_PORT))
filePath= input("Please enter the file path for your .txt file ")
f = open(filePath) #open file 
SENT_MESSAGE = f.read() #sent message should be the string that is read from the text file
CLIENT_SOCKET.sendall(SENT_MESSAGE.encode()) #send the text file to server

WORDS, SERVER_ADDRESS = CLIENT_SOCKET.recvfrom(4096) #recieve our calculated values
LENGTH, SERVER_ADDRESS = CLIENT_SOCKET.recvfrom(4096)

print ("Number of words",WORDS.decode())
print("Number of characters",LENGTH.decode())
input("Press enter to exit ")
