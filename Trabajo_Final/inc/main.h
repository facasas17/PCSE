/*=============================================================================
 * Copyright (c) 2020, Fabiola de las Casas <fabioladelascasas@gmail.com>
 * All rights reserved.
 * License: Free
 * Date: 2020/10/09
 * Version: v1.1
 *===========================================================================*/

#ifndef _MAIN_H_
#define _MAIN_H_

/*==================[ Inclusiones ]============================================*/
#include "sapi.h"
#include "sapi_esp8266.h"

#include "ff.h"       // <= Biblioteca FAT FS
#include "fssdc.h"    // API de bajo nivel para unidad "SDC:" en FAT FS
#include "ffconf.h"

#include "sd_read.h"
#include "esp8266_WebServer.h"

/*==================[ Definiciones y Macros ]==================================*/
#define LED_ERROR_ESP	LED2
#define LED_OK			LEDG
#define BAUD_RATE		115200
#define WIFI_MAX_DELAY  60000		// El maximo tiempo que se espera una respuesta del modulo ESP8266

/*==================[ Definiciones de datos globales ]=========================*/

FATFS fs;		// <-- FatFs work area needed for each volume
FIL fp;          // <-- File object needed for each open file

char HttpWebPageBody[MAX_HTTP_WEB_LENGHT - LEN_HTML_END];	// Acepta leer un archivo de como maximo el largo admitido para enviar al web server.
char HttpWebPageEnd[LEN_HTML_END];
char HttpWebPageHeader[20];


#endif /* _MAIN_H_ */
