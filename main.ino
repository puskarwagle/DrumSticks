void setup() {
  Serial.begin(115200);

  // Setup Bluetooth discovery
  setupBluetoothDiscovery();
  discoverDevices();

  // Setup A2DP playback
  setupTestPlay();
}

void loop() {
  loopTestPlay();  // Periodically check A2DP connection state
}
