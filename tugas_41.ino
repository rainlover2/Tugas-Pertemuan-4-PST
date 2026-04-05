// PIN CONFIGURATION
const int vRed = 3, vYellow = 4, vGreen = 5;      
const int p1Red = 6, p1Green = 7;                 
const int p2Red = 8, p2Green = 9;                 
const int buttonPin = 2;                          

volatile bool adaPejalan = false;

void setup() {
  // Semua LED sebagai Output
  pinMode(vRed, OUTPUT); pinMode(vYellow, OUTPUT); pinMode(vGreen, OUTPUT);
  pinMode(p1Red, OUTPUT); pinMode(p1Green, OUTPUT);
  pinMode(p2Red, OUTPUT); pinMode(p2Green, OUTPUT);
  
  // Tombol sebagai Input
  pinMode(buttonPin, INPUT);

  // Pasang Interupsi: Deteksi saat tombol ditekan
  attachInterrupt(digitalPinToInterrupt(buttonPin), requestCross, RISING);

  // Kondisi Default: Kendaraan HIJAU, Pedestrian MERAH
  kondisiNormal();
}

void loop() {
  if (adaPejalan) {
    prosesPenyeberangan();
    adaPejalan = false; 
  }
}

// FUNGSI LOGIKA
void requestCross() {
  adaPejalan = true;
}

void kondisiNormal() {
  digitalWrite(vGreen, HIGH);
  digitalWrite(vYellow, LOW);
  digitalWrite(vRed, LOW);
  digitalWrite(p1Red, HIGH); digitalWrite(p1Green, LOW);
  digitalWrite(p2Red, HIGH); digitalWrite(p2Green, LOW);
}

void prosesPenyeberangan() {
  delay(500); 
  
  // 1. Kendaraan: Hijau MATI, Kuning KEDIP 3x (Transisi Berhenti)
  digitalWrite(vGreen, LOW);
  for (int i = 0; i < 3; i++) {
    digitalWrite(vYellow, HIGH); delay(333);
    digitalWrite(vYellow, LOW); delay(333);
  }

  // 2. Kendaraan MERAH, Pedestrian HIJAU (Orang Jalan)
  digitalWrite(vRed, HIGH);
  digitalWrite(p1Red, LOW); digitalWrite(p1Green, HIGH);
  digitalWrite(p2Red, LOW); digitalWrite(p2Green, HIGH);
  
  delay(5000); 

  // 3. Pedestrian Kembali MERAH
  digitalWrite(p1Green, LOW); digitalWrite(p1Red, HIGH);
  digitalWrite(p2Green, LOW); digitalWrite(p2Red, HIGH);
  
  delay(1000); 

  // 4. Kendaraan: Kuning KEDIP 3x (Transisi Jalan)
  for (int i = 0; i < 3; i++) {
    digitalWrite(vYellow, HIGH); delay(333);
    digitalWrite(vYellow, LOW); delay(333);
  }

  // Selesai, kembali ke Hijau Kendaraan
  digitalWrite(vRed, LOW);
  kondisiNormal();
}