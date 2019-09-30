#include <keyboard.h>
#include <io.h>

char char_map[] =
{
  '\0','\0','1','2','3','4','5','6',
  '7','8','9','0','\'','¡','\0','\0',
  'q','w','e','r','t','y','u','i',
  'o','p','`','+','\0','\0','a','s',
  'd','f','g','h','j','k','l','ñ',
  '\0','º','\0','ç','z','x','c','v',
  'b','n','m',',','.','-','\0','*',
  '\0','\0','\0','\0','\0','\0','\0','\0',
  '\0','\0','\0','\0','\0','\0','\0','7',
  '8','9','-','4','5','6','+','1',
  '2','3','0','\0','\0','\0','<','\0',
  '\0','\0','\0','\0','\0','\0','\0','\0',
  '\0','\0'
};

void keyboard_routine(){
  //Agafem el valor del port del teclat
	unsigned char port_data_keyboard = inb(0x60);

  //Guardem el valor de quin caracter és i eliminem el bit
  //de si la tecla esta pulsada o no	
  unsigned char key_value = port_data_keyboard & 0b01111111;

  //Extreiem el valor que diu si la tecla esta pulsada
  char pressed = port_data_keyboard >> 7;

  if (pressed == 0){
    if(char_map[key_value] != '\0'){
      char value = char_map[key_value];
      printc_xy(0,0,value);
    }
    else {
      printc_xy(74,24,'C');
    }
  }
}
	
