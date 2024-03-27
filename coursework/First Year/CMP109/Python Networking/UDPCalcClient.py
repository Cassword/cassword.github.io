import socket

SERVER_NAME = 'localhost'
SERVER_PORT = 12345

CLIENT_SOCKET = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

USER_NUM1 = input('Input a number ')
USER_NUM2 = input('Input another number ')
print("Add (1)")
print("Subtract (2)")
print("Multiply (3)")
print("Divide (4)")
while True: #not strictly necessary input validation
    USER_NUM3 = input('What would you like to do? ') 
    USER_NUM3 = int(USER_NUM3) #convert NUM 3 to an integer so we can check it's a valid choice with an if statement - no point sending an invalid operation.
    if USER_NUM3 <0 or USER_NUM3 >4: # ensure it is within valid bounds
        print("Invalid Choice")
        continue
    else:
        break
USER_NUM3 = str(USER_NUM3) #encode back to string so we can encode it to be sent via socket 

    
    

CLIENT_SOCKET.sendto(USER_NUM1.encode(),(SERVER_NAME,SERVER_PORT))
CLIENT_SOCKET.sendto(USER_NUM2.encode(),(SERVER_NAME,SERVER_PORT))
CLIENT_SOCKET.sendto(USER_NUM3.encode(),(SERVER_NAME,SERVER_PORT))

MODIFIED_MESSAGE, SERVER_ADDRESS = CLIENT_SOCKET.recvfrom(2048)

print("Calculated Answer: ",MODIFIED_MESSAGE.decode())
input("Press enter to close program") #Keeping this here so that if you run both via python it doesn't close as soon as it's completed
