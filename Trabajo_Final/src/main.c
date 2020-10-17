/*=============================================================================
 * Copyright (c) 2020, Fabiola de las Casas <fabioladelascasas@gmail.com>
 * All rights reserved.
 * License: Free
 * Date: 2020/10/09
 * Version: v1.1
 *===========================================================================*/

/*==================[ Inclusiones ]============================================*/
#include "main.h"

/*==================[ Definiciones y Macros ]==================================*/
#define FILE_EXTENSION		"*.html"	// Modifico esto en funcion al tipo de archivo que quiero buscar
#define ARCHIVO_CONFIG_WIFI	"wifi_config.txt"

/*==================[ Funcion principal]======================================*/

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main( void ){

	char file_name[20];
	char wifiName[20];
	char wifiPass[20];

   // ---------- CONFIGURACIONES ------------------------------
   // Inicializar y configurar la plataforma
   boardConfig();

   uartConfig( UART_USB, BAUD_RATE );

   printf("Inicializando\n");
   printf("\r\n");

   // Funcion para inciar la comunicación SPI y
   // configurar el driver de la tarjeta SD
   SD_init();

   // Lectura de configuracion de Wifi desde la SD
   wifi_config(wifiName, wifiPass, ARCHIVO_CONFIG_WIFI);

   // Busqueda de archivo con extension .html
   search_file( FILE_EXTENSION, file_name );

   // Lectura de archivo html encontrado
   load_html( file_name );

   // Inicializacion del servidor Web
   WebServer_init(wifiName, wifiPass);

   // ---------- REPETIR POR SIEMPRE --------------------------
   while( TRUE )
   {
	   WebServer_load();
   }

   // NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta
   // directamenteno sobre un microcontroladore y no es llamado/ por ningun
   // Sistema Operativo, como en el caso de un programa para PC.
   return 0;
}
/*==================[fin del archivo]========================================*/
