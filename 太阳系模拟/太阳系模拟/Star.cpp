#include "Star.h"
void draw_wired_circle(float x, float y, float radius)
{
	int count;
	int sections = 200;

	GLfloat TWOPI = 2.0f * 3.14159f;

	glBegin(GL_LINE_STRIP);
	for (count = 0; count <= sections; count++)
	{
		glVertex2f(x + radius*cos(count*TWOPI / sections), y + radius*sin(count*TWOPI / sections));
	}
	glEnd();
}
void Star::DrawStar(int timecc)
{
	glPointSize(1);
	glPushMatrix();
	glPointSize(2);
	draw_wired_circle(0, 0, 5);
	draw_wired_circle(0, 0, 6);
	draw_wired_circle(0, 0, 9);
	draw_wired_circle(0, 0, 13);
	glPointSize(1);
	//����ת�뾶Ϊ��ʱ��������Ϊ����
	if (this->pty == sun)
	{	
		glColor3f(this->color[0], this->color[1], this->color[2]);

		glBegin(GL_POLYGON);
		for (int i = 0; i < n; i++)
		{
			glVertex2f(this->selfradius  * cos(2 * PI*i / n), this->selfradius * sin(2 * PI*i / n));   //���嶥��
		}
	}
	else
	{
		glColor3f(this->color[0], this->color[1], this->color[2]);
		if (this->parent != nullptr)
		{
			glTranslatef(this->parent->x, this->parent->y, 0.0);
		}
		glTranslatef(this->radius * sin(PI * 2 * (timecc%this->selfT) / this->selfT), this->radius * cos(PI * 2 * (timecc%this->selfT) / this->selfT), 0.0);
		glBegin(GL_POLYGON);
		for (int i = 0; i < n; i++)
		{
			glVertex2f(this->selfradius  * cos(2 * PI*i / n), this->selfradius * sin(2 * PI*i / n));   //���嶥��
		}
		x = this->radius * sin(PI * 2 * (timecc%this->selfT) / this->selfT);
		y = this->radius * cos(PI * 2 * (timecc%this->selfT) / this->selfT);
	}
	glEnd();
	glPopMatrix();
}

void Star::MoveStar()
{
}
SolarSystem::SolarSystem()
{
	GLfloat sun_c[4] = { 0.8,0.8,0.0,0.1 };//��ɫ
	GLfloat water_c[4] = { 0.66,0.66,0.66,0.1 };//����
	GLfloat glad_c[4] = { 0.51,0.51,0.0,0.1 };//��ɫ
	GLfloat earth_c[4] = { 0.8,0.3,1.0,0.1 };//��ɫ
	GLfloat moon_c[4] = { 0.5,0.5,0.5,0.1 };//��ɫ
	GLfloat burn_c[4] = { 1.0,0.0,0.0,0.1 };//��ɫ

	this->stars = new LightStar(sun_c, 2.5, 10, 3, 0,0);//̫��
	//����۲�Ƕ�
	viewX = 0.0, viewY = 0.0, viewZ = 20.0;
	//���ﲻ֪��ΪʲôviewZ����>20 Ȼ��ͺ���  лл
	//��������1399130811@qq.com
	centerX = 0.0, centerY = 0.0, centerZ = 0.0;
	upX = 0.0, upY = 1.0, upZ = 0.0;	

	GLfloat m[4] = { 0.6,0.3,0.8,0.1 }; 

//ˮ��
	this->stars->childstar = new PlanetStar(water_c, 0.3, 6, 10, 5, 30, water);
	this->stars->childstar->parent = this->stars;	
	//����
	this->stars->childstar->brotherstar = new PlanetStar(glad_c, 0.2, 6, 10, 6, 100, glad);
	this->stars->childstar->brotherstar->parent = this->stars;
	//����
	this->stars->childstar->brotherstar->brotherstar = new PlanetStar(earth_c,0.4, 6, 10,9, 150, earth);
	this->stars->childstar->brotherstar->brotherstar->parent = this->stars;
	//����
	this->stars->childstar->brotherstar->brotherstar->childstar = new PlanetStar(moon_c,0.2, 6, 10, 1, 19, moon);
	this->stars->childstar->brotherstar->brotherstar->childstar->parent = this->stars->childstar->brotherstar->brotherstar;
	//����	
	this->stars->childstar->brotherstar->brotherstar->brotherstar  = new PlanetStar(burn_c, 0.2, 6, 10,13, 400, burn);
	this->stars->childstar->brotherstar->brotherstar->brotherstar->parent = this->stars;

}

SolarSystem::~SolarSystem()
{
	if (stars != nullptr)
	{
		delete stars;
	}
}

void SolarSystem::onDisplay(int timecc)
{
	if (stars != nullptr)
		stars->Draw(timecc);
}

void SolarSystem::onUpdate()
{
}

void LightStar::drawLight()
{
}
