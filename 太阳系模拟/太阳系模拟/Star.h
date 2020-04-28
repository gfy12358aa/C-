#pragma once
#include"para.h"
class Star
{
public:
	GLfloat x=0,y=0;
	plantTYPE pty;
	//��ɫ
	GLfloat color[4];
	//����뾶 
	GLfloat selfradius;
	//�Դ��ٶ�  
	GLfloat selfspeed;
	//��ת�ٶ� 
	GLfloat  speed;
	//��ת�뾶
	GLfloat radius;
	//�Դ��Ƕ�
	GLfloat selfalpha;	
	//�Դ�����
	int selfT;
	Star* parent;
	//���������� 
	Star *childstar;
	Star *brotherstar;
	Star() {}
	~Star() 
	{
		if (this->childstar != nullptr)
		{
			this->childstar->~Star();
			delete this->childstar;
		}	
		if (this->brotherstar != nullptr)
		{
			this->brotherstar->~Star();
			delete this->brotherstar;
		}
	}
	/*
	���캯�� ������������ṩ
	��ɫ   color[4];
	����뾶 selfradius;
	�Դ��ٶ� selfspeed;
	��ת�ٶ� speed;
	��ת�뾶 radius;
	�Դ��Ƕ� selfalpha;
	���������� *childstar;
	*/
	Star(GLfloat color[4], GLfloat selfradius, GLfloat selfspeed, GLfloat  speed, GLfloat radius, int selfT,plantTYPE pty=sun)
		: selfradius(selfradius), selfspeed(selfspeed), speed(speed), radius(radius), selfT(selfT) ,childstar(nullptr), brotherstar(nullptr),parent(nullptr),pty(pty)
	{
		this->color[0] = color[0];
		this->color[1] = color[1];
		this->color[2] = color[2];
		this->color[3] = color[3];
	}
	//����߱����»��ƺ���
	void DrawStar(int timecc);
	//��������ƶ�����
	void MoveStar();
	virtual void Draw(int timecc)
	{
		DrawStar(timecc);
		if (brotherstar != nullptr)
		{
			for (auto i = brotherstar; i != nullptr; i = i->brotherstar)
			{
				i->Draw( timecc);
			}
		}	
		if (childstar != nullptr)
		{
			for (auto i = childstar; i != nullptr; i = i->childstar)
			{
				i->Draw(timecc);
			}
		}
	}
	//Ĭ��ʵ�ָ�����������ݸ���
	virtual void Updata(int timecc) { MoveStar(); Draw(timecc); }
};


class PlanetStar :public Star
{
public:
	PlanetStar(GLfloat color[4], GLfloat selfradius, GLfloat selfspeed, GLfloat  speed, GLfloat radius, int selfT, plantTYPE pty = sun)
		: Star(color,selfradius,selfspeed,speed, radius, selfT,pty)
	{
	}
	void drawPlanet();
	//��дdraw����
	virtual void Draw(int timecc)override
	{
		DrawStar(timecc);
		if (brotherstar != nullptr)
		{
			for (auto i = brotherstar; i != nullptr; i = i->brotherstar)
			{
				i->Draw(timecc);
			}
		}
		if (childstar != nullptr)
		{
			for (auto i = childstar; i != nullptr; i = i->childstar)
			{
				i->Draw(timecc);
			}
		}
	}
};

class LightStar :public Star
{
public:
	LightStar(GLfloat color[4], GLfloat selfradius, GLfloat selfspeed, GLfloat  speed, GLfloat radius, int selfT, plantTYPE pty = sun)
		: Star(color, selfradius, selfspeed, speed, radius, selfT, pty)	//���ƹ���
	{
	}
	void drawLight();
	//��дdraw����
	virtual void Draw(int timecc)override {
		DrawStar(timecc);
		drawLight(); 	
		if (brotherstar != nullptr)
		{
			for (auto i = brotherstar; i != nullptr; i = i->brotherstar)
			{
				i->Draw( timecc);
			}
		}
		if (childstar != nullptr)
		{
			for (auto i = childstar; i != nullptr; i = i->childstar)
			{
				i->Draw(timecc);
			}
		}
	}

};

class SolarSystem
{
public:
	SolarSystem();
	~SolarSystem();

	void onDisplay(int timecc);
	void onUpdate();

	Star *stars;
	//����۲�Ƕ�
	GLdouble viewX, viewY, viewZ;
	GLdouble centerX, centerY, centerZ;
	GLdouble upX, upY, upZ;
};