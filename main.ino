void setup() {
  Serial.begin(115200);

  // Initialize Bluetooth discovery and connection
  setupBluetooth("ESP32test");

  // Discover and connect to a Bluetooth device
  while (!isDeviceConnected()) {
    Serial.println("Discovering and connecting to a Bluetooth device...");
    if (!discoverAndConnect()) {
      Serial.println("Retrying discovery in 2 seconds...");
      delay(2000);
    }
  }

  Serial.println("Bluetooth device connected!");

  // Check A2DP connection state
  Serial.println("Checking A2DP connection...");
  if (a2dpSource.get_connection_state() != ESP_A2D_CONNECTION_STATE_CONNECTED) {
    Serial.println("A2DP not connected. Attempting to connect...");
    if (!connectToA2DP(connectedDeviceAddress)) {
      Serial.println("A2DP connection failed. Restarting discovery...");
      handleDisconnection();
    }
  } else {
    Serial.println("A2DP already connected successfully!");
  }
}

void loop() {
  // Keep the loop clean for future tasks or additional processing
  delay(1000);
}
