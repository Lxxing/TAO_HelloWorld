/******************************************************************************************
* RMQ4CPP 
* Auther : luxiang
* github:https://github.com/Lxxing?tab=repositories
* ��ӭ����ָ�� xiaoxiaomiantianwo@163.com
******************************************************************************************/
#ifndef __MQBUFFER__H_
#define __MQBUFFER__H_

namespace lxmq{



class MQBuffer
{
public:

	MQBuffer();
	MQBuffer(int length);
	~MQBuffer();
	void Clean();
	const char * GetData() const;
	int GetSize() const;
	void SetSize(int newlen);
private:
	char * data;
	int length;


};






}//    end of lxmq




#endif //__MQBUFFER__H_

