#include <Keypad.h>
#include <Arduino.h>
#define COLS 4
#define ROWS 4

// Définir la disposition des touches du clavier
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {5, 4, 3, 2};  // Assignation des broches pour les lignes
byte colPins[COLS] = {9, 8, 7, 6};  // Assignation des broches pour les colonnes

// Initialisation du clavier
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Définir les broches pour les LED
const int ledPinGreen = 11;  // LED verte connectée à la broche 11
const int ledPinRed = 10;    // LED rouge connectée à la broche 10

String enteredCode = "";  // Variable pour stocker le code entré
String correctCode = "12";  // Le code correct à valider

void setup() {
  Serial.begin(9600);  // Démarrage de la communication série
  pinMode(ledPinGreen, OUTPUT);  // Initialisation de la broche de la LED verte comme sortie
  pinMode(ledPinRed, OUTPUT);    // Initialisation de la broche de la LED rouge comme sortie
  digitalWrite(ledPinGreen, LOW);  // Éteindre la LED verte au démarrage
  digitalWrite(ledPinRed, LOW);    // Éteindre la LED rouge au démarrage
}

void loop() {
  char key = keypad.getKey();  // Récupérer la touche pressée par l'utilisateur
  
  if (key) {
    Serial.print("Le bouton ");
    Serial.print(key);  // Affiche le bouton pressé dans le moniteur série
    Serial.println(" est pressé");

    // Ajouter la touche pressée au code entré
    enteredCode += key;
    
    // Si le code entré fait 2 chiffres
    if (enteredCode.length() == 2) {
      Serial.print("Code entré : ");
      Serial.println(enteredCode);

      // Vérifier si le code est correct
      if (enteredCode == correctCode) {
        Serial.println("Code correct !");
        digitalWrite(ledPinGreen, HIGH);  // Allumer la LED verte si le code est correct
        digitalWrite(ledPinRed, LOW);     // Éteindre la LED rouge si le code est correct
      } else {
        Serial.println("Code incorrect !");
        digitalWrite(ledPinRed, HIGH);   // Allumer la LED rouge si le code est incorrect
        digitalWrite(ledPinGreen, LOW);  // Éteindre la LED verte si le code est incorrect
      }

      // Réinitialiser le code après une tentative
      enteredCode = "";
      delay(1000);  // Attendre 1 seconde avant de permettre une nouvelle entrée
      digitalWrite(ledPinGreen, LOW);  // Éteindre la LED verte après la vérification
      digitalWrite(ledPinRed, LOW);    // Éteindre la LED rouge après la vérification
    }
  }
}
