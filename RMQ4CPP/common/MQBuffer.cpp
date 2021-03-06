/******************************************************************************************
* RMQ4CPP 
* Auther : luxiang
* github:https://github.com/Lxxing?tab=repositories
* ��ӭ����ָ�� xiaoxiaomiantianwo@163.com
******************************************************************************************/

#include <iostream>
#include <stdio.h>
#include "MQBuffer.h"


namespace lxmq{



MQBuffer::MQBuffer()
{
	this->data = NULL;
	this->length = 0;
}

MQBuffer::MQBuffer(int length)
{
	this->length = length;
	this->data = (char*)malloc(length);
}
MQBuffer::~MQBuffer()
{	
	if (this->data != NULL)
	{
		free(this->data);
	}
}

void MQBuffer::Clean()
{	
	if(this->data != NULL)
	{
		free(this->data);
	}

	this->length = 0;
	
}

const char *MQBuffer::GetData() const
{
	return this->data;
}

int MQBuffer::GetSize() const
{
	return this->length;
}

void MQBuffer::SetSize(int newlen)
{
	this->length = newlen;
	this->data = (char*)malloc(newlen);
}


}//    end of lxmq

