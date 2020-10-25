

#include "Render.h"

#include <Windows.h>
#include <GL\GL.h>
#include <GL\GLU.h>
#include <corecrt_math.h>
using namespace std;

void DrawingFigure();
void DrawingCircleWalls(double* X, double* Y);
void FoundR(double* X, double* Y, double R[]);
double FoundCosAngle();

double A1[] = { 0,0,0.1 };
double B1[] = { 5,0,0.1 };
double C1[] = { 2,7,0.1 };
double D1[] = { 9,15,0.1 };
double E1[] = { -1,13,0.1 };
double F1[] = { -4,6,0.1 };

double A2[] = { 0,0,4 };
double B2[] = { 5,0,4 };
double C2[] = { 2,7,4 };
double D2[] = { 9,15,4 };
double E2[] = { -1,13,4 };
double F2[] = { -4,6,4 };

double R[] = { 0,0,0,0 };


void Render(double delta_time)
{    

	glPushMatrix();
	glTranslated(4.5, -4, 0);
	DrawingFigure();
	glPopMatrix();
}   

void DrawingFigure()
{
#pragma region Base

	glBegin(GL_TRIANGLES);
	glColor3d(0.2, 0.2, 0.2);
	glVertex3dv(A1);
	glVertex3dv(B1);
	glVertex3dv(C1);

	glVertex3dv(C1);
	glVertex3dv(A1);
	glVertex3dv(F1);

	glVertex3dv(F1);
	glVertex3dv(C1);
	glVertex3dv(E1);

	glVertex3dv(E1);
	glVertex3dv(C1);
	glVertex3dv(D1);
	//---------------------------
	glNormal3d(0, 0, 1);
	glVertex3dv(A2);
	glVertex3dv(B2);
	glVertex3dv(C2);

	glVertex3dv(C2);
	glVertex3dv(A2);
	glVertex3dv(F2);

	glVertex3dv(F2);
	glVertex3dv(C2);
	glVertex3dv(E2);

	glVertex3dv(E2);
	glVertex3dv(C2);
	glVertex3dv(D2);
	glEnd();
#pragma endregion

#pragma region Walls

	
	glBegin(GL_QUADS);
	glColor3d(0.8, 0, 0);
	glTexCoord2d(0, 0);
	glVertex3dv(A1);
	glTexCoord2d(0, 1);
	glVertex3dv(A2);
	glTexCoord2d(1, 1);
	glVertex3dv(B2);
	glTexCoord2d(1, 0);
	glVertex3dv(B1);
	glEnd();

	glBegin(GL_QUADS);
	glColor3d(0.7, 0, 0);
	glTexCoord2d(0, 1);
	glVertex3dv(C1);
	glTexCoord2d(1, 1);
	glVertex3dv(C2);
	glTexCoord2d(1, 0);
	glVertex3dv(B2);
	glTexCoord2d(0, 0);
	glVertex3dv(B1);
	glEnd();

	
	glBegin(GL_QUADS);
	glColor3d(0.6, 0, 0);
	glTexCoord2d(0, 0);
	glVertex3dv(C1);
	glTexCoord2d(0, 1);
	glVertex3dv(C2);
	glTexCoord2d(1, 1);
	glVertex3dv(D2);
	glTexCoord2d(1, 0);
	glVertex3dv(D1);

	
	glColor3d(0.5, 0, 0);
	glVertex3dv(D1);
	glVertex3dv(D2);
	glVertex3dv(E2);
	glVertex3dv(E1);
	glEnd();


	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBegin(GL_QUADS);
	//glColor4d(0.3, 0.5, 0.2, 0.3);
	
	glVertex3dv(F1);
	glVertex3dv(F2);
	glVertex3dv(A2);
	glVertex3dv(A1);
	glEnd();
#pragma endregion

#pragma region Semicircle
	double grad = 0.005;
	double X[] = { 0,0,0.1 };
	double Y[] = { 0,0,0.1 };

	FoundR(F1, E1, R);

	glPushMatrix();
	//glTranslated(0.01, 0.01, 0);
	double angle = FoundCosAngle();
	for (double i = 0.005; i < 3.145; i += 0.005)
	{
		X[0] = (R[0] + cos(angle + i - grad) * R[3]);
		X[1] = (R[1] + sin(angle + i - grad) * R[3]);

		Y[0] = (R[0] + cos(angle + i) * R[3]);
		Y[1] = (R[1] + sin(angle + i) * R[3]);

		glBegin(GL_TRIANGLES);
		glColor3d(0, 0.7, 0);
		glVertex3d(R[0], R[1], R[2]);
		glVertex3d(X[0], X[1], 0.1);
		glVertex3d(Y[0], Y[1], 0.1);

		glVertex3d(R[0], R[1], 4);
		glVertex3d(X[0], X[1], 4);
		glVertex3d(Y[0], Y[1], 4);

		glEnd();

		glBegin(GL_QUADS);
		glColor3d(0, 0, 0.6);
		glVertex3d(X[0], X[1], 0.1);
		glVertex3d(Y[0], Y[1], 0.1);
		glVertex3d(Y[0], Y[1], 4);
		glVertex3d(X[0], X[1], 4);
		glEnd();
	}

	glPopMatrix();
#pragma endregion

}

void DrawingCircleWalls(double* X, double* Y)
{
	glBegin(GL_QUADS);
	glVertex3d(*X, *++X, 0.1);
	glVertex3d(*Y, *++Y, 0.1);
	*--Y;
	glVertex3d(*Y, *++Y, 4);
	*--X;
	glVertex3d(*X, *++X, 4);
	glEnd();
}

void FoundR(double* X, double* Y, double R[])
{
	R[0] = (*X + *Y) / 2;
	X++;
	Y++;
	R[1] = (*X + *Y) / 2;
	R[2] = 0.1;
	X--;
	Y--;
	R[3] = sqrt(pow(X[0] - Y[0], 2) + pow(X[1] - Y[1], 2) + 0) / 2;
}

double FoundCosAngle()
{
	double Gipoten = sqrt(1.5 * 1.5 + 3.5 * 3.5);
	double CosAngle = 1.5 / Gipoten;
	return acos(CosAngle);
}