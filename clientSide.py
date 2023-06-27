import time
import socket
import sys

print("\nWelcome to Chat Room(21BDS0064)\n")
time.sleep(1)
client_socket = socket.socket()
host = socket.gethostname()
ip = socket.gethostbyname(host)
print(host, "(", ip, ")\n")
server_address = input(str("Enter server address: "))
client_name = input(str("\nEnter your name: "))
port = 80
print("Connecting to ", server_address, "(", port, ")\n")
time.sleep(1)
client_socket.connect((server_address, port))
print("Successfully connected\n")
client_socket.send(client_name.encode())
server_name = client_socket.recv(1024)
server_name = server_name.decode()
print(server_name, "has joined the chat room. Enter 'exit' to exit chat room\n")
while True:
    received_message = client_socket.recv(1024)
    received_message = received_message.decode()
    print(server_name, ":", received_message)
    message = input(str("Me : "))
    if message == "exit":
        message = "Left chat room!"
        client_socket.send(message.encode())
        print("\n")
        break
    client_socket.send(message.encode())
