#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#define MAXTIMINGS  85
#define DHTPIN    7
int dht11_dat[5] = { 0, 0, 0, 0, 0 };
 
float degrees_c2f(int whole, int decimal) 
{
  float c = whole + (decimal / 10.0);
  return (c * 9.0 / 5.0) + 32;
}

void read_dht11_dat()
{
  uint8_t laststate = HIGH;
  uint8_t counter   = 0;
  uint8_t j   = 0, i;
  float f; 
 
  dht11_dat[0] = dht11_dat[1] = dht11_dat[2] = dht11_dat[3] = dht11_dat[4] = 0;
 
  pinMode( DHTPIN, OUTPUT );
  digitalWrite( DHTPIN, LOW );
  delay( 18 );
  digitalWrite( DHTPIN, HIGH );
  delayMicroseconds( 40 );
  pinMode( DHTPIN, INPUT );
 
  for ( i = 0; i < MAXTIMINGS; i++ )
  {
    counter = 0;
    while ( digitalRead( DHTPIN ) == laststate )
    {
      counter++;
      delayMicroseconds( 1 );
      if ( counter == 255 )
      {
        break;
      }
    }
    laststate = digitalRead( DHTPIN );
 
    if ( counter == 255 )
      break;
 
    if ( (i >= 4) && (i % 2 == 0) )
    {
      dht11_dat[j / 8] <<= 1;
      if ( counter > 16 )
        dht11_dat[j / 8] |= 1;
      j++;
    }
  }
 
  if ( (j >= 40) &&
       (dht11_dat[4] == ( (dht11_dat[0] + dht11_dat[1] + dht11_dat[2] + dht11_dat[3]) & 0xFF) ) )
  {
    time_t rawtime;
    struct tm * timeinfo;
  
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    //printf ( "Current local time and date: %s", asctime (timeinfo) );

    f = degrees_c2f(dht11_dat[2], dht11_dat[3]);
    char *timestamp = asctime(timeinfo);
    timestamp[24] = ' ';
    printf( "%s- Humidity = %d.%d %% Temperature = %d.%d C (%.1f F)\n",
      timestamp, dht11_dat[0], dht11_dat[1], dht11_dat[2], dht11_dat[3], f );
  }else  {
    printf( "Data not good, skip\n" );
  }
}
 
int main( void )
{
  printf( "Raspberry Pi wiringPi DHT11 Temperature test program\n" );
 
  if ( wiringPiSetup() == -1 )
    exit( 1 );
 
  while ( 1 )
  {
    read_dht11_dat();
    delay( 1000 * 60 ); 
  }
 
  return(0);
}
