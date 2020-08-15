/******************************
 * 观察者模式
 ******************************/
#include <iostream>
#include <vector>
#include <list>

using namespace std;

class Observer;
 
/*------------------------------------------*
 *通知（发布）者基类 
 *------------------------------------------*/
class Subject{
public:
	Subject(){}
	~Subject(){}	
	
	void attach(Observer* ob);
	void dettach(Observer* ob);
	
	void notify(); 
	
	std::string getState()const{ return m_state;}
	void setState(const std::string& state){m_state = state;}

private:
	std::list<Observer*> m_observers;

	string m_state;
};

void Subject::attach(Observer* ob){
	if(ob){
		m_observers.push_back(ob);
	}	
};

void Subject::dettach(Observer* ob){
	if(ob){
		m_observers.remove(ob);
	}	
};

void Subject::notify(){
	for(Observer* ob  : m_observers){
		ob->update();		
	}		
};
 
 
/*------------------------------------------*
 *观察（订阅）者基类 
 *------------------------------------------*/
class Observer{
public:
	Observer(Subject* subject);
	~Observer(){}
	
protected:
 	virtual void update() = 0;	
	
	Subject* m_subject;

};

Observer::Observer(Subject* subject){
	if(subject){
		m_subject = subject;
		m_subject->attach(this);	
	}
};

 
/*------------------------------------------*
 *网格图，继承自Subject
 *------------------------------------------*/ 
class MeshPlot : public Subject{

	
};
 
 
/*------------------------------------------*
 *图形区，继承自Observer
 *------------------------------------------*/ 
class ViewerWidget : public Observer{
protected:
  	void update();	
};
void ViewerWidget::update(){
	cout << "图形区更新：" << m_subject->getState();
};
  
  
/*------------------------------------------*
 *属性区，继承自Observer
 *------------------------------------------*/ 
class PropertyWidget : public Observer{
protected:
  	void update(); 
};
void PropertyWidget::update(){
	cout << "属性区更新：" << m_subject->getState();
};


/*------------------------------------------*
 *日志区，继承自Observer
 *------------------------------------------*/ 
class LoggerWidget : public Observer{
protected:
  	void update(); 
};
void LoggerWidget::update(){
	cout << "日志区更新：" << m_subject->getState();
};
 
 
/*------------------------------------------*
 *主函数
 *------------------------------------------*/ 
int main(){
 	MeshPlot meshPlot;

	ViewerWidget viwer(&meshPlot);
	PropertyWidget property(&meshPlot);
	LoggerWidget logger(&meshPlot);
	
	meshPlot.setState("New State.");
	meshPlot.notify();
 	
 	
};