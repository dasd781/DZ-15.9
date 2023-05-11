#include <stdio.h>

#include "hash.h"

HashTable::HashTable() {
    count = 0;
    mem_size = 8;
    array = new Pair[mem_size];
}

HashTable::~HashTable() {
    delete[] array;
}

const AuthData* HashTable::find(const std::string& key) const
{
    const AuthData* result = nullptr;

    // ����� ����� �� ���� i �� 0 �� ������� �������
    for (int i = 0; i < mem_size; i++) {
        const int index = hash_func(key, i);
        if (array[index].status == enPairStatus::engaged) {
            if (array[index].data.login == key)
            {
                result = &array[index].data;
                break;
            }
        }
    }

    return result;
}

static int mult_hash(int val, int M)
{
    const double A = 0.7;
    return int(M * (A * val - int(A * val)));
}

int HashTable::hash_func(std::string login, int offset) const
{
    // ��������� ������
    int hash = 0;
    for (int i = 0; i < login.length(); i++) {
        hash += login[i];
    }

    // ������������ �����
    return mult_hash(mult_hash(hash, mem_size) + offset * offset, mem_size);
}

void HashTable::resize() {
    int mem_size_save = mem_size;
    Pair* array_save = array;
    mem_size = mem_size * 2;
    count = 0;
    array = new Pair[mem_size];
    for (int i = 0; i < mem_size_save; i++)
    {
        if (array_save[i].status == enPairStatus::engaged)
        {
            int index = -1;

            for (int j = 0; j < mem_size; j++)
            {
                index = hash_func(array_save[i].data.login, j);
                if (array[index].status == enPairStatus::free)
                {
                    break;
                }
            }
            array[index] = Pair(array_save[i].data);
            count++;
        }
    }
    delete[] array_save;

    // �� �������� �������� ����� resize() � ������ �����
    // ������ ������ add, � ����� �������� ������� � ����������� ������
    // ��� ���
}

void HashTable::add(AuthData data)
{
    /* � ���� ������ ����� �������� ����� resize() */
    int index = -1;
    for (; ; )
    {
        int i = 0;
        // ����� ����� �� ���� i �� 0 �� ������� �������
        for (; i < mem_size; i++) {
            index = hash_func(data.login, i);
            if (array[index].status == enPairStatus::free) {
                // ������� ������ ������, �������� ��
                break;
            }
        }
        if (i < mem_size)
            break;
        resize();
    }
    // ������ � ��������� ������ ����
    array[index] = Pair(data);
    count++;
}