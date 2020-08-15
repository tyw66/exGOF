/******************************
 * �۲���ģʽ
 ******************************/
#include <iostream>
#include <vector>
#include <list>

using namespace std;

class Observer;
 
/*------------------------------------------*
 *֪ͨ���������߻��� 
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
 *�۲죨���ģ��߻��� 
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
 *����ͼ���̳���Subject
 *------------------------------------------*/ 
class MeshPlot : public Subject{

	
};
 
 
/*------------------------------------------*
 *ͼ�������̳���Observer
 *------------------------------------------*/ 
class ViewerWidget : public Observer{
protected:
  	void update();	
};
void ViewerWidget::update(){
	cout << "ͼ�������£�" << m_subject->getState();
};
  
  
/*------------------------------------------*
 *���������̳���Observer
 *------------------------------------------*/ 
class PropertyWidget : public Observer{
protected:
  	void update(); 
};
void PropertyWidget::update(){
	cout << "���������£�" << m_subject->getState();
};


/*------------------------------------------*
 *��־�����̳���Observer
 *------------------------------------------*/ 
class LoggerWidget : public Observer{
protected:
  	void update(); 
};
void LoggerWidget::update(){
	cout << "��־�����£�" << m_subject->getState();
};
 
 
/*------------------------------------------*
 *������
 *------------------------------------------*/ 
int main(){
 	MeshPlot meshPlot;

	ViewerWidget viwer(&meshPlot);
	PropertyWidget property(&meshPlot);
	LoggerWidget logger(&meshPlot);
	
	meshPlot.setState("New State.");
	meshPlot.notify();
 	
 	
};