/*=============================================================================
 * Copyright (c) 2020, Fabiola de las Casas <fabioladelascasas@gmail.com>
 * All rights reserved.
 * License: Free
 * Date: 2020/10/09
 * Version: v1.1
 *===========================================================================*/

#ifndef _SD_READ_H_
#define _SD_READ_H_

/*==================[ Inclusiones ]============================================*/
#include <string.h>
#include "sapi.h"
#include "ff.h"       // <= Biblioteca FAT FS
#include "fssdc.h"    // API de bajo nivel para unidad "SDC:" en FAT FS
#include "ffconf.h"

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================[ Definiciones y Macros ]==================================*/
#define LED_ERROR_SD	LEDR
#define LED_OK			LEDG
#define TIME_FF_PROC	10
#define DELAY_SD		1000
#define LEN_HTML_END	7		// Los archivos html terminan </html> --> 7 bytes
#define MAX_HTTP_WEB_LENGHT   1500

/*==================[ Definiciones de datos internos ]=========================*/

/*==================[ Definiciones de datos externos ]=========================*/

/*==================[ Declaraciones de funciones internas ]====================*/

/*==================[ Declaraciones de funciones externas ]====================*/

void disk_timerproc(void);
void SD_search_file( char *extension, char *fname );
void SD_init( void );
void SD_load_html( char *file_name );
void SD_wifi_config(char * wifiName, char * wifiPass, char *wifi_file);

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
}
#endif

/*==================[end of file]============================================*/
#endif /* #ifndef _SD_READ_H_ */
