#include <BluetoothSerial.h>

BluetoothSerial SerialBT;
#define BT_DISCOVER_TIME 10000

String discoveredDeviceName = "";

void setupBluetoothDiscovery() {
  if (!SerialBT.begin("ESP32_Discover", true)) {
    Serial.println("Bluetooth init failed!");
    while (true);
  }
  Serial.println("Bluetooth initialized.");
}

void discoverDevices() {
  if (discoveredDeviceName.isEmpty()) {
    Serial.println("Starting discovery...");
    if (SerialBT.discoverAsync([](BTAdvertisedDevice *device) {
          if (discoveredDeviceName.isEmpty()) {
            discoveredDeviceName = device->getName().c_str();
            Serial.printf("First device: %s\n", discoveredDeviceName.c_str());
          }
        })) {
      delay(BT_DISCOVER_TIME);
      SerialBT.discoverAsyncStop();
      Serial.println("Discovery done.");
    }
  }
}

String getDiscoveredDeviceName() {
  return discoveredDeviceName;
}

