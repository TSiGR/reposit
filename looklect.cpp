#include <iostream>

template<typename Type>
class MySimpleClass
{
    public:
    MySimpleClass(Type field) : m_field(field) {}

    Type getval() const
    {
        return m_field;
    }

    template<typename U>
    friend std::ostream& operator<<(std::ostream&, const MySimpleClass<U>&);

    private:
    Type m_field;
};

template<typename Type>
std::ostream& operator<<(std::ostream& out, const MySimpleClass<Type> &another)
{
    out << "Value: " << another.m_field << std::endl;
    return out;
}

template<typename T>
struct Node
{
    const T *value;
    Node *next;
    Node *prev;
};

template<typename T>
class List
{
    public:

    List(T* ptr)
    {
        Node<T> *temp = new Node<T>;
        temp->value = ptr;
        temp->next = nullptr;
        temp->prev = nullptr;
        m_head = temp;
        m_tail = temp;
    }

    void add(const T* another)
    {
        Node<T> *temp = new Node<T>;
        temp->value = another;
        temp->next = m_head;
        temp->prev = nullptr;
        m_head->prev = temp;
        m_head = temp;
    }

    void remove()
    {
        if (m_head != m_tail)
        {
            Node<T> *temp = m_head;
            m_head = temp->next;
            m_head->prev = nullptr;
            temp->next = nullptr;
            temp->prev = nullptr;
            delete temp;
            temp = nullptr;
        }
        else
        {
            delete m_head;
            m_head = nullptr;
            m_tail = nullptr;
        }
    }

    const int print_size() const
    {
        Node<T> *temp = m_head;
        int count = 0;
        while (temp != nullptr)
        {
            count++;
            temp = temp->next;
        }
        return count;
    }

    List& operator=(const List &another) = delete;
    List(const List &another) = delete;

    private:
    Node<T> *m_head;
    Node<T> *m_tail;
};

template<typename T>
class Linked_ptr
{
    public:

    explicit Linked_ptr(T* ptr = 0) : m_ptr(ptr), m_list(nullptr)
    {
        if (m_ptr)
            m_list = new List(m_ptr);
    }

    Linked_ptr(const Linked_ptr<T>& another)
    {
        m_ptr = another.m_ptr;
        m_list = another.m_list;
        m_list->add(m_ptr);
    }

    Linked_ptr& operator=(const Linked_ptr<T>& another)
    {
        if (this != &another)
        {
            this->~Linked_ptr();
            this->m_ptr = another.m_ptr;
            this->m_list = another.m_list;
            this->m_list->add(this->m_ptr);
        }

        return *this;
    }

    void reset(T* ptr)
    {
        this->~Linked_ptr();
        m_ptr = ptr;
        if (m_ptr)
            m_list = new List(m_ptr);
    }

    const int get_size() const
    {
        return m_list->print_size();
    }

    T* get() const
    {
        return m_ptr;
    }

    T& operator*()
    {
        return *m_ptr;
    }
    T* operator->()
    {
        return m_ptr;
    }

    ~Linked_ptr() 
    { 
        if (m_ptr)
            m_list->remove();
    }

    Linked_ptr(Linked_ptr &&another) = delete;
    Linked_ptr& operator=(Linked_ptr &&another) = delete;

    private:

    List<T> *m_list;
    T *m_ptr;
};

int main()
{
    const int c = 9;
    int t = 8;
    int const *p = &c;
    int const *a = &c;
    p = &t;
    std::cout << p << " " << *p << " " << &t << " " << &c << std::endl;

    Linked_ptr<MySimpleClass<int>> ptr_myclass(new MySimpleClass<int>(t));
    std::cout << ptr_myclass->getval() << std::endl;
    std::cout << *ptr_myclass << std::endl;
    std::cout << ptr_myclass.get_size() << std::endl;
    Linked_ptr<MySimpleClass<int>> ptr_myclass_second(ptr_myclass);
    std::cout << ptr_myclass_second->getval() << std::endl;
    std::cout << *ptr_myclass_second << std::endl;
    std::cout << ptr_myclass.get_size() << std::endl;
    Linked_ptr<MySimpleClass<int>> ptr_myclass_third(ptr_myclass);
    Linked_ptr<MySimpleClass<int>> ptr_myclass_fourth(ptr_myclass_third);
    std::cout << ptr_myclass.get_size() << std::endl;
    std::cout << ptr_myclass_second.get() << std::endl;
    std::cout << ptr_myclass.get() << std::endl;
    std::cout << ptr_myclass_third.get() << std::endl;
    std::cout << ptr_myclass_fourth.get() << std::endl;

    Linked_ptr<int const> p1;
    std::cout << p1.operator->() << " " << p1.get() << std::endl;
    Linked_ptr<int const> p2(p);
    std::cout << p2.operator->() << " " << p2.get() << std::endl;
    Linked_ptr<int const> p3(a);
    std::cout << p3.operator->() << " " << p3.get() << std::endl;
    Linked_ptr p4(p2);
    std::cout << p4.operator->() << " " << p4.get() << std::endl;
    Linked_ptr<int const> p5;
    std::cout << p5.operator->() << " " << p5.get() << std::endl;
    p5 = p2;
    std::cout << p5.operator->() << " " << p5.get() << std::endl;
    p5 = p4;
    std::cout << p5.operator->() << " " << p5.get() << std::endl;
    p1 = p5;
    std::cout << p1.operator->() << " " << p1.get() << std::endl;
    p3.reset(nullptr);
    std::cout << p3.operator->() << " " << p3.get() << std::endl;
    p3 = p5;
    std::cout << p3.operator->() << " " << p3.get() << std::endl;
    p5.reset(nullptr);
    std::cout << p5.operator->() << " " << p5.get() << std::endl;
    Linked_ptr<int const> p6;
    std::cout << p6.operator->() << " " << p6.get() << std::endl;
    Linked_ptr<MySimpleClass<int>> p7;
    std::cout << p7.operator->() << " " << p7.get() << std::endl;
    p7 = p7;
    std::cout << p7.operator->() << " " << p7.get() << std::endl;
    p7.reset(nullptr);    
    std::cout << p7.operator->() << " " << p7.get() << std::endl;
    p7.reset(new MySimpleClass<int>(25));
    std::cout << p7.operator->() << " " << p7.get() << std::endl;
    Linked_ptr<MySimpleClass<int>> p8(new MySimpleClass<int>(15));
    std::cout << p8.operator->() << " " << p8.get() << std::endl;
    p8.reset(nullptr);
    std::cout << p8.operator->() << " " << p8.get() << std::endl;
    p1 = p1;
    std::cout << p1.operator->() << " " << p1.get() << std::endl;
    return 0;
}