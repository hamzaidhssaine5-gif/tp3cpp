#include <iostream>
#include <iomanip>

class Buffer {
private:
    size_t size;
    unsigned char* data;

public:
    Buffer() : size(0), data(nullptr) {
        std::cout << "Buffer par défaut créé (taille 0)" << std::endl;
    }

    Buffer(size_t n) : size(n), data(nullptr) {
        if (size > 0) {
            data = new unsigned char[size]{0};
        }
        std::cout << "Buffer paramétré créé (taille " << size << ")" << std::endl;
    }

    Buffer(const Buffer& autre) : size(autre.size), data(nullptr) {
        if (size > 0) {
            data = new unsigned char[size];
            for (size_t i = 0; i < size; ++i) {
                data[i] = autre.data[i];
            }
        }
        std::cout << "Constructeur de copie appelé (taille " << size << ")" << std::endl;
    }

    Buffer& operator=(const Buffer& autre) {
        if (this != &autre) {
            delete[] data;
            size = autre.size;
            data = nullptr;
            if (size > 0) {
                data = new unsigned char[size];
                for (size_t i = 0; i < size; ++i) {
                    data[i] = autre.data[i];
                }
            }
        }
        std::cout << "Opérateur d'affectation appelé (taille " << size << ")" << std::endl;
        return *this;
    }

    ~Buffer() {
        std::cout << "Destruction du buffer de " << size << " octet(s)" << std::endl;
        delete[] data;
    }

    size_t getSize() const {
        return size;
    }

    void fill(unsigned char value) {
        for (size_t i = 0; i < size; ++i) {
            data[i] = value;
        }
    }

    void printHex() const {
        if (size == 0) {
            std::cout << "Buffer de 0 octet(s)" << std::endl;
            return;
        }
        std::cout << "Buffer de " << size << " octet(s) : ";
        for (size_t i = 0; i < size; ++i) {
            std::cout << std::hex << std::uppercase << std::setw(2) << std::setfill('0')
                      << static_cast<int>(data[i]) << " ";
        }
        std::cout << std::dec << std::endl;
    }
};

int main() {
    Buffer b1;
    Buffer b2(8);
    b2.fill(0xAA);
    Buffer b3 = b2;

    b1.printHex();
    b2.printHex();
    b3.printHex();

    std::cout << "Taille b1 : " << b1.getSize() << std::endl;
    std::cout << "Taille b2 : " << b2.getSize() << std::endl;
    std::cout << "Taille b3 : " << b3.getSize() << std::endl;

    return 0;
}
