#include "Client.h"

#pragma comment(lib,"ws2_32.lib")

using namespace std;


/*-------------------------------------------------------------------*
 * main()                                                            *
 *                                                                   *
 * Entrada:     No posee                                             *
 *                                                                   *
 * Salida:      No posee                                             *
 *                                                                   *
 * Retorno:     No posee                                             *
 *                                                                   *
 * Descripcion: Rutina principal del programa                        *
 *-------------------------------------------------------------------*/
int main()
{
	// Variable de longitud
	int send_len = 0;
	int recv_len = 0;
	
	// Variables para búfer de envío y recepción
	//char send_buf[100];
	char recv_buf[100];
	
	// Variables para el socket 
	SOCKET s_server;
	
	// Variables para direccion del servidor y cliente
	SOCKADDR_IN server_addr;
	int port;

	//Variables de la señal y filtro
	double y_in;
	float fc;
	float y_filter;
	IIR_1order IIR_1order_handle;
	
	initialization();
	// Complete la información del servidor 
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	cout << "Enter port number for communication" << endl;
	cin >> port;
	server_addr.sin_port = htons(port);
	
	cout << "Enter the cutoff frequency of the low pass filter" << endl;
	cin >> fc;
	IIR_1order_init(&IIR_1order_handle, fc);

	// Crear socket
	s_server = socket(AF_INET, SOCK_STREAM, 0);
	if (connect(s_server, (SOCKADDR*)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
		cout << "Failed to connect to server" << endl;
		WSACleanup();
	}
	else
	{
		cout << "The connection to the server is successful" << endl;
	}
	
	// Bucle para recibir datos 
	while (1)
	{
		recv_len = recv(s_server, recv_buf, 100, 0);
		y_in = atof(recv_buf);
		if (recv_len < 0)
		{
			cout << "Accept the error and exit" << endl;
			break;
		}
		else
		{
			IIR_1order_handle.Vi = (float )y_in; // Suponiendo que ADCresult es el resultado del muestreo de ADC
			IIR_1order_FUNC(&IIR_1order_handle);    //usage
			y_filter = IIR_1order_handle.Vo; // FilteredResult almacena el resultado filtrado
			
			cout << "Signal sent by server:" << recv_buf << endl;
			cout << "Filtered signal:" << y_filter << endl;
		}
	}
	

	// Cerrar la conexion
	closesocket(s_server);
	
	// Liberar recursos DLL
	WSACleanup();
	return 0;
}

/*-------------------------------------------------------------------*
 * initialization()                                                  *
 *                                                                   *
 * Entrada:     No posee                                             *
 *                                                                   *
 * Salida:      No posee                                             *
 *                                                                   *
 * Retorno:     No posee                                             *
 *                                                                   *
 * Descripcion: Inicializa la libreria de sockets                    *
  *------------------------------------------------------------------*/
void initialization(void)
{
	// Inicializa la biblioteca de sockets
	WORD w_req = MAKEWORD(2, 2);
	
	// Numero de version  
	WSADATA wsadata;
	int err;
	
	err = WSAStartup(w_req, &wsadata);
	if (err != 0)
	{
		cout << "Error initializing socket library" << endl;
	}
	else
	{
		cout << "Sockets library initialized successfully" << endl;
	}
	
	// Verifica el número de versión
	if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wHighVersion) != 2)
	{
		cout << "Socket library version number does not match" << endl;
		WSACleanup();
	}
	else
	{
		cout << "Socket library version is correct" << endl;
	}
}

