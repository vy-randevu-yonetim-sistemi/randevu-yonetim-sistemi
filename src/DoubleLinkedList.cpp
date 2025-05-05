#include <iostream>
#include "DoubleLinkedList.h"

int main() {
    DoubleLinkedList<int> list;

    std::cout << "Listeye basa ve sona eleman ekleniyor..." << std::endl;
    list.addFront(10);
    list.addBack(20);
    list.addFront(5);
    list.addBack(30);

    std::cout << "Listenin basi: " << list.front() << std::endl;
    std::cout << "Listenin sonu: " << list.back() << std::endl;

    std::cout << "\nBastan eleman cikariliyor: " << list.removeFront() << std::endl;
    std::cout << "Yeni bas: " << list.front() << std::endl;

    std::cout << "\n Sondan eleman cikariliyor: " << list.removeBack() << std::endl;
    std::cout << "Yeni son: " << list.back() << std::endl;

    std::cout << "\nTum liste bosaltiliyor..." << std::endl;
    while (!list.isEmpty()) {
        std::cout << "Cikarilan: " << list.removeFront() << std::endl;
    }

    std::cout << "Liste bos mu? " << (list.isEmpty() ? "Evet" : "Hayir") << std::endl;

    return 0;
}
