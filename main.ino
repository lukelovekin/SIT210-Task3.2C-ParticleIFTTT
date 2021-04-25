#include <Adafruit_DHT.h>
#define DHTPIN 2
#define DHTTYPE DHT22

String outputData;

DHT dht(DHTPIN, DHTTYPE);

bool triggered = false;

double temp = 0;

// void myHandler(const char *event, const char *data)
// {
//     Particle.publish("hotTemp", data);
// }

void setup() {
    dht.begin();
    // particle variable to show up in IFTTT
    Particle.variable("temp", &temp, DOUBLE);
}

void loop() {

    delay(30000);//delay readings by 30 minutes

    float temperature = dht.getTempCelcius(); //get the temperature in celcius
    temp = temperature;

    // outputData = String::format ("%.1f  %,%.1f C", humidity,temperature);
    outputData = String::format ("%.1f", temperature);
    
    // Particle.function(temperature, checkTemp);
    if(temperature > 23 && !triggered)
    {
        // This is used to meet the other IFTTT event trigger I also set up
        Particle.publish("Hot_Temp", outputData);
    }
    else
    {
        Particle.publish("temp", "not hotter then 23 yet");
    }

}