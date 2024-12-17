#include <Arduino.h>
#include <Keypad.h>  // Inclut la bibliothèque Keypad, nécessaire pour utiliser le clavier matriciel
#define COLS 4  // Définit le nombre de colonnes du clavier (ici 4)
#define ROWS 4  // Définit le nombre de lignes du clavier (ici 4)

// Définition de la disposition des touches du clavier
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},  // Première ligne du clavier
  {'4', '5', '6', 'B'},  // Deuxième ligne du clavier
  {'7', '8', '9', 'C'},  // Troisième ligne du clavier
  {'*', '0', '#', 'D'}   // Quatrième ligne du clavier
};

// Assignation des broches de l'Arduino aux lignes du clavier
byte rowPins[ROWS] = {5, 4, 3, 2};  // Lignes du clavier connectées aux broches 5, 4, 3, 2
// Assignation des broches de l'Arduino aux colonnes du clavier
byte colPins[COLS] = {9, 8, 7, 6};  // Colonnes du clavier connectées aux broches 9, 8, 7, 6

// Initialisation de l'objet "keypad" avec la configuration définie plus haut
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);  // Initialisation de la communication série à une vitesse de 9600 bauds
}

void loop() {
  char key = keypad.getKey();  // Récupère la touche pressée sur le clavier (si une touche est appuyée)

  if (key) {  // Si une touche est pressée, la condition est vraie
  if (key == '4') {  // Si la touche pressée est '4'
    // Action à réaliser quand le bouton '4' est pressé
    Serial.println("==================================");
    Serial.println("Le bouton 4 est pressé -> bonjour");
    Serial.println("==================================");
  } else {
    // Si une autre touche est pressée, afficher quel bouton a été pressé
    Serial.println("---------------------------");
    Serial.print("Le bouton ");
    Serial.print(key);  // Affiche la touche pressée
    Serial.println(" est pressé");
    Serial.println("---------------------------");
    Serial.println();
  }
  }
}
