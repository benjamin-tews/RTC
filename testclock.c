#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/* Puffer fuer die RTC-Daten */
#define BUFSIZE 7

/* Verwende I2C 1 */
#define I2CADDR "/dev/ds3231"

/* defined in <linux/i2c-dev.h> */
/* #define I2C_SLAVE 0x703 */

/* Adresse des RTC-Chips */
#define RTC 0x68

int main()
  {
  int Device;          /* Device-Handle */
  char Date[BUFSIZE];  /* Datenpuffer   */
  int i;

  /* I2C aktivieren  */
  if ((Device = open(I2CADDR, O_RDWR)) < 0)
    {
    printf("I2C-Modul kann nicht geladen werden!\n");
    return -1;
    }

  /*  Port und Adresse setzen */
/*  if (ioctl(Device, I2C_SLAVE, RTC) < 0)
    {
    printf("RTC-Deviceadresse wurde nicht gefunden!\n");
    exit(1);
    }
*/
  /* Pointer auf Adresse 0 (Startadresse) setzen */
  Date[0] = 0x00;

  /* Uhrzeit einlesen */
  if (read(Device, Date, BUFSIZE) != BUFSIZE)
    {
    printf("Fehler beim Lesen der Daten!\n");
    return -1;
    }
  else
    {
    /* Werte von BCD in Dezimal umwandeln */
    for(i = 0; i < BUFSIZE; i++)
      {
      Date[i] = (Date[i] & 0x0f) + 10 * (Date[i] >> 4);
      }

    /* Ausgabe von Uhrzeit und Datum */
    printf("\n");
    printf("Uhrzeit: %02d:%02d:%02d\n", Date[2],Date[1],Date[0]);
    printf("Datum:   %02d.%02d.%04d\n", Date[4],Date[5],Date[6] + 2000);
    switch(Date[3])
      {
      case 1: printf("Sonntag");  break;
      case 2: printf("Montag");   break;
      case 3: printf("Dienstag"); break;
      case 4: printf("Mittwoch"); break;
      case 5: printf("Donnerstag"); break;
      case 6: printf("Freitag");  break;
      case 7: printf("Samstag");  break;
      }
    printf("\n");
    }

  close(Device);
  return 0;
  }
