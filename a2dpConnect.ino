#include <BluetoothA2DPSource.h>

BluetoothA2DPSource a2dpSource;

// Function to connect to A2DP using BTAddress
bool connectToA2DP(BTAddress btAddress) {
  esp_bd_addr_t peerAddress;  // Address array to store the 6 bytes
  
  // Convert BTAddress to a String and parse into peerAddress
  String addrStr = btAddress.toString();  // Convert BTAddress to string format "XX:XX:XX:XX:XX:XX"
  for (int i = 0; i < 6; i++) {
    peerAddress[i] = strtol(addrStr.substring(i * 3, i * 3 + 2).c_str(), NULL, 16);
  }

  // Print the converted address for debugging
  Serial.print("Converted Device Address: ");
  for (int i = 0; i < 6; i++) {
    Serial.printf("%02X", peerAddress[i]);
    if (i < 5) Serial.print(":");
  }
  Serial.println();

  // Attempt to connect using the converted address
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
