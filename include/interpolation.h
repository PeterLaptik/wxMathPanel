#ifndef INTERPOLATION_H_INCLUDED
#define INTERPOLATION_H_INCLUDED

#include "stddef.h"

////////////////////////////////////////////////////////////////////
// Classes to implement polynomial interpolation in Lagrange form //
////////////////////////////////////////////////////////////////////

// Maximum points for polynom
static const int MAX_POINTS = 20;

// Point on a flat surface
// Decart's coordinates
struct Point
{
	double x;
	double y;
};

// Simple expression:
// Multiplier*x^power
struct Monom
{
    int power;          // power for x
    double multiplier;  // float point multiplier
};

// Sum of two monoms:
// Multiplier1*x^power1 + Multiplier2*x^power2
struct Dinom
{
    Monom m1;
    Monom m2;
};

//
// Polynomial interpolation computing
class Polynom
{
	public:
		Polynom();
		~Polynom();
		bool SetPoint(double x, double y, int pos);
		int GetCount(void) const;
		Point* GetPointArray(void);
		double* GetPolynomialArray(void);
		Point GetPoint (int pos) const;
		void SetCount(int number);

		// Coefficients calculating
		bool CheckPoints(void);
		void Calculate(void);
		double GetMaxX(void);
		double GetMinX(void);

	protected:

	private:
	    int CalculateSingleMultiply(Dinom a, Monom *result, size_t n);
	    void CalculateNumberMultiply(double number, Monom *result, size_t n);

		Point m_points[MAX_POINTS];             // points list
		double m_polynomial[MAX_POINTS];        // result polynomial
		double m_coeffitients[MAX_POINTS];
		int m_counter;
};

#endif // INTERPOLATION_H_INCLUDED
