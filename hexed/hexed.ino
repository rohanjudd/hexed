// Hexed Game 
// Rohan Judd Feb 2018

class Target
{
  byte value = 0;
  byte high = 0;
  byte low = 0;
  
  public:
  Target(byte b)
  {
  }

  void set_value(byte b)
  {
    value = b;
    high = value >> 4;
    low = value & 0x0F;
  }

  byte get_value()
  {
    return value;
  }

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
    output += String(high,HEX);
    output += String(low,HEX);
    return output;
  }

  String get_hex_string2()
  {
    String output = "";
    return "";
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

Target target(0);

void setup() 
{
  Serial.begin(115200);
  while(!Serial)
  Serial.println("Hexed");
  Serial.println(target.get_value());
  Serial.println(target.get_hex_string());
}

void loop() 
{
  target.generate();
  Serial.println(target.get_value());
  Serial.println(target.get_hex_string());
  Serial.println(target.get_hex_string());
  delay(400);
}
