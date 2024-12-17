#include <BluetoothSerial.h>

BluetoothSerial SerialBT;
BTAddress connectedDeviceAddress;  // Store the connected device's address
#define BT_DISCOVER_TIME 10000  // Discovery time in milliseconds
bool isConnected = false;  // Flag to track connection status

void setupBluetooth(const char *deviceName) {
  if (!SerialBT.begin(deviceName, true)) {  // Initialize Bluetooth with given name
    Serial.println("Bluetooth initialization failed!");
    abort();
  }
  Serial.println("Bluetooth initialized.");
}

bool discoverAndConnect() {
  Serial.println("Starting Bluetooth discovery...");

  // Start discovery
  if (SerialBT.discoverAsync([](BTAdvertisedDevice *device) {
        Serial.printf("Found device: %s\n", device->toString().c_str());
      })) {
    delay(BT_DISCOVER_TIME);  // Wait for the discovery period
    SerialBT.discoverAsyncStop();
    Serial.println("Discovery stopped.");
  } else {
    Serial.println("Failed to start discovery.");
    return false;
  }

  // Connect to the first discovered device
  BTScanResults *results = SerialBT.getScanResults();
  if (results->getCount() > 0) {
    BTAdvertisedDevice *device = results->getDevice(0);
    Serial.printf("Connecting to: %s\n", device->getAddress().toString().c_str());

    connectedDeviceAddress = device->getAddress();  // Store the address globally

    if (SerialBT.connect(connectedDeviceAddress)) {
      Serial.println("Connected!");
      isConnected = true;
      return true;
    } else {
      Serial.println("Connection failed.");
      return false;
    }
  } else {
    Serial.println("No devices found.");
    return false;
  }
}

bool isDeviceConnected() {
  return isConnected && SerialBT.connected();
}

void handleDisconnection() {
  Serial.println("Device disconnected. Restarting discovery...");
  isConnected = false;
}
