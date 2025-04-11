import socket
import re

HOST = '130.192.5.212'
PORT = 6531
NUM_CHALLENGES = 129

def is_ecb(output_hex):
    """Check if the first half matches the second half"""
    return output_hex[:len(output_hex)//2] == output_hex[len(output_hex)//2:]

def main():
    with socket.create_connection((HOST, PORT)) as s:
        s.settimeout(5)
        for i in range(NUM_CHALLENGES):
            data = b''
            while True:
                chunk = s.recv(4096)
                data += chunk
                if b'Input:' in data or b'The flag is:' in data:
                    break

            text = data.decode()
            print(text)  # Optional

            # Check if flag is in this message
            if "The flag is:" in text:
                print("\n🎉 FLAG FOUND 🎉")
                print(text)
                break

            # Extract the OTP
            match = re.search(r"The otp I'm using: ([0-9a-f]{64})", text)
            if not match:
                print("OTP not found.")
                break

            otp = match.group(1)
            s.sendall((otp + '\n').encode())

            # Wait for Output
            data = b''
            while True:
                chunk = s.recv(4096)
                data += chunk
                if b'What mode did I use?' in data or b'The flag is:' in data:
                    break

            text = data.decode()
            print(text)  # Optional

            # Check again for the flag
            if "The flag is:" in text:
                print("\nHere's the flag:")
                print(text)
                break

            # Extract output
            match = re.search(r"Output: ([0-9a-f]{64})", text)
            if not match:
                print("Output not found.")
                break

            output = match.group(1)
            mode = 'ECB' if is_ecb(output) else 'CBC'
            print(f"Detected mode: {mode}")

            s.sendall((mode + '\n').encode())

        print("Done with the session.")

if __name__ == '__main__':
    main()
