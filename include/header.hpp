#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <iostream>
#include <atomic>

using namespace std;

template <typename T>
class SharedPtr {

private:
    T* object = nullptr;
    std::atomic_size_t *count = nullptr;

public:
    SharedPtr()
    {
        count = new std::atomic_size_t (1);
    }

    explicit SharedPtr(T* ptr)
    {
        object = ptr;
        count = new std::atomic_size_t (1);
    }

    SharedPtr(const SharedPtr& r)
    {
        *this = r;
    }

    SharedPtr(SharedPtr&& r)
    {
        *this = move(r); //move возвращает ссылку r-value (значение, которое не имеет постоянного адреса в памяти)
    }

    ~SharedPtr()
    {
        if (count != nullptr && --(*count) == 0)
        {
            delete object;
            delete count;
        }
    }

    auto operator=(const SharedPtr& r) -> SharedPtr&
    {
        if (this == &r)
            return *this;
        else {
            this->~SharedPtr();
            count = r.count;
            object = r.object;
            //(*count)++;
            return *this;
        }
    }
    auto operator=(SharedPtr&& r) -> SharedPtr&
    {
        if (this == &r)
            return *this;
        else {
            this->~SharedPtr();
            count = r.count;
            object = r.object;

            r.count = nullptr;
            r.object = nullptr;
            //(*count)++;
            return *this;
        }
    }

    // проверяет, указывает ли указатель на объект
    explicit operator bool() const
    {
        bool flag = true;

        if (count == nullptr)
            flag = false;

        return flag;
    }

    auto operator*() const -> T&
    {
        return *object;
    }
    auto operator->() const -> T*
    {
        return object;
    }

    auto get() -> T*
    {
        return object;
    }

    void reset()
    {
        *this = SharedPtr();
    }

    //заменяет объект, которым владеет
    void reset(T* ptr)
    {
        *this = SharedPtr(ptr);
    }

  //обмен содержимым
    void swap(SharedPtr& r)
    {
        std::swap(object, r.object);
        std::swap(count, r.count);
    }
    // возвращает количество объектов SharedPtr, которые ссылаются на тот же управляемый объект
    auto use_count() const -> size_t
    {
       return *count;
    }
};



#endif // INCLUDE_HEADER_HPP_
