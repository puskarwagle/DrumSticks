#include "BluetoothA2DPSource.h"
#include "tom.h"

BluetoothA2DPSource a2dp_source;

// Declare the extern array from tom.c
extern const unsigned char tom_wav[];
extern const unsigned int tom_wav_len;

SoundData *music = new OneChannelSoundData((int16_t*)tom_wav, tom_wav_len / 2);

void setupTestPlay() {
  String deviceName = getDiscoveredDeviceName();  // Get the discovered device name dynamically
  if (!deviceName.isEmpty()) {
    a2dp_source.start(deviceName.c_str());  // Start streaming to the discovered device
    a2dp_source.write_data(music);
    a2dp_source.set_volume(100);
    Serial.printf("Streaming initialized for: %s\n", deviceName.c_str());
  } else {
    Serial.println("No device found. Cannot start A2DP.");
  }
}

void checkConnectionState() {
  int state = a2dp_source.get_connection_state();  // Get the current connection state

  switch (state) {
    case 0:
      Serial.println("A2DP: Disconnected");
      break;
    case 1:
      Serial.println("A2DP: Connecting");
      break;
    case 2:
      Serial.println("A2DP: Connected");
      break;
    case 3:
      Serial.println("A2DP: Streaming");
      break;
    default:
      Serial.println("A2DP: Unknown state");
      break;
  }
}

void loopTestPlay() {
  String deviceName = getDiscoveredDeviceName();
  checkConnectionState();  // Periodically check connection state
  a2dp_source.start(deviceName.c_str());
  a2dp_source.write_data(music);
  delay(3000);  // Add a delay to avoid spamming
}
