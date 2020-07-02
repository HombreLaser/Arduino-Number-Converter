
#ifndef Convert_h
#define Convert_h

#include "Arduino.h"

class Convert
{
  public:
    Convert();
    long binaryToDecimal(String value);
    long hexaToDecimal(String value);
    long octalToDecimal(String value);
	long base6ToDecimal(String value);
	long base20ToDecimal(String value);
    String decimalToBinary(long value);
    String decimalToHexa(long value);
    String decimalToOctal(long value);
	String decimalToBase6(long value);
	String decimalToBase20(long value);
	String decimalToBase6Float(float value);
	String decimalToHexaFloat(float value);
	String decimalToBinaryFloat(float value);
	String decimalToBase20Float(float value);
  private:
  	String fourBitsToHex(String value);
};

#endif
