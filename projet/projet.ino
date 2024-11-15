class Capteur {
protected:
    int id;
    String type;

public:
    Capteur(int id, String type) : id(id), type(type) {}
    virtual float mesurer() = 0; // Méthode virtuelle pure pour mesurer
    virtual void afficherValeur() = 0; // Pour afficher la valeur sur l'écran
};

class CapteurLuminosite : public Capteur {
private:
    int pin;
    int valeurLuminosite;

public:
    CapteurLuminosite(int id, int pin) : Capteur(id, "Luminosité"), pin(pin) {}

    float mesurer() override {
        valeurLuminosite = analogRead(pin);
        return valeurLuminosite;
    }

    void afficherValeur() override {
        Serial.print("Luminosité : ");
        Serial.println(valeurLuminosite);
    }
};
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
