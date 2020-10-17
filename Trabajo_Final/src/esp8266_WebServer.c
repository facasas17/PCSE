/*=============================================================================
 * Copyright (c) 2020, Fabiola de las Casas <fabioladelascasas@gmail.com>
 * All rights reserved.
 * License: Free
 * Date: 2020/10/09
 * Version: v1.1
 *===========================================================================*/


/*==================[ Inclusiones ]============================================*/
#include "esp8266_WebServer.h"

//*==================[ Definiciones de datos externos ]=========================*/
extern char HttpWebPageBody[MAX_HTTP_WEB_LENGHT - LEN_HTML_END];	// Acepta leer un archivo de como maximo el largo admitido para enviar al web server.
extern char HttpWebPageEnd[LEN_HTML_END];
extern char HttpWebPageHeader[20];

/*==================[definiciones de funciones internas]=====================*/
void WebServer_init( char * wifiName, char * wifiPass )
{
	bool_t error = FALSE;
	delay_t wifiDelay;

	// Configura GPIO1 como output para el EN del ESP-01
	gpioInit(GPIO1, GPIO_OUTPUT);
	gpioWrite(GPIO1, ON);

	stdioPrintf(UART_USB, "\n\rConfigurando servidor HTTP. Puede tardar hasta 1 minuto.");

	// Configura un delay para salir de la configuracion en caso de error.
	delayConfig(&wifiDelay, WIFI_MAX_DELAY);

	// Mientras no termine la configuracion o mientras no pase el tiempo maximo, ejecuta la configuracion.
	// A la configuracion se le pasa nombre y contrasenia de RED
	while (!esp8266ConfigHttpServer("Super Intranet", "TheEfes1990") && !error)
	{
	  if (delayRead(&wifiDelay))
	  {
		 error = TRUE;
	  }
	}

	// Avisa al usuario como salio la configuracion
	if (!error)
	{
	  stdioPrintf(UART_USB, "\n\rServidor HTTP configurado. IP: %s", esp8266GetIpAddress());
	  // Enciende LED_OK indicando que el modulo esta configurado.
	  gpioWrite(LED_OK, TRUE);
	} else
	{
	  stdioPrintf(UART_USB, "\n\rError al configurar servidor HTTP.");
	  // Enciende LED_ERROR_ESP indicando que el modulo esta en error.
	  gpioWrite(LED_ERROR_ESP, TRUE);
	}
}

void WebServer_load( void )
{
	delay_t wifiDelay;
	bool_t error = FALSE;

	// Si llego una peticion al servidor http
	if (esp8266ReadHttpServer())
	{
		error = FALSE;
		// Configura un delay para salir de la configuracion en caso de error.
		delayConfig(&wifiDelay, WIFI_MAX_DELAY);

		// Mientras no termine el envio o mientras no pase el tiempo maximo, ejecuta el envio.
		while (!esp8266WriteHttpServer(HttpWebPageHeader, HttpWebPageBody, HttpWebPageEnd) && !error)
		{
			if (delayRead(&wifiDelay))
			{
				error = TRUE;
			}
		}

		// Avisa al usuario como fue el envio
		if (!error)
		{
			stdioPrintf(UART_USB, "\n\rPeticion respondida al cliente HTTP %d.", esp8266GetConnectionId());
			gpioToggle(LED_OK);
		} else
		{
			stdioPrintf(UART_USB, "\n\rPeticion no respondida al cliente HTTP %d.", esp8266GetConnectionId());
			gpioToggle(LED_ERROR_ESP);
		}
	}
}
