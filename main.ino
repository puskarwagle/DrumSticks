void setup() {
  Serial.begin(115200);

  // Initialize Bluetooth discovery and connection
  setupBluetooth("ESP32test");

  // Wait and connect to a Serial Bluetooth device
  while (!isDeviceConnected()) {
    Serial.println("Discovering and connecting to a Serial Bluetooth device...");
    if (!discoverAndConnect()) {
      Serial.println("Retrying discovery in 2 seconds...");
      delay(2000);  // Retry delay
    }
  }

  Serial.println("Serial Bluetooth device connected.");
}

void loop() {
  static bool a2dpConnected = false;
  static esp_bd_addr_t currentDeviceAddress;  // To hold the connected device's address

  // Get the current device address from DiscoverConnect
  if (getConnectedDeviceAddress(currentDeviceAddress)) {
    if (!a2dpConnected) {
      Serial.println("Attempting A2DP connection...");
      if (connectToA2DP(currentDeviceAddress)) {
        a2dpConnected = true;
        Serial.println("A2DP connected!");
      } else {
        Serial.println("A2DP connection failed. Retrying in 2 seconds...");
        delay(2000);
      }
    } else {
      Serial.println("A2DP connection already established.");
      delay(5000);  // Periodic check
    }
  } else {
    Serial.println("No connected device address available.");
    delay(2000);  // Wait before checking again
  }
}
