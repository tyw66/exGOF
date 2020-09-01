/******************************
 * 观察者模式
 ******************************/
#include <iostream>
#include <vector>
#include <list>

#include "testwidget.h"

using namespace std;

class Observer;

/*------------------------------------------*
 *通知（发布）者基类
 *------------------------------------------*/
class Subject
{
public:
    Subject();
    ~Subject();

    void attach(Observer *ob);
    void dettach(Observer *ob);

    void notify();

    std::string getState() const { return m_state; }
    void setState(const std::string &state) { m_state = state; }

private:
    std::list<Observer *> m_observers;

    string m_state;
};

void Subject::attach(Observer *ob)
{
    if(ob){
        m_observers.push_back(ob);
    }
};

void Subject::dettach(Observer *ob)
{
    if(ob){
        m_observers.remove(ob);
    }
};

/*------------------------------------------*
 *网格图，继承自Subject
 *------------------------------------------*/
class MeshPlot : public Subject
{
};

/*------------------------------------------*
 *观察（订阅）者基类
 *------------------------------------------*/
class Observer
{
public:
    Observer(Subject *subject);
    ~Observer() {}

    virtual void update() = 0;
    virtual void subjectRemoved(Subject *) { m_subject = 0; }

protected:
    Subject *m_subject;
};

Observer::Observer(Subject *subject)
{
    if (subject){
        m_subject = subject;
        m_subject->attach(this);
    }
};

/*------------------------------------------*
 *图形区，继承自Observer
 *------------------------------------------*/
class ViewerWidget : public Observer
{
public:
	ViewerWidget(Subject *sub);

	void update();
};

ViewerWidget::ViewerWidget(Subject *sub) : Observer(sub)
{
}

void ViewerWidget::update()
{
	cout << "viewer widget update. " << m_subject->getState() << endl;
};

/*------------------------------------------*
 *属性区，继承自Observer
 *------------------------------------------*/
class PropertyWidget : public Observer
{
public:
	PropertyWidget(Subject *sub);

	void update();
};

PropertyWidget::PropertyWidget(Subject *sub) : Observer(sub)
{
}

void PropertyWidget::update()
{
	cout << "property widget update. " << m_subject->getState() << endl;
};

/*------------------------------------------*
 *日志区，继承自Observer
 *------------------------------------------*/
class LoggerWidget : public Observer
{
public:
	LoggerWidget(Subject *sub);
	void update();
};

LoggerWidget::LoggerWidget(Subject *sub) : Observer(sub)
{
}
void LoggerWidget::update()
{
	cout << "logger widget update. " << m_subject->getState() << endl;
};

/***************/
Subject::Subject()
{
	std::list<Observer *>::iterator pos;
	for (pos = m_observers.begin(); pos != m_observers.end(); ++pos)
	{
		(*pos)->subjectRemoved(this);
    }
}

Subject::~Subject()
{

};

void Subject::notify()
{
	for (Observer *ob : m_observers)
	{
		ob->update();
	}
};


/*------------------------------------------*
 *主函数
 *------------------------------------------*/
int main()
{
	MeshPlot meshPlot;

	ViewerWidget viwer(&meshPlot);
	LoggerWidget logger(&meshPlot);
    PropertyWidget property(&meshPlot);

	meshPlot.setState("New State.");
	meshPlot.notify();


    TestWidget w;
    w.update();

	getchar();
};
