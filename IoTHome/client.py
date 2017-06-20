# -*- cofing: utf8 -*-

from socket import *
from select import select
import sys

HOST = '192.168.1.1'
PORT = 8080
BUFSIZE = 1024
ADDR = (HOST,PORT)

clientSocket = socket(AF_INET,SOCK_STREAM)
try:
	print('cool')
	clientSocket.connect(ADDR)
except Exception as e:
	print('fail')
	sys.exit()
print('서버에 연결되었습니다 : %s:%s' % ADDR)

def prompt():
	sys.stdout.write('<out>')
	sys.stdout.flush()

while True :
	try :
		connection_list = [sys.stdin, clientSocket]

		read_socket, write_socket, error_socket = select(connection_list, [], [], 10)

		for sock in read_socket :
			if sock == clientSocket :
				data = sock.recv(BUFSIZE)
				if not data:
					print('disconnect')
					clientSocket.close()
					sys.exit()
				else:
					print('%s'% data)
					prompt()
			else:
				message = sys.stdin.readline()
				clientSocket.sendto(message.encode('utf-8'),ADDR)
				prompt()
	except KeyboardInterrupt :
		clientSocket.close()
		sys.exit()
