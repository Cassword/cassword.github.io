import sys
import pigpio
import requests
from matrixKeypad_RPi_GPIO import keypad
from time import sleep

# [PIURL] was added to obscure private IP


email = sys.argv[1]
package_code = sys.argv[2]

pi = pigpio.pi()
if not pi.connected:
    exit("couldn't connect to pigpio daemon")


SERVO_PIN = 16  # (physical pin 36 - don't initialize both BCM and board.)

kp = keypad()

def digit():
    r = None
    while r is None:
        r = kp.getKey()
    return r

def main():

    user_input = ""
    print("Please enter the 6-digit package code: ")

    for i in range(6):
        key = digit()  #get the next key press
        user_input += str(key)  
        print(f"Key {i + 1}: {key} (input so far: {user_input})") 
        sleep(0.5) 

    #print the full entered code
    print(f"Full Entered Code: {user_input}")

    url = "http://[PIURL]:5000/verify_package_code"
    response = requests.post(url, json={"email": email, "package_code": package_code, "user_input": user_input})

    if response.status_code == 200:
        print("Backend confirmed the correct code.")
        pi.set_servo_pulsewidth(SERVO_PIN, 2000)  #move servo to unlock position (~+90 degrees)
        sleep(0.5)  
        pi.set_servo_pulsewidth(SERVO_PIN, 0)  #turn off the servo
        print("package code verified, servo unlocked.")
    else:
        print(f"error message from backend: {response.json().get('error')}.")

    pi.stop()

if __name__ == "__main__":
    main()
