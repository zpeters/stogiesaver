/*-----( Import needed libraries )-----*/
#include <dht11.h>
#include <Morse.h>

/*-----( Setup pins )-----*/
int ledPin = 13;
#define DHT11PIN 1

/*-----( Settings )-----*/
int sleepDelay = 5000;
int morseDelay = 110;
// http://en.wikipedia.org/wiki/Humidor
// and http://www.cigar.com/cs/forums/thread/611022.aspx
float fahrenheitTriggerLow = 55;
float fahrenheitTriggerHigh = 77;
float humidityTriggerLow = 62;
float humidityTriggerHigh = 75;

// Alert triggers
boolean alertTriggered;
boolean tempHigh;
boolean tempLow;
boolean humidityHigh;
boolean humidityLow;


// Global Variables
float fahrenheit;
float humidity;

// Setup Objects
Morse morse(ledPin, morseDelay);
dht11 DHT11;


void setup() {             
  alertTriggered = false;  
  tempLow = false;
  tempHigh = false;
  humidityHigh = false;
  humidityLow = false;
  Serial.begin(38400);
}

void alert() {
  Serial.println("Alerting...");

  if (tempHigh) {
    Serial.println("\tTemp high alert...");
    // TH and a pause
    morse.t(); 
    morse.h();
    morse.wordPause();
  }

  if (tempLow) {
    Serial.println("\tTemp low alert...");
    // TL
    morse.t(); 
    morse.l();
    morse.wordPause();
  }

  if (humidityHigh) {
    Serial.println("\tHumidity high alert...");
    // HH and a pause
    morse.h(); 
    morse.h();
    morse.wordPause();
  }

  if (humidityLow) {
    Serial.println("\tHumidity low alert...");
    // HL
    morse.h(); 
    morse.l();
    morse.wordPause();
  }

}

double Fahrenheit(double celsius) {
  return 1.8 * celsius + 32;
}


void loop()                     
{
  
  // Get and check temperature and humidity
  int chk = DHT11.read(DHT11PIN);
  fahrenheit = Fahrenheit(DHT11.temperature);
  humidity = DHT11.humidity;
 
   Serial.print("Temperature: ");
   Serial.print(fahrenheit);
   Serial.println(" F");
   
   Serial.print("Humidity: ");
   Serial.print(humidity);
   Serial.println(" %");
  
  // check if we are over our threshold
  if (fahrenheit > fahrenheitTriggerHigh) {
    alertTriggered = true;
    tempHigh = true;
    Serial.print("\t");    
    Serial.print(fahrenheit);
    Serial.print("F is over our limit of ");
    Serial.print(fahrenheitTriggerHigh);
    Serial.println("F. Setting alert");
  }
  // check if we are under our threshold
  if (fahrenheit < fahrenheitTriggerLow) {
    alertTriggered = true;
    tempLow = true;
    Serial.print("\t");    
    Serial.print(fahrenheit);
    Serial.print("F is under our limit of ");
    Serial.print(fahrenheitTriggerLow);
    Serial.println("F. Setting alert");
  }

  // check if we are over our threshold
  if (humidity > humidityTriggerHigh) {
    alertTriggered = true;
    humidityHigh = true;
    Serial.print("\t");    
    Serial.print(humidity);
    Serial.print("% is over our limit of ");
    Serial.print(humidityTriggerHigh);
    Serial.println("%. Setting alert");
  }
  // check if we are under our threshold
  if (humidity < humidityTriggerLow) {
    alertTriggered = true;
    humidityLow = true;
    Serial.print("\t");    
    Serial.print(humidity);
    Serial.print("% is under our limit of ");
    Serial.print(humidityTriggerLow);
    Serial.println("F. Setting alert");
  }
  
  // Alerting
  // Check if our alert has been triggered
  if (alertTriggered) {
    alert();
  } else {
    morse.dot();  
  }
  
  // Reset alert status for our next round of checks
  alertTriggered = false;  
  tempLow = false;
  tempHigh = false;
  humidityHigh = false;
  humidityLow = false;
  delay(sleepDelay);
}

