#include <iostream>
#include <stdexcept>

class Node {
public:
    int value;  // Значение узла
    Node *next; // Указатель на следующий узел

    // Конструктор узла
    Node(int val) : value(val), next(nullptr) {}
};

class LinkedList {
private:
    Node *head;  // Голова списка
    int size;    // Размер списка

public:
    // Конструктор
    LinkedList(int *arr, int size) : head(nullptr), size(size) {
        if (size <= 0) {
            throw std::invalid_argument("Размер должен быть больше 0.");
        }
        head = new Node(arr[0]); // Создаем первый узел
        Node *current = head;

        // Создаем последующие узлы из массива
        for (int i = 1; i < size; ++i) {
            current->next = new Node(arr[i]);
            current = current->next;
        }
    }

    // Деструктор
    ~LinkedList() {
        Node *current = head;
        while (current != nullptr) {
            Node *next = current->next;
            delete current;
            current = next;
        }
    }

    // Метод для отображения списка
    void display() const {
        Node *current = head;
        while (current != nullptr) {
            std::cout << current->value << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    // Метод для получения размера списка
    int getSize() const {
        return size;
    }

    // Метод для получения данных по индексу
    int getData(int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Индекс за границами списка.");
        }
        Node *current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->value;
    }

    // Метод для сложения двух списков
    LinkedList *operator+(const LinkedList& other) {
        if (this->size != other.size) {
            throw std::invalid_argument("Размерность двух списков не совпадает.");
        }
        int *newData = new int[size];
        Node *current1 = this->head;
        Node *current2 = other.head;
        for (int i = 0; i < size; ++i) {
            newData[i] = current1->value + current2->value;
            current1 = current1->next;
            current2 = current2->next;
        }
        return new LinkedList(newData, size);
    }

    // Метод для вычитания двух списков
    LinkedList *operator-(const LinkedList& other) {
        if (this->size != other.size) {
            throw std::invalid_argument("Размерность двух списков не совпадает.");
        }
        int *newData = new int[size];
        Node *current1 = this->head;
        Node *current2 = other.head;
        for (int i = 0; i < size; ++i) {
            newData[i] = current1->value - current2->value;
            current1 = current1->next;
            current2 = current2->next;
        }
        return new LinkedList(newData, size);
    }

    // Метод для умножения двух списков
    LinkedList *operator*(const LinkedList& other) {
        if (this->size != other.size) {
            throw std::invalid_argument("Размерность двух списков не совпадает.");
        }
        int *newData = new int[size];
        Node *current1 = this->head;
        Node *current2 = other.head;
        for (int i = 0; i < size; ++i) {
            newData[i] = current1->value * current2->value;
            current1 = current1->next;
            current2 = current2->next;
        }
        return new LinkedList(newData, size);
    }

    // Метод для деления двух списков
    LinkedList *operator/(const LinkedList& other) {
        if (this->size != other.size) {
            throw std::invalid_argument("Размерность двух списков не совпадает.");
        }
        int *newData = new int[size];
        Node *current1 = this->head;
        Node *current2 = other.head;
        for (int i = 0; i < size; ++i) {
            if (current2->value == 0) {
                throw std::runtime_error("Division by zero");
            } else {
                newData[i] = current1->value / current2->value;
            }
            current1 = current1->next;
            current2 = current2->next;
        }
        return new LinkedList(newData, size);
    }
};



int main() {
    // Создание двух массивов одинаковой длины
    int arr1[] = {1, 2, 3, 7};
    int arr2[] = {4, 5, 6};
    int size1 = sizeof(arr1)/sizeof(arr1[0]);
    int size2 = sizeof(arr2)/sizeof(arr2[0]);
    
    try {
        LinkedList list1(arr1, size1);
        LinkedList list2(arr2, size2);

        // Отображение списка
        std::cout << "List 1: ";
        list1.display();

        std::cout << "List 2: ";
        list2.display();

        // Сложения
        LinkedList *sum = list1 + list2;
        std::cout << "Сумма: ";
        sum->display();

        // Вычитание
        LinkedList *diff = list1 - list2;
        std::cout << "Разность: ";
        diff->display();

        // Умножение
        LinkedList *mul = list1 * list2;
        std::cout << "Произведение: ";
        mul->display();

        // Деление
        LinkedList *div = list1 / list2;
        std::cout << "Частное: ";
        div->display();

        // Очистка памяти
        delete sum;
        delete diff;
        delete mul;
        delete div;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

