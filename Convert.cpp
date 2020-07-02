#include "Arduino.h"
#include "Convert.h"

Convert::Convert(){}

/**
  1: Convert the string into char array
  2: Use char array with cpp strtol and base

  Reference: http://www.cplusplus.com/reference/cstdlib/strtol/
*/
long Convert::binaryToDecimal(String value){
    int base = 2; 
    int length = value.length() +1;
    char valueAsArray[length];
    value.toCharArray(valueAsArray, length);
    
    return strtol(valueAsArray, NULL, base);
}

/**
  1: Convert the string into char array
  2: Use char array with cpp strtol and base

  Reference: http://www.cplusplus.com/reference/cstdlib/strtol/
*/
long Convert::hexaToDecimal(String value){
    int base = 16;
    int length = value.length() +1;
    char valueAsArray[length];
    value.toCharArray(valueAsArray, length);
    return strtol(valueAsArray, NULL, base);
}

/**
  1: Convert the string into char array
  2: Use char array with cpp strtol and base

  Reference: http://www.cplusplus.com/reference/cstdlib/strtol/
*/
long Convert::octalToDecimal(String value){
    int base = 8;
    int length = value.length() +1;
    char valueAsArray[length];
    value.toCharArray(valueAsArray, length);
    return strtol(valueAsArray, NULL, base);
}

long Convert::base6ToDecimal(String value){
	int base = 6;
    int length = value.length() +1;
    char valueAsArray[length];
    value.toCharArray(valueAsArray, length);
    return strtol(valueAsArray, NULL, base);
}

long Convert::base20ToDecimal(String value){
	int base = 20;
    int length = value.length() +1;
    char valueAsArray[length];
    value.toCharArray(valueAsArray, length);
    return strtol(valueAsArray, NULL, base);
}

/**
  Using the divide by 2 and remainder method to create a binary string

  Reference: http://www.wikihow.com/Convert-from-Decimal-to-Binary
*/
String Convert::decimalToBinary(long value){
  String result = "";
  if(value == 0){
    return "0";
  }else{
    while(value > 0){
      if((value % 2) == 0){
        result = "0" + result;
      }else{
        result = "1" + result;
      }
      value /= 2;
    }
  }
  return result;
}


/**
  1: Convert the decimal value into a binary String
  2: Each 4 bit pattern is translated into hexadecimal

  Reference: http://www.rapidtables.com/convert/number/how-binary-to-hex.htm
*/
String Convert::decimalToHexa(long value){
  String valueAsBinary = decimalToBinary(value);
  String valueAsHexa = "";
  String tmp = "";

  // Loop over the binary list from right to left
  for(int i = valueAsBinary.length() ; i > 0; i--){
    if(tmp.length() == 4){
      valueAsHexa = fourBitsToHex(tmp) + valueAsHexa;
      tmp = "";
    }
    tmp = valueAsBinary.substring(i, i-1) + tmp;
  }

  valueAsHexa = fourBitsToHex(tmp) + valueAsHexa;
  return valueAsHexa;
}

/**
  1: Convert the decimal value into a binary String
  2: Each 3 bit pattern is translated into octal

  Reference: http://www.wikihow.com/Convert-Binary-to-Octal-Number
*/
String Convert::decimalToOctal(long value){
  String valueAsBinary = decimalToBinary(value);
  String valueAsOctal = "";
  String tmp = "";

  // Loop over the binary list from right to left
  for(int i = valueAsBinary.length() ; i > 0; i--){
    if(tmp.length() == 3){
      valueAsOctal = String(binaryToDecimal(tmp)) + valueAsOctal;
      tmp = "";
    }
    tmp = valueAsBinary.substring(i, i-1) + tmp;
  }

  valueAsOctal = String(binaryToDecimal(tmp)) + valueAsOctal;
  return valueAsOctal;

}

//Divide entre 6
String Convert::decimalToBase6(long value){
  String result = "";
  short int n;
  if(value == 0){
    return "0";
  }else{
    while(value > 0){
      n = value % 6;
	  result = String(n) + result;
      value /= 6;
    }
  }
	return result;
}

String Convert::decimalToBase20(long value){
	String result = "";
	short int n;
	if(value == 0){
		return "0";
	}else{
		while(value > 0){
			n = value % 20;
			switch(n){
				case 10:
					result = "A" + result;
				break;
				case 11:
					result = "B" + result;
				break;
				case 12:
					result = "C" + result;
				break;
				case 13:
					result = "D" + result;
				break;
				case 14:
					result = "E" + result;
				break;
				case 15:
					result = "F" + result;
				break;
				case 16:
					result = "G" + result;
				break;
				case 17:
					result = "H" + result;
				break;
				case 18:
					result = "I" + result;
				break;
				case 19:
					result = "J" + result;
				break;
				default:
					result = String(n) + result;
				break;
			}
			value /= 20;
		}
		return result;
	}
}

/**
	Este método toma la parte fraccionaria de un número decimal
	y la multiplica por la base para así conseguir la parte 
	fraccionaria de su equivalente en base 6. Sólo repite el
	proceso dos veces. Si la parte fraccionaria es igual a 0 
	regresará "00", los dos decimales que muestra la calculadora
	por defecto.
**/

String Convert::decimalToBase6Float(float value){
	String result = "";
	float n;
	bool integerVerifier = false;
	n = value - round(value - 0.5);
	result = decimalToBase6(value) + ".";
	if(n != 0){
		for(int i = 1; i <= 2; i++){
			while(!integerVerifier){
				n *= 6; 
				if(n >= 1){
					result += String(round(n - 0.5));
					n -= round(n - 0.5);
					if(n == 0){
						integerVerifier = true;
					}
				}else{
					n *= 6;
				}
			}
		}
	}else{
		result += "00";
	}
	return result;
}

String Convert::decimalToHexaFloat(float value){
	String result = "";
	float n;
	short int roundedN;
	bool integerVerifier = false;
	n = value - round(value - 0.5);
	result = decimalToHexa(value) + ".";
	if(n != 0){
		for(int i = 1; i <= 2; i++){
			while(integerVerifier == false){
				n *= 16; 
				if(n >= 1){
					roundedN = round(n - 0.5);
					switch(roundedN){
						case 10:
							result += "A";
						break;
						case 11:
							result += "B";
						break;
						case 12:
							result += "C";
						break;
						case 13:
							result += "D";
						break;
						case 14:
							result += "E";
						break;
						case 15:
							result += "F";
						break;
						default:
							result += String(roundedN);
						break;
					}
					n -= round(n - 0.5);
					if(n == 0){
						integerVerifier = true;
					}
				}else{
					n *= 16;
				}
			}
		}
	}else{
		result += "00";
	}
	return result;
}

String Convert::decimalToBinaryFloat(float value){
	String result = "";
	float n;
	bool integerVerifier = false;
	n = value - round(value - 0.5);
	result = decimalToBinary(value) + ".";
	if(n != 0){
		for(int i = 1; i <= 2; i++){
			while(integerVerifier == false){
				n *= 2; 
				if(n >= 1){
					result += String(round(n - 0.5));
					n -= round(n - 0.5);
					if(n == 0){
						integerVerifier = true;
					}
				}else{
					n *= 2;
				}
			}
		}
	}else{
		result += "00";
	}
	return result;
}

String Convert::decimalToBase20Float(float value){
	String result = "";
	float n;
	short int roundedN;
	bool integerVerifier = false;
	n = value - round(value - 0.5);
	result = decimalToBase20(value) + ".";
	if(n != 0){
		for(int i = 1; i <= 2; i++){
			while(integerVerifier == false){
				n *= 16; 
				if(n >= 1){
					roundedN = round(n - 0.5);
					switch(roundedN){
						case 10:
							result += "A";
						break;
						case 11:
							result += "B";
						break;
						case 12:
							result += "C";
						break;
						case 13:
							result += "D";
						break;
						case 14:
							result += "E";
						break;
						case 15:
							result += "F";
						break;
						case 16:
							result += "G";
						break;
						case 17:
							result += "H";
						break;
						case 18:
							result += "I";
						break;
						case 19:
							result += "J";
						break;
						default:
							result += String(roundedN);
						break;
					}
					n -= round(n - 0.5);
					if(n == 0){
						integerVerifier = true;
					}
				}else{
					n *= 16;
				}
			}
		}
	}else{
		result += "00";
	}
	return result;
}

/**
  This method will translate a 4 bit binary value into the correct hexadecimal digit
*/
String Convert::fourBitsToHex(String value){
  int decValue = binaryToDecimal(value);
  switch(decValue){
    case 10:
      return "A";
    break;
    case 11:
      return "B";
    break;
    case 12:
      return "C";
    break;
    case 13:
      return "D";
    break;
    case 14:
      return "E";
    break;
    case 15:
      return "F";
    break;
    default:
      return String(decValue);
    break;
  }
}


