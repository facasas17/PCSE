/*=============================================================================
 * Copyright (c) 2020, Fabiola de las Casas <fabioladelascasas@gmail.com>
 * All rights reserved.
 * License: Free
 * Date: 2020/10/09
 * Version: v1.1
 *===========================================================================*/


/*==================[ Inclusiones ]============================================*/
#include "sd_read.h"

/*==================[ Definiciones y Macros ]==================================*/

/*==================[ Definiciones de datos internos ]=========================*/

/*==================[ Definiciones de datos externos ]=========================*/
extern FATFS fs;		// <-- FatFs work area needed for each volume
extern FIL fp;          // <-- File object needed for each open file

extern char HttpWebPageBody[MAX_HTTP_WEB_LENGHT - LEN_HTML_END];	// Acepta leer un archivo de como maximo el largo admitido para enviar al web server.
extern char HttpWebPageEnd[LEN_HTML_END];
extern char HttpWebPageHeader[20];

/*==================[ Declaraciones de funciones internas ]====================*/
static void diskTickHook( void *ptr );

/*==================[ Definiciones de funciones]=====================*/

void SD_init( void )
{
	// SPI configuration
	spiConfig( SPI0 );

	// Inicializar el conteo de Ticks con resolucion de 10ms,
	// con tickHook diskTickHook
	tickConfig( TIME_FF_PROC );
	tickCallbackSet( diskTickHook, NULL );

	// Initialize SD card driver
	FSSDC_InitSPI ();
	// Give a work area to the default drive
	if( f_mount( &fs, "SDC:", 0 ) != FR_OK )
	{
	  // If this fails, it means that the function could
	  // not register a file system object.
	  // Check whether the SD card is correctly connected
	   while (1)
	   {
		   gpioToggle( LED_ERROR_SD );
		   printf("SD no disponible\n");
		   delay(DELAY_SD);
	   }
	}
}

void SD_search_file( char *extension, char *fname )
{
	DIR dir;         /* Directory object */
	FILINFO fno;
	char path[] = "SDC:/";

	if( f_findfirst(&dir, &fno, "", extension) != FR_OK )
	{
	   printf("\n\rNo se encontro ningun archivo con la extension %s", extension);
	   gpioWrite( LED_ERROR_SD, ON );
	}
	else
	{
		strcpy(fname, fno.fname);
	}
}

void SD_load_html( char *file_name )
{
	UINT size_read = 0;

	if( f_open( &fp, file_name, FA_READ | FA_WRITE ) == FR_OK )
	{
		if( f_size(&fp) > MAX_HTTP_WEB_LENGHT)
		{
			gpioWrite( LED_ERROR_SD, ON );
		}

		/* Leo la primera linea del archivo html y lo guardo en HttpWebPageHeader */
		f_gets(HttpWebPageHeader, sizeof(HttpWebPageHeader), &fp);

		/* Leo el archivo desde lo ultimo que leyo. */
		f_read( &fp, HttpWebPageBody, sizeof(HttpWebPageBody), &size_read );

		/* Me muevo hasta el ultimo byte leido que corresponde al tamaño de HttpWebPageBody */
		f_lseek( &fp, sizeof(HttpWebPageBody));

		f_gets(HttpWebPageEnd, sizeof(HttpWebPageEnd), &fp);

		f_close(&fp);
	 }
	 else
	 {
		 // Si no se pudo abrir el archivo
		 gpioWrite( LED_ERROR_SD, ON );
		 while (TRUE)
			 continue;
	 }
}

void SD_wifi_config(char * wifiName, char * wifiPass, char *wifi_file)
{
	char aux_name[50];
	char aux_pass[50];
	char *aux;

	uint8_t ssid_size = sizeof("WIFI_SSID:");
	uint8_t password_size = sizeof("WIFI_PASSWORD:");

	if( f_open( &fp, wifi_file, FA_READ | FA_WRITE ) == FR_OK )
	{
		f_gets(aux_name, sizeof(aux_name), &fp);
		f_gets(aux_pass, sizeof(aux_pass), &fp);
		f_close(&fp);
	}

	aux = aux_name + ssid_size;
	strcpy(wifiName, aux);
	aux = aux_pass + password_size;
	strcpy(wifiPass, aux);
}

/*==================[ Definiciones de funciones internas]=====================*/

static void diskTickHook( void *ptr )
{
   disk_timerproc();   // Disk timer process
}
