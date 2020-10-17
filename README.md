# Webserver con carga de datos desde tarjeta SD para EDU-CIAA-NXP

### Permite la carga de un servidor HTTP y la configuración de la red Wifi almacenados en una tarjeta SD

El programa se encuentra modularizado, diviendo asi la configuración y lectura del modulo de tarjeta SD y la configuración y carga del servido HTTP.

El conexiado del módulo ESP-01 y el módulo lector de tarjetas SD es el estandar para la EDU-CIAA-NXP, excepto el CH_PD del ESP-01 que se conecta al GPIO1.

* __void search_file( char *extension, char *fname )__ :
Permite buscar archivos que tengan el nombre o la extensión indicados en *extension*.
Para este programa se configura la extension en el main.c con __#define FILE_EXTENSION		"*.html"__

* __void wifi_config(char * wifiName, char * wifiPass, char *wifi_file)__ : 
Lee el archivo con el nombre indicado en el main.c con **#define ARCHIVO_CONFIG_WIFI** y levanta los datos de la red Wifi donde se va a conectar (SSDI y contraseña).


### Archivo configuración Wifi "wifi_config.txt"

* Debe tener las siguientes dos lineas con la información correspondiente:

WIFI_SSID: nombre_red

WIFI_PASSWORD: contraseña_red

* Se puede cambiar el nombre del archivo modificando **#define ARCHIVO_CONFIG_WIFI	"wifi_config.txt"** con el nombre deseado.

### Archivo HTML

* Si hay más de un archivo html en la tarjeta SD, se levantará el que lea primero el programa.
* El archivo no debe estar guardado en ninguna carpeta dentro de la tarjeta SD.
* No puede tener un tamaño mayor a 1.5kB

### Indicadores

* El LEDR indica un error en el proceso de configuración o lectura de archivos de la tarjeta SD.

* El LED2 indica un error en el proceso de configuración o conexión del módulo ESP-01







