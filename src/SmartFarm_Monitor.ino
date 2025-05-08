SOIL MOISTURE PROJECT


// 1.	SoilMoisture+ Esp

const int soilPin = 36;
void setup(){
  Serial.begin(115200);
}
void loop(){
  int rawValue = analogRead(soilPin);
  int moistPercent = map(rawValue, 4095, 1400, 0 ,100);

  Serial.print("Raw Value: ");
  Serial.print(rawValue);
  Serial.print("| Moistuer Percent: ");
  Serial.print(moistPercent);
  Serial.println("%");

  delay(2000);
}

//2.	Sim800l Module + Arduino Mega

#include <SoftwareSerial.h>
#define sim800l Serial1  // Mega's Serial1 (RX1=19, TX1=18)

String _buffer;
String number = "+************";  // Replace with your number

void setup() {
  Serial.begin(9600);   // Debug serial
  sim800l.begin(9600);  // SIM800L baud rate
  _buffer.reserve(255);

  delay(3000);  // Critical: Wait for SIM800L power-up

  // Initialize module
  sendATCommand("AT", "OK", 2000);       // Check if alive
  sendATCommand("AT+CFUN=1", "OK", 2000); // Enable full functionality
  sendATCommand("AT+CMEE=1", "OK", 1000);  // Enable verbose errors
  
  Serial.println("System Ready");
  Serial.println("Commands: s=Send SMS, r=Receive SMS, c=Call");
}

void loop() {
  if (Serial.available() > 0) {
    char cmd = Serial.read();
    switch (cmd) {
      case 's': SendMessage(); break;
      case 'r': ReceiveMessage(); break;
      case 'c': callNumber(); break;
    }
  }
  
  if (sim800l.available()) {
    Serial.write(sim800l.read());
  }
}

// ================== IMPROVED SMS FUNCTION ================== //
void SendMessage() {
  Serial.println("Preparing SMS...");
  
  // Set text mode
  if (!sendATCommand("AT+CMGF=1", "OK", 2000)) {
    Serial.println("Failed to set text mode!");
    return;
  }

  // Start SMS
  sim800l.print("AT+CMGS=\"");
  sim800l.print(number);
  sim800l.println("\"");
  
  // Wait for ">" prompt
  unsigned long timeout = millis() + 10000;
  while (millis() < timeout) {
    if (sim800l.available()) {
      char c = sim800l.read();
      Serial.write(c);
      if (c == '>') {
        break;
      }
    }
  }

  // Send message content
  String SMS = "Tycoon electricals says Hello!";
  sim800l.println(SMS);
  delay(100);  // Short delay before CTRL+Z
  
  // Send CTRL+Z properly
  sim800l.write(26);
  sim800l.println();  // Extra newline helps some modules
  
  // Wait for confirmation
  timeout = millis() + 10000;
  bool sent = false;
  while (millis() < timeout) {
    if (sim800l.available()) {
      String response = sim800l.readString();
      Serial.print(response);
      if (response.indexOf("+CMGS:") != -1) {
        sent = true;
        break;
      } else if (response.indexOf("ERROR") != -1) {
        break;
      }
    }
  }
  
  if (sent) {
    Serial.println("SMS sent successfully!");
  } else {
    Serial.println("SMS failed to send");
  }
}

// ================== OTHER FUNCTIONS ================== //
bool sendATCommand(String cmd, String expected, int timeout) {
  Serial.println("CMD: " + cmd);
  sim800l.println(cmd);
  
  long endTime = millis() + timeout;
  String response = "";
  
  while (millis() < endTime) {
    while (sim800l.available()) {
      char c = sim800l.read();
      response += c;
      Serial.write(c);
    }
    if (response.indexOf(expected) != -1) {
      return true;
    }
  }
  return false;
}

void ReceiveMessage() {
  Serial.println("Setting SMS reception...");
  sendATCommand("AT+CMGF=1", "OK", 2000);
  sendATCommand("AT+CNMI=2,2,0,0,0", "OK", 2000);
  Serial.println("Ready to receive SMS");
}

void callNumber() {
  Serial.println("Calling...");
  String cmd = "ATD" + number + ";";
  sendATCommand(cmd, "OK", 2000);
}


