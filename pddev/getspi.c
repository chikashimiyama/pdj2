#include "m_pd.h"
#include "wiringPi.h"
#include "wiringPiSPI.h"
#define CS 12

static t_class *getspi_class;

typedef struct _getspi
{
  t_object x_obj;
  t_outlet *x_outlet;
  unsigned char data[2];  
} t_getspi;


void getspi_bang(t_getspi *x){
  int res;
  unsigned char value;
  digitalWrite(CS, LOW);
  res = wiringPiSPIDataRW(1, &x->data[0], 2);
  digitalWrite(CS, HIGH);
  
  value = (x->data[0] << 2) + (x->data[1] >> 6);
  outlet_float(x->x_outlet, (float)value);
}

void *getspi_new(void){
  int spi = wiringPiSPISetup(1, 500000);
  wiringPiSetup();
  pinMode(CS, OUTPUT); 
  digitalWrite(CS, HIGH);
  if(spi == -1){
    post("cannot initialize SPI\n");
  }

  t_getspi *x = (t_getspi *)pd_new(getspi_class);
  x->x_outlet = outlet_new(&x->x_obj, gensym("float"));
  return (void *)x;
}

void getspi_setup(void){
  getspi_class = class_new(gensym("getspi"),
			   (t_newmethod)getspi_new, 
			   0, 
			   sizeof(t_getspi), CLASS_DEFAULT, 
			   0);
  class_addbang(getspi_class, getspi_bang);
}
