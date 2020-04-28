#pragma once
#include"para.h"
class Star
{
public:
	GLfloat x=0,y=0;
	plantTYPE pty;
	//颜色
	GLfloat color[4];
	//星球半径 
	GLfloat selfradius;
	//自传速度  
	GLfloat selfspeed;
	//公转速度 
	GLfloat  speed;
	//公转半径
	GLfloat radius;
	//自传角度
	GLfloat selfalpha;	
	//自传周期
	int selfT;
	Star* parent;
	//子星球链表 
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
	构造函数 创建星球必须提供
	颜色   color[4];
	星球半径 selfradius;
	自传速度 selfspeed;
	公转速度 speed;
	公转半径 radius;
	自传角度 selfalpha;
	子星球链表 *childstar;
	*/
	Star(GLfloat color[4], GLfloat selfradius, GLfloat selfspeed, GLfloat  speed, GLfloat radius, int selfT,plantTYPE pty=sun)
		: selfradius(selfradius), selfspeed(selfspeed), speed(speed), radius(radius), selfT(selfT) ,childstar(nullptr), brotherstar(nullptr),parent(nullptr),pty(pty)
	{
		this->color[0] = color[0];
		this->color[1] = color[1];
		this->color[2] = color[2];
		this->color[3] = color[3];
	}
	//必须具备更新绘制函数
	void DrawStar(int timecc);
	//本星球的移动函数
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
	//默认实现负责星球的数据更新
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
	//重写draw方法
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
		: Star(color, selfradius, selfspeed, speed, radius, selfT, pty)	//绘制光照
	{
	}
	void drawLight();
	//重写draw方法
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
	//定义观察角度
	GLdouble viewX, viewY, viewZ;
	GLdouble centerX, centerY, centerZ;
	GLdouble upX, upY, upZ;
};