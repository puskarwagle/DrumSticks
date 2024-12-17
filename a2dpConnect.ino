#include <BluetoothA2DPSource.h>

BluetoothA2DPSource a2dpSource;

bool connectToA2DP(esp_bd_addr_t peerAddress) {
  Serial.println("Attempting to connect to A2DP device...");
  if (a2dpSource.connect_to(peerAddress)) {
    Serial.println("A2DP connection initiated.");
    return true;
  } else {
    Serial.println("A2DP connection failed.");
    return false;
  }
}

bool isA2DPDeviceConnected() {
  return a2dpSource.is_connected();
}
