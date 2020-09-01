/******************************
 * 单例模式
 ******************************/
#include <iostream>
using namespace std;

/*------------------------------------------*
/* 最一般的实现(懒汉) - 线程不安全
 *------------------------------------------*/
class Singleton01
{
public:
    static Singleton01 *insteace(){
        if (m_self == NULL){
            m_self = new Singleton01();
        }
        return m_self;
    }

    void showMessage() { cout << "hello 1" << endl; }

private:
    static Singleton01 *m_self;

    Singleton01(){	cout << "Construct 01." << endl;}

};
Singleton01* Singleton01::m_self = NULL;


/*------------------------------------------*
 * 饿汉模式 - 一启动就初始化
 * 过早占用资源, 拖慢启动速度 , 但线程安全
 *------------------------------------------*/
class Singleton02
{
public:
    static Singleton02 *insteace(){ return m_self;	}

    void showMessage() { cout << "hello 2" << endl; }

private:
    static Singleton02* m_self;

    Singleton02(){	cout << "Construct 02." << endl;}
};
Singleton02* Singleton02::m_self = new Singleton02();


/*------------------------------------------*
 * 饿汉模式 - 简化版
 *------------------------------------------*/
class Singleton03
{
public:
    static Singleton03 *m_self;

    void showMessage() { cout << "hello 3" << endl; }

private:
    Singleton03(){	cout << "Construct 03." << endl;}
};
Singleton03 * Singleton03::m_self  = new Singleton03();


/*------------------------------------------*
 * 懒汉模式 - 用的时候才初始化
 * 线程不安全 ，需要加锁。双重检查锁定
 *------------------------------------------*/
#include <mutex>
mutex m_mutex;
class Singleton04
{
public:
    static Singleton04 *insteace(){
        if (m_self == NULL){
            m_mutex.lock();
            if (m_self == NULL){
                m_self = new Singleton04();
            }
            m_mutex.unlock();
        }
        return m_self;
    }

    void showMessage() { cout << "hello 4" << endl; }

private:
    static Singleton04 *m_self;

    Singleton04(){	cout << "Construct 04." << endl;}

};
Singleton04* Singleton04::m_self = NULL;


/*------------------------------------------*
 * Meyers' Singleton --《Effective C++》
 * 使用函数内的 local static 对象
 *  -- 对于local static 对象，其初始化发生在控制流第一次执行到该对象的初始化语句时。多个线程的控制流可能同时到达其初始化语句。
 *  -- C++11规定了local static在多线程条件下的初始化行为，要求编译器保证了内部静态变量的线程安全性。
 *------------------------------------------*/
class Singleton05
{
private:
    Singleton05() {	cout << "Construct 05." << endl;}
    ~Singleton05() { }
    Singleton05(const Singleton05&);
    Singleton05& operator=(const Singleton05&);

public:
    static Singleton05& getInstance()
    {
        static Singleton05 instance; //local static 对象
        return instance;
    }

    static void* showMessage(void* args) { cout << "hello 5" << endl; }//必须将该函数声明为静态函数函数,方便多线程调用
};



#if 1

/*主程序*/
int main(){

    Singleton01::insteace()->showMessage();

    Singleton02::insteace()->showMessage();

    Singleton03::m_self->showMessage();

    Singleton04::insteace()->showMessage();

    Singleton05::getInstance().showMessage(NULL);

    getchar();
    return 0;
}

#else

/*主程序(多线程)*/
#include <pthread.h>
#define NUM_THREADS 100
int main(){
    // 定义线程的 id 变量，多个变量使用数组
    pthread_t tids[NUM_THREADS];

    for(int i = 0; i < NUM_THREADS; ++i)
    {
        //参数依次是：创建的线程id，线程参数，调用的函数，传入的函数参数
        int ret = pthread_create(&tids[i], NULL, Singleton05::getInstance().showMessage, NULL);
        if (ret != 0)
        {
            cout << "pthread_create error: error_code=" << ret << endl;
        }
    }
    //等各个线程退出后，进程才结束，否则进程强制结束了，线程可能还没反应过来；
    pthread_exit(NULL);

    getchar();
}

#endif

