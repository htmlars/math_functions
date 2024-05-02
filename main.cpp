#include <iostream>
#include <memory>
#include <cmath>

class Funktion {
public:
    virtual ~Funktion() = default;
    virtual double at(double x) const = 0;
    virtual bool valid(double x) const = 0;
    virtual std::string toString() const = 0;
    virtual std::string toString(double x) const = 0;
};

class Wurzel : public Funktion {
public:
    bool valid(double x) const override {
        return (x >= 0);
    }
    double at(double x) const override {
        return sqrt(x);
    }
    std::string toString(double x) const override {
        return "Quadratwurzel(" + std::to_string(x) + ")= " + std::to_string(at(x));
    }
    std::string toString() const override {
        return "f(x) = Quadratwurzel(x)";
    }
};

class Quadrat : public Funktion {
public:
    bool valid(double /*x*/) const override {
        return true;
    }
    double at(double x) const override {
        return x * x;
    }
    std::string toString(double x) const override {
        return "Quadrat(" + std::to_string(x) + ")= " + std::to_string(at(x));
    }
    std::string toString() const override {
        return "f(x) = Quadrat(x)";
    }
};

class FProd : public Funktion {
private:
    std::unique_ptr<Funktion> m_f1;
    std::unique_ptr<Funktion> m_f2;

public:
    FProd(std::unique_ptr<Funktion> f1, std::unique_ptr<Funktion> f2)
            : m_f1(std::move(f1)), m_f2(std::move(f2)) {}

    bool valid(double x) const override {
        return m_f1->valid(x) && m_f2->valid(x);
    }

    double at(double x) const override {
        return m_f1->at(x) * m_f2->at(x);
    }

    std::string toString(double x) const override {
        return "Produkt: (" + std::to_string((m_f1->at(x) * m_f2->at(x))) + ")";
    }

    std::string toString() const override {
        return "Funktionen:" + m_f1->toString() + " * " + m_f2->toString() + '\n';
    }
};

template <typename T>
void werteTafel(const T& f, double von, double bis, double schritt) {
    std::cout << "Wertetabelle der Funktion: " << f.toString() << "\n=========================\n";
    for (double x = von; x <= bis; x += schritt) {
        if (f.valid(x))
            std::cout << f.toString(x) << "(" << x << ") = " << f.at(x) << "\n";
        else
            std::cout << f.toString(x) << "(" << x << ") = " << "ist nicht berechenbar\n";
    }
    std::cout << "\n";
}

int main() {
    std::unique_ptr<Wurzel> wurzel1 = std::make_unique<Wurzel>();
    std::unique_ptr<Quadrat> quadrat1 = std::make_unique<Quadrat>();
    std::unique_ptr<FProd> fprod1 = std::make_unique<FProd>(std::move(wurzel1), std::move(quadrat1));

    werteTafel(*fprod1, -1, 1, 0.1);

    return 0;
}



