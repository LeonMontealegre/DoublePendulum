#include <emscripten.h>
#include <stdint.h>
#include <cmath>

#include <leon/utils.h>
#include <leon/vector.h>
#include <leon/integrators.h>

#define FUNC EMSCRIPTEN_KEEPALIVE

extern "C" {
	void init(double theta0, double theta1, double dTheta0, double dTheta1);
	void step(double h);
	double a1();
	double a2();
}

#define g 9.81
#define L1 5.0
#define L2 3.0
#define m1 1.0
#define m2 1.0


static Vec4 theta;
static double t;

FUNC Vec4 f(double t, Vec4 theta) {
	double a1 = theta[0];
	double w1 = theta[1];
	double a2 = theta[2];
	double w2 = theta[3];

	return Vec(w1,
			   (-g*(2*m1+m2)*sin(a1) - m2*g*sin(a1-2*a2) - 2*sin(a1-a2)*m2*(w2*w2*L2 + w1*w1*L1*cos(a1 - a2)))  /  (L1 * (2*m1 + m2 - m2*cos(2*a1 - 2*a2))),
			   w2,
			   (2*sin(a1-a2)*(w1*w1*L1*(m1 + m2) + g*(m1 + m2)*cos(a1) + w2*w2*L2*m2*cos(a1 - a2)))  /  (L2 * (2*m1 + m2 - m2*cos(2*a1 - 2*a2))));

	// return Vec(theta[1],
	// 		   (w2*l*(-sin(theta[0]) + M*cos(dTheta)*sin(theta[2])) - M*l*(theta[1]*theta[1]*cos(dTheta) + l*theta[3]*theta[3])*sin(dTheta)) / (l - M*l*cos(dTheta)*cos(dTheta)),
	// 		   theta[3],
	// 		   (w2*cos(dTheta)*sin(theta[0]) - w2*sin(theta[2]) + (theta[1]*theta[1] + M*l*theta[3]*theta[3]*cos(dTheta))*sin(dTheta)) / (l - M*l*cos(dTheta)*cos(dTheta)));
}

FUNC void init(double theta0, double theta1, double dTheta0, double dTheta1) {
	theta = Vec(theta0, dTheta0, theta1, dTheta1);
	t = 0;
}

FUNC void step(double h) {
	theta = rk4_single(f, t, h, theta);
	t += h;
}

FUNC double a1() {
	return theta[0];
}
FUNC double a2() {
	return theta[2];
}
