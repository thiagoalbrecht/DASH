class JSON
{
public:
  String handler(String var, String val, String varType)
  {
    String JSONString;
    if (varType == "bool")
    {
      if (val == "true")
        JSONString = "{\"" + var + "\":true}";
      else
        JSONString = "{\"" + var + "\":false}";
    }
    else if (varType == "num")
      JSONString = "{\"" + var + "\":" + val + "}";
    else
      JSONString = "{\"" + var + "\":\"" + val + "\"}";
    return JSONString;
  }
};
JSON json;

void webpage()
{
  server.send(200,"text/html", webpageCode);
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t welength)
{
  String JSON;
  String varType;
  String payloadString = (const char *)payload;
  Serial.print("rawMessage= ");
  Serial.println(payloadString);
  if (payloadString == "/")
    webSocket.broadcastTXT("{\"readyState\":true}");

  if (type == WStype_TEXT)
  {
    byte separator = payloadString.indexOf('=');
    String var = payloadString.substring(0, separator);
    Serial.print("variable= ");
    Serial.println(var);
    String val = payloadString.substring(separator + 1);
    Serial.print("value= ");
    Serial.println(val);
    Serial.println(" ");

    if (var == "m")
    {
      varType = "num";
      motorDirection = 0;
      //delay(50);
      motorDirection = val.toInt();
    }
    
    if (var == "btn")
    {
      varType = "num";
      switch(val.toInt()){
        case 1:
          irsend.sendNEC(BTN_1);
        break;
        case 2:
          irsend.sendNEC(BTN_2);
        break;
        case 3:
          irsend.sendNEC(BTN_3);
        break;
        case 4:
          irsend.sendNEC(BTN_4);
        break;
        case 0:
          irsend.sendNEC(BTN_AST);
        }
    }
    JSON = json.handler(var, val, varType);
    webSocket.broadcastTXT(JSON);
  }
}
