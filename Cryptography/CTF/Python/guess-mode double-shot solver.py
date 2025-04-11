import socket
import re
import os

HOST = '130.192.5.212'
PORT = 6532
MAX_TRIES = 129

def random_hex_string(length=64):
    return os.urandom(length // 2).hex()

def main():
    with socket.create_connection((HOST, PORT)) as s:
        s.settimeout(5)

        for i in range(MAX_TRIES):
            # Wait for first input prompt
            data = b''
            while True:
                chunk = s.recv(4096)
                data += chunk
                if b'Input:' in data or b'The flag is:' in data:
                    break

            text = data.decode()
            print(text)

            if "The flag is:" in text:
                print("\n🎉 FLAG FOUND 🎉")
                print(text)
                break

            # Generate input
            test_input = random_hex_string(64)
            s.sendall((test_input + '\n').encode())

            # Read first output
            data = b''
            while True:
                chunk = s.recv(4096)
                data += chunk
                if b'Output:' in data:
                    break

            output1 = re.search(rb'Output: ([0-9a-f]{64})', data)
            if not output1:
                print("First output not found.")
                break
            out1 = output1.group(1).decode()
            print(f"Output1: {out1}")

            # Wait for next input prompt
            while b'Input:' not in data:
                chunk = s.recv(4096)
                data += chunk
                if b'The flag is:' in data:
                    print("\n🎉 FLAG FOUND 🎉")
                    print(data.decode())
                    return

            s.sendall((test_input + '\n').encode())

            # Read second output
            data = b''
            while True:
                chunk = s.recv(4096)
                data += chunk
                if b'Output:' in data or b'The flag is:' in data:
                    break

            output2 = re.search(rb'Output: ([0-9a-f]{64})', data)
            if not output2:
                print("Second output not found.")
                break
            out2 = output2.group(1).decode()
            print(f"Output2: {out2}")

            # Determine mode
            mode = 'ECB' if out1 == out2 else 'CBC'
            print(f"Detected mode: {mode}")
            s.sendall((mode + '\n').encode())

        print("Done with all tries.")

if __name__ == '__main__':
    main()
