/****************************************************************************
**
** Copyright 2019 yanglingwell@sina.com
**
** Permission is hereby granted, free of charge, to any person obtaining
** a copy of this software and associated documentation files (the "Software"),
** to deal in the Software without restriction, including without limitation the
** rights to use, copy, modify, merge, publish, distribute, sublicens-e, and/or
** sell copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in
** all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
** THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/
/*
 *【题目】
 * 根据已知的 Pet， Dog， Cat 类，实现猫狗队列。
 *【要求】
 * 猫狗队列具有以下功能：
 *（1）add          将 Cat 对象或 Dog 对象加入猫狗队列中；
 *（2）poll         将猫狗队列中的所有对象按照入队顺序弹出队首元素
 *（3）poll_dog     将猫狗队列中的狗对象按照入队顺序弹出队首元素
 *（4）poll_cat     将猫狗队列中的猫对象按照入队顺序弹出队首元素
 *（5）empty/empty_cat/empty_dog 判断猫狗队列中是否没有“猫/狗”/“猫”/“狗”
 *【解题思路】 
 * 维护两个个带有队首元素入队时间的队列，分别保存入队的猫狗元素。
 * 猫狗的出队顺序根据队首元素的入队时间判断
 */

#include<string>
#include<iostream>
#include<queue>
#include <utility> 
using namespace std;

class Pet
{
public:
    Pet(const string& type) : _type(type){}
    
string get_pet_type() const
    {
        return _type;
    }
private:
    string _type;
};

class Dog : public Pet
{
public:
    Dog() : Pet("dog"){}
};

class Cat : public Pet
{
public:
    Cat() : Pet("cat"){}
};

// the queue with timestamp
template<typename _Ty>
class QueueWithTimeStamp
{
public:
    void add(const _Ty elem, size_t timestamp)
    {
        _que_with_timestamp.push({elem, timestamp});
    }
    
    pair<_Ty, size_t> peek() const
    {
        if (_que_with_timestamp.empty()) 
        {
            return {_Ty(), (size_t)0};
        }
        return _que_with_timestamp.front();
    }

    pair<_Ty, size_t> poll()
    {
        if (_que_with_timestamp.empty())
        {
            return {_Ty(), (size_t)0};
        }
        auto ret = this->peek();
        _que_with_timestamp.pop();
        
        return ret;
    }

    bool empty() const
    {
        return _que_with_timestamp.empty();
    }
private:
    queue<pair<_Ty, size_t>> _que_with_timestamp;
};

// the queue of cats and dogs
class CatDogQueue
{
public:
    CatDogQueue():timestamp(0){}
    
    void add(Pet* pet)
    {
        if (pet == nullptr) return;
        if (pet->get_pet_type() == "dog")
        {
            _queue_dogs.add(pet, timestamp++);
        }
        else if (pet->get_pet_type() == "cat")
        {
            _queue_cats.add(pet, timestamp++);
        }
    }
    
    bool empty() const
    {
        return (empty_dog() && empty_cat());
    }
    bool empty_cat() const
    {
        return _queue_cats.empty();
    }
    bool empty_dog() const
    {
        return _queue_dogs.empty();
    }

    Pet* poll()
    {
        if (empty()) return nullptr;
        if (empty_dog()) return _queue_cats.poll().first;
        if (empty_cat()) return _queue_dogs.poll().first;

        // FIFO
        if (_queue_dogs.peek().second < _queue_cats.peek().second)
        {
            return _queue_dogs.poll().first;
        }
        else
        {
            return _queue_cats.poll().first;
        }
    }
    Pet* poll_dog()
    {
        return _queue_dogs.poll().first;        
    }
    Pet* poll_cat()
    {
        return _queue_cats.poll().first;        
    }
private:
    QueueWithTimeStamp<Pet*> _queue_dogs, _queue_cats;
    size_t timestamp;
};

int main()
{
    CatDogQueue que;

    que.add(new Cat()); que.add(new Dog()); que.add(new Dog());
    que.add(new Cat()); que.add(new Cat()); que.add(new Dog());

    while (!que.empty())
    {
        Pet* pet = que.poll();
        cout << pet->get_pet_type() << " ";
        delete pet;
    }
    cout << endl;

    que.add(new Cat()); que.add(new Dog()); que.add(new Dog());
    que.add(new Cat()); que.add(new Cat()); que.add(new Dog());

    cout << "dogs: ";
    while (!que.empty_dog())
    {
        Pet* pet = que.poll_dog();
        cout << pet->get_pet_type() << " ";
        delete pet;
    }
    cout << endl << "cats: ";
    while (!que.empty_cat())
    {
        Pet* pet = que.poll_cat();
        cout << pet->get_pet_type() << " ";
        delete pet;
    }
    cout << endl;

    return 0;
}
