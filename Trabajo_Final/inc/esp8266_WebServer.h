/*=============================================================================
 * Copyright (c) 2020, Fabiola de las Casas <fabioladelascasas@gmail.com>
 * All rights reserved.
 * License: Free
 * Date: 2020/10/09
 * Version: v1.1
 *===========================================================================*/


#ifndef ESP8266_WEBSERVER_H_
#define ESP8266_WEBSERVER_H_

/*==================[ Inclusiones ]============================================*/
#include "sapi.h"
#include "esp8266_WebServer.h"
#include "sd_read.h"

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================[ Definiciones y Macros ]==================================*/
// El maximo tiempo que se espera una respuesta del modulo ESP8266
#define WIFI_MAX_DELAY  60000
#define LED_ERROR_ESP	LED2
#define LED_OK			LEDG

/*==================[ Definiciones de datos internos ]=========================*/

/*==================[ Definiciones de datos externos ]=========================*/

/*==================[ Declaraciones de funciones internas ]====================*/

/*==================[ Declaraciones de funciones externas ]====================*/

void WebServer_init( char * wifiName, char * wifiPass );
void WebServer_load( void );

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
}
#endif

/*==================[end of file]============================================*/

#endif /* ESP8266_WEBSERVER_H_ */
