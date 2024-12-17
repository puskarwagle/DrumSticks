#include <BluetoothSerial.h>

BluetoothSerial SerialBT;
bool isConnected = false;  
esp_bd_addr_t connectedDeviceAddress;  // Store connected device's address

bool discoverAndConnect() {
  Serial.println("Starting discovery...");
  if (SerialBT.discoverAsync([](BTAdvertisedDevice *device) {
        Serial.printf("Found device: %s\n", device->toString().c_str());
      })) {
    delay(10000);  // Discovery timeout
    SerialBT.discoverAsyncStop();
    Serial.println("Discovery stopped.");
  } else {
    Serial.println("Failed to start discovery.");
    return false;
  }

  BTScanResults *results = SerialBT.getScanResults();
  if (results->getCount() > 0) {
    BTAdvertisedDevice *device = results->getDevice(0);
    Serial.printf("Connecting to: %s\n", device->getAddress().toString().c_str());

    if (SerialBT.connect(device->getAddress())) {
      memcpy(connectedDeviceAddress, device->getAddress().getNative(), sizeof(esp_bd_addr_t));
      isConnected = true;
      Serial.println("Serial Bluetooth device connected!");
      return true;
    } else {
      Serial.println("Connection failed.");
    }
  } else {
    Serial.println("No devices found.");
  }
  return false;
}
