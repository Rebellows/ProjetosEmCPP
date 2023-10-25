#include <iostream>

using namespace std;

class Animal {
private:
    string nome;
    int idade;
public:
    Animal() { nome = ""; idade = 0; }
    Animal(string n, int i) { nome = n; idade = i; }
    string getNome() { return nome; }
    int getIdade() { return idade; }
    void setNome(string n) { nome = n; }
    void setIdade(int i) { idade = i; }
    virtual string emiteSom() const = 0;
};

class Porco : public Animal {
public:
    Porco() : Animal("", 0) {}
    Porco(string n, int i) : Animal(n, i) {}
    string emiteSom() const override { return "oinc oinc"; }
};

class Cachorro : public Animal {
public:
    Cachorro() : Animal("", 0) {}
    Cachorro(string n, int i) : Animal(n, i) {}
    string emiteSom() const override { return "au au"; }    
};

class Gato : public Animal {
public:
    Gato() : Animal("", 0) {}
    Gato(string n, int i) : Animal(n, i) {}
    string emiteSom() const override { return "miau miau"; }
};

int main() {
    Animal* animais[6];
    animais[0] = new Cachorro("Rex", 3);
    animais[1] = new Cachorro("Buddy", 2);
    animais[2] = new Gato("Whiskers", 5);
    animais[3] = new Gato("Mittens", 4);
    animais[4] = new Porco("Tweety", 1);
    animais[5] = new Porco("Polly", 2);
    for (int i = 0; i < 6; i++) {
        std::cout << "Nome: " << animais[i]->getNome() << ", Idade: " << animais[i]->getIdade() << ", Som: " << animais[i]->emiteSom() << std::endl;
    }
    for (int i = 0; i < 6; i++) {
        delete animais[i];
    }
    return 0;
}
