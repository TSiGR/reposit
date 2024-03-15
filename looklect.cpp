#include <iostream>

void make(int value) { std::cout << "int\n"; }
void make(const char* value) { std::cout << "char* object\n"; }

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

    List(const T* ptr)
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

    ~List()
    {

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

    explicit Linked_ptr(T* ptr)
    {
        m_ptr = ptr;
        m_list = new List(m_ptr);
    }
    Linked_ptr(const Linked_ptr<T>& another)
    {
        m_ptr = another.m_ptr;
        m_list = another.m_list;
        m_list->add(m_ptr);
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
        m_list->remove();
    }

    Linked_ptr(Linked_ptr &&another) = delete;
    Linked_ptr& operator=(Linked_ptr &&another) = delete;
    Linked_ptr& operator=(const Linked_ptr &another) = delete;
    private:

    List<T> *m_list;
    T *m_ptr;
};

int main()
{
    make(0);
    make(nullptr);

    const int c = 9;
    int t = 8;
    int const *p = &c;
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
    return 0;
}