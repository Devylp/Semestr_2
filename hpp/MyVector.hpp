#pragma once
#include <iostream>
#include <algorithm>
#include <stdexcept>

template<typename T>
class MyVector {
T* m_arr;
size_t m_size;
size_t capacity_;

public:
	MyVector() {
		m_size = 0; //текущий размер
		capacity_ = 0; //с запасом
		m_arr = nullptr;
	}

	explicit MyVector(size_t size) : m_size(0), capacity_(size) {
		m_arr = new T[capacity_];
	}

	//Конструктор копирования
	MyVector(const MyVector& other) : m_size(other.m_size), capacity_(other.capacity)
	{
		m_arr = new int[capacity_];
		for (size_t i = 0; i < m_size; ++i) {
			m_arr[i] = other.m_arr[i];
		}
	}

	//Оператор присваивания копированием
	MyVector& operator = (MyVector other) // передается копия, она уничтожиться при выходе
	{
		swap(*this, other);
		return *this;
	}
	// Вспомогательная функция для оператора присваивания копированием (идиома copy-and-swap)
	friend void swap(MyVector& a, MyVector& b) noexcept {
		std::swap(a.m_arr, b.m_arr);
		std::swap(a.m_size, b.m_size);
		std::swap(a.capacity_, b.capacity_);
	}

	// Деструктор
	~MyVector() {
		if (m_arr != nullptr)
			delete[] m_arr;
	}

	// Оператор чтения по индексу
	const T& operator [] (size_t index) const {
		if (index >= m_size)
			throw std::out_of_range("Invalid index: Out of range");
		return m_arr[index];
	}

	// Оператор изменения значения по индексу
	T& operator [] (size_t index) {
		if (index >= m_size)
			throw std::out_of_range("Invalid index: Out of range");
		return m_arr[index];
	}

	// Резервирование памяти
	void reserve(size_t new_capacity) {
		if (new_capacity <= capacity_) return;

		T* new_data = new int[new_capacity];
		for (size_t i = 0; i < m_size; ++i) {
			new_data[i] = m_arr[i];
		}

		delete[] m_arr;
		m_arr = new_data;
		capacity_ = new_capacity;
	}

	bool empty() {
		return (m_size == 0);
	}

	void push_back(T value) {
		if (m_size >= capacity_)
			reserve(capacity_ == 0 ? 1 : capacity_ * 2);
	m_arr[m_size++] = value;
	}

	void shrink_to_fit() {
		if (m_size == capacity_) return;

		T* new_data = new T[m_size];
		for (size_t i = 0; i < m_size; ++i) {
			new_data[i] = m_arr[i];
		}

		delete[] m_arr;
		m_arr = new_data;
		capacity_ = m_size;
	}

	void resize(size_t new_size, const T& value = T()) {
		if (new_size > capacity_) {
			reserve(new_size);
		}

		for (size_t i = m_size; i < new_size; ++i) {
			m_arr[i] = value;
		}

		m_size = new_size;
	}

	size_t size() const {
		return m_size;
	}

	size_t capacity() const {
		return capacity_;
	}

	const T& front() {
		return m_arr[0];
	}

	const T& back() {
		return m_arr[m_size - 1];
	}

	void insert(size_t pos, const T& value) {
		if (pos > m_size) throw std::out_of_range("Invalid position");

		if (m_size >= capacity_) {
			reserve(capacity_ == 0 ? 1 : capacity_ * 2);
		}

		// Сдвиг элементов вправо
		for (size_t i = m_size; i > pos; --i) {
			m_arr[i] = m_arr[i - 1];
		}

		m_arr[pos] = value;
		m_size++;
	}

	void erase(size_t pos) {
		if (pos >= m_size) throw std::out_of_range("Invalid position");

		// Сдвиг элементов влево
		for (size_t i = pos; i < m_size - 1; ++i) {
			m_arr[i] = m_arr[i + 1];
		}

		m_size--;
	}
};




// Специализация под vector bool
template<>
class MyVector<bool> {
private:
    uint8_t* data = nullptr;
    size_t size = 0;     // Количество битов
    size_t capacity = 0; // Количество байтов

	// Создаем прокси-обьект (он же посредник)
    class BitReference {
        uint8_t* byte;
        uint8_t mask;

    public:
        BitReference(uint8_t* byte_ptr, size_t bit_pos)
            : byte(byte_ptr), mask(1 << (bit_pos % 8)) {}

        operator bool() const { return (*byte & mask) != 0; }

        BitReference& operator=(bool value) {
            if (value) *byte |= mask;
            else       *byte &= ~mask;
            return *this;
        }
    };

public:
    ~MyVector() { delete[] data; }

    void reserve(size_t new_capacity_bytes) {
        if (new_capacity_bytes <= capacity) return;
        uint8_t* new_data = new uint8_t[new_capacity_bytes]{};
        if (data) {
            std::copy(data, data + capacity, new_data);
        }
        delete[] data;
        data = new_data;
        capacity = new_capacity_bytes;
    }

    void push_back(bool value) {
        if (size >= capacity * 8) {
            // Увеличиваем capacity в байтах, учитывая необходимые биты
            size_t required_capacity = (size + 8) / 8; // Байты для (size+1) битов
            reserve(std::max(capacity * 2, required_capacity));
        }
        size_t byte_idx = size / 8;
        uint8_t bit_offset = size % 8;
        if (value) {
            data[byte_idx] |= (1 << bit_offset);
        } else {
            data[byte_idx] &= ~(1 << bit_offset);
        }
        size++;
    }

    void insert(size_t pos, bool value) {
        if (pos > size) return;
        // Увеличиваем размер без использования push_back
        if (size + 1 > capacity * 8) {
            size_t required_capacity = (size + 8) / 8;
            reserve(std::max(capacity * 2, required_capacity));
        }
        size++; // Временное увеличение size для сдвига
        // Сдвигаем биты вправо напрямую
        for (size_t i = size - 1; i > pos; --i) {
            bool bit = get_bit(i - 1);
            set_bit(i, bit);
        }
        set_bit(pos, value);
    }

    void erase(size_t pos) {
        if (pos >= size) return;
        // Сдвигаем биты влево напрямую
        for (size_t i = pos; i < size - 1; ++i) {
            bool bit = get_bit(i + 1);
            set_bit(i, bit);
        }
        size--;
    }

private:
    // Прямой доступ к битам без использования BitReference
    
	// Получить бит
	bool get_bit(size_t index) const {
        size_t byte_idx = index / 8;
        uint8_t bit_offset = index % 8;
        return (data[byte_idx] & (1 << bit_offset)) != 0;
    }

	// Установить бит
    void set_bit(size_t index, bool value) {
        size_t byte_idx = index / 8;
        uint8_t bit_offset = index % 8;
        if (value) {
            data[byte_idx] |= (1 << bit_offset);
        } else {
            data[byte_idx] &= ~(1 << bit_offset);
        }
    }

public:
    BitReference operator[](size_t index) {
        if (index >= size) throw std::out_of_range("Index out of range");
        return BitReference(&data[index / 8], index);
    }

    bool operator[](size_t index) const {
        if (index >= size) throw std::out_of_range("Index out of range");
        return get_bit(index);
    }

    size_t size_b() const { return size; }
    size_t capacity_b() const { return capacity * 8; }
};
