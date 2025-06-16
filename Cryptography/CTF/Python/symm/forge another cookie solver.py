import socket
from Crypto.Util.number import bytes_to_long, long_to_bytes

HOST = "130.192.5.212"
PORT = 6552
BLOCK_SIZE = 16


def receive_until(sock, marker=b"> ", timeout=2):
    sock.settimeout(timeout)
    data = b""
    try:
        while not marker in data:
            part = sock.recv(4096)
            if not part:
                break
            data += part
    except socket.timeout:
        pass
    return data


def send_line(sock, line: str):
    sock.sendall(line.encode() + b"\n")


def split_blocks(data, size=16):
    return [data[i : i + size] for i in range(0, len(data), size)]


def main():
    with socket.create_connection((HOST, PORT)) as sock:
        receive_until(sock, b"Username: ")
        username = "A" * 12 + "admintrue"
        print(f"{username}")
        send_line(sock, username)

        data = receive_until(sock, b"\n")
        print("Cookie:", repr(data))

        lines = data.decode().splitlines()
        cookie_line = next(line for line in reversed(lines) if line.strip().isdigit())
        cookie_bytes = long_to_bytes(int(cookie_line))

        blocks = split_blocks(cookie_bytes)
        print(f"Total blocks: {len(blocks)}")

        forged = b"".join(blocks[:2] + [blocks[1]])

        print(f"{len(forged)}")

        receive_until(sock, b"> ")
        send_line(sock, "flag")

        receive_until(sock, b"Cookie: ")
        send_line(sock, str(bytes_to_long(forged)))

        response = receive_until(sock)
        print(response.decode())


if __name__ == "__main__":
    main()
