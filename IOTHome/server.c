#include <sys/types.h>
#include <sys/socket.h>
#include <stdio>
void main()
{
	int server;
	int client_addr_size;
	struct sockaddr_in server_addr;

	server = socket(AF_INET,SOCK_STREAM,0);
	if( -1 == server)
	{
		printf("fail");
		exit(1);
	}

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(8080);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if( -1 == bind( server_socket, (struct sockaddr*)&server_addr, sizeof( server_addr) ) )
	{
   	printf( "bind() 실행 에러\n");
   	exit( 1);
	}

	if( -1 == listen( server_socket, 5))
	{
    printf( "대기상태 모드 설정 실패\n");
    exit( 1);
	}
	while(1){
		client_addr_size = sizeof( client_addr);
		client_socket = accept( server_socket, (struct
			sockaddr*)&client_addr,&client_addr_size);
		if ( -1 == client_socket)
		{
	  	printf( "클라이언트 연결 수락 실패\n");
	   	exit( 1);
		}
		read ( client_socket, buff_rcv, BUFF_SIZE);
		printf("receive : %s\n",buff_rcv);

		sprintf( buff_snd, "%d : %s", strlen( buff_rcv), buff_rcv);
		write( client_socket, buff_snd, strlen( buff_snd)+1);
		close( client_socket);
	}
}
