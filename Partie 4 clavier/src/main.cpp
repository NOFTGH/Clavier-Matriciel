#include <Keypad.h>
#include <Arduino.h>
#define COLONNES 4
#define LIGNES 4
// Définir la disposition des touches du clavier
char touches[LIGNES][COLONNES] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte brochesLignes[LIGNES] = {5, 4, 3, 2};  // Assignation des broches pour les lignes
byte brochesColonnes[COLONNES] = {9, 8, 7, 6};  // Assignation des broches pour les colonnes
// Initialisation du clavier
Keypad clavier = Keypad(makeKeymap(touches), brochesLignes, brochesColonnes, LIGNES, COLONNES);
// Définir les broches pour les LED
const int brocheLedVerte = 11;  // LED verte connectée à la broche 11
const int brocheLedRouge = 10;  // LED rouge connectée à la broche 10
String codeEntree = "";  // Variable pour stocker le code entré
String codeCorrect = "1234";  // Le code correct à valider (modifié pour 4 chiffres)
int compteurTentatives = 0;  // Compteur des tentatives incorrectes
unsigned long tempsDeblocage = 0;  // Variable pour enregistrer le moment où le clavier est bloqué
bool estBloque = false;  // Indicateur pour vérifier si le clavier est bloqué
void setup() {
  Serial.begin(9600);  // Démarrage de la communication série
  pinMode(brocheLedVerte, OUTPUT);  // Initialisation de la broche de la LED verte comme sortie
  pinMode(brocheLedRouge, OUTPUT);  // Initialisation de la broche de la LED rouge comme sortie
  digitalWrite(brocheLedVerte, LOW);  // Éteindre la LED verte au démarrage
  digitalWrite(brocheLedRouge, LOW);  // Éteindre la LED rouge au démarrage
}
void loop() {
  // Si le clavier est bloqué, on vérifie le temps écoulé pour le débloquer
  if (estBloque) {
  // Vérifier si 5 secondes sont passées depuis le début du blocage
  if (millis() - tempsDeblocage >= 5000) {
    estBloque = false;  // Débloquer le clavier
    compteurTentatives = 0;  // Réinitialiser le compteur de tentatives
    Serial.println("Le clavier est débloqué. Vous pouvez maintenant essayer de nouveau.");
    digitalWrite(brocheLedRouge, LOW);  // Éteindre la LED rouge
  } else {
    // Clignoter la LED rouge pendant le blocage
    if (millis() % 500 < 250) {
      digitalWrite(brocheLedRouge, HIGH);  // Allumer la LED rouge
    } else {
      digitalWrite(brocheLedRouge, LOW);   // Éteindre la LED rouge
    }
  }
  return;  // Ne pas continuer à traiter les entrées clavier pendant le blocage
  }

  // Si le clavier n'est pas bloqué, vérifier la saisie
  char touche = clavier.getKey();  // Récupérer la touche pressée par l'utilisateur
  if (touche) {
  Serial.print("Le bouton ");
  Serial.print(touche);  // Affiche le bouton pressé dans le moniteur série
  Serial.println(" est pressé");
  // Ajouter la touche pressée au code entré
  codeEntree += touche;
  // Si le code entré fait 4 chiffres
  if (codeEntree.length() == 4) {
    Serial.print("Code entré : ");
    Serial.println(codeEntree);
    // Vérifier si le code est correct
    if (codeEntree == codeCorrect) {
      Serial.println("Code correct !");
      digitalWrite(brocheLedVerte, HIGH);  // Allumer la LED verte si le code est correct
      digitalWrite(brocheLedRouge, LOW);   // Éteindre la LED rouge si le code est correct
      compteurTentatives = 0;  // Réinitialiser le compteur des tentatives après une réussite
    } else {
      Serial.println("Code incorrect !");
      digitalWrite(brocheLedRouge, HIGH);   // Allumer la LED rouge si le code est incorrect
      digitalWrite(brocheLedVerte, LOW);  // Éteindre la LED verte si le code est incorrect
      compteurTentatives++;  // Incrémenter le compteur de tentatives incorrectes
      if (compteurTentatives >= 3) {
        // Si l'utilisateur a fait 3 tentatives incorrectes
        estBloque = true;  // Bloquer le clavier
        tempsDeblocage = millis();  // Enregistrer le moment où le blocage commence
        Serial.println("Trop de tentatives incorrectes. Le clavier est bloqué pendant 5 secondes.");
        digitalWrite(brocheLedVerte, LOW);  // Éteindre la LED verte
      }
    }
    // Réinitialiser le code après une tentative
    codeEntree = "";
    delay(1000);  // Attendre 1 seconde avant de permettre une nouvelle entrée
    digitalWrite(brocheLedVerte, LOW);  // Éteindre la LED verte après la vérification
    digitalWrite(brocheLedRouge, LOW);  // Éteindre la LED rouge après la vérification
  }
  }
}
