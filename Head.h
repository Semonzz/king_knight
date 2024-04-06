#pragma once
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <vector>
#include <ctime>
#include "glut.h"

using namespace std;

const int W = 600;
const int H = 600;

const double PI = acos(-1.0);
double scale = 1;

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
    
}

void init() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-w/2*scale, w/2*scale, -h/2 * scale, h/2 * scale);
	glMatrixMode(GL_MODELVIEW);
}

struct point {
    double x, y;
    point() {
        x = 0;
        y = 0;
    }
    point(double x_r, double y_r) {
        x = x_r;
        y = y_r;
    }

    point operator + (point B) {
        point res;
        res.x = x + B.x;
        res.y = y + B.y;
        return res;
    }

    point operator - (point B) {
        point res;
        res.x = x - B.x;
        res.y = y - B.y;
        return res;
    }

    point operator * (double k) {
        point res;
        res.x = x * k;
        res.y = y * k;
        return res;
    }
};

double dist2(point A) {
    return (A.x * A.x + A.y * A.y); //в квадрате
}

double distance_point(point A, point B) {
    return (B.x - A.x) * (B.x - A.x) + (B.y - A.y) * (B.y - A.y);
}

double cross(point A, point B) {
    return A.x * B.y - B.x * A.y;
}

void Generate_point(point& A) {
    A.x = ((rand() % 4000) * 1.0 - 2000) / 1000;
    A.y = ((rand() % 4000) * 1.0 - 2000) / 1000;
}

void Generate_point_1(point& A, double size_1, double size_2) {
    int t;
    t = (size_2 - size_1) * 1000;
    int r = size_1;
    r *= 1000;
    A.x = ((rand() % t) * 1.0 + r) / 1000;
    A.y = ((rand() % (2*H * 10))-H*10)*1.0 / 1000;
}