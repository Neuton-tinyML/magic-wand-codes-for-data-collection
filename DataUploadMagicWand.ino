#include <Arduino_LSM9DS1.h>

#define CONVERT_G_TO_MS2    9.80665f
#define FREQUENCY_HZ        100
#define INTERVAL_MS         (1000 / (FREQUENCY_HZ + 1))

int c = 0;
int sampleReady = 1;
int samplesCount = 0;
static unsigned long last_interval_ms = 0;

void setup() {
    Serial.begin(115200);
    while(!Serial)
    {
    };
    
    // Serial.println("x,y,z,gx,gy,gz,mx,my,mz");

    if (!IMU.begin()) {
        Serial.println("Failed to initialize IMU!");
        while (1);
    }
}

void loop() {
    float x, y, z, gx, gy, gz, mx, my, mz;

    if(sampleReady == 1)
    {
      Serial.println("Get ready in 2 second");
      delay(1000);
      sampleReady = 0;
      c = 0;
    }

    if (millis() > last_interval_ms + INTERVAL_MS && sampleReady == 0) {
        last_interval_ms = millis();

        IMU.readAcceleration(x, y, z);
        IMU.readGyroscope(gx, gy, gz);
        IMU.readMagneticField(mx, my, mz);

        Serial.print(x * CONVERT_G_TO_MS2);
        Serial.print(',');
        Serial.print(y * CONVERT_G_TO_MS2);
        Serial.print(',');
        Serial.print(z * CONVERT_G_TO_MS2);
        Serial.print(',');
        Serial.print(gx);
        Serial.print(',');
        Serial.print(gy);
        Serial.print(',');
        Serial.print(gz);
        Serial.print(',');
        Serial.print(mx);
        Serial.print(',');
        Serial.print(my);
        Serial.print(',');
        Serial.println(mz);
        c++;

        if(c == 200)
        {
          sampleReady = 1;
          samplesCount++;
        }
        
    }
}
