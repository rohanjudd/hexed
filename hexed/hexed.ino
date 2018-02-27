// Hexed Game 
// Rohan Judd Feb 2018

class Hex_Byte
{
  byte value = 0;
  byte high = 0;
  byte low = 0;
  
  public:
  Hex_Byte(byte b)
  {
    set_value(b);
  }

  void set_value(byte b)
  {
    value = b;
    high = value >> 4;
    low = value & 0x0F;
  }

  byte get_value(){return value;}

  byte get_high()
  {
    return value;
  }

   byte get_low()
  {
    return value;
  }

  void generate()
  {
    set_value(random(0,255));
  }

  String get_hex_string()
  {
    String output = "";
    output += nibble_to_char(high);
    output += nibble_to_char(low);
    return output;
  }

  char nibble_to_char(byte b)
  {
    if(b < 10)
    {
      return b + 48;
    }
    else
    {
      return b - 10 + 65;
    }
  }
};

byte guess = 0;
int score = 0;

Hex_Byte target(0);

void setup() 
{
  Serial.begin(115200);
  while(!Serial)
  Serial.println("Hexed");
  print_target();
}

void loop() 
{
  target.generate();
  print_target();
  delay(400);
}

void print_target()
{
  Serial.print("DEC: ");
  Serial.print(target.get_value());
  Serial.print("  HEX: ");
  Serial.println(target.get_hex_string());
}



  
