#include "interpolation.h"

Polynom::Polynom()
{
	m_counter = 0;
	for (int i=0; i<MAX_POINTS; ++i)
	{
		m_points[i].x = 0;
		m_points[i].y = 0;
		m_coeffitients[i] = 0;
	}
}

Polynom::~Polynom()
{

}

bool Polynom::SetPoint(double x, double y, int pos)
{
	if ((pos>=MAX_POINTS)||(pos<0))
        return false;

	m_points[pos].x = x;
	m_points[pos].y = y;
	return true;
}

Point* Polynom::GetPointArray(void)
{
    return &m_points[0];
}

double* Polynom::GetPolynomialArray(void)
{
    return &m_polynomial[0];
}

Point Polynom::GetPoint (int pos) const
{
	return m_points[pos];
}

int Polynom::GetCount() const
{
	return m_counter;
}

void Polynom::SetCount(int number)
{
    m_counter = number;
}

double Polynom::GetMaxX()
{
    double maxX;
    maxX = m_points[0].x;

    for (int i=1; i<m_counter; ++i)
    {
        if (maxX<m_points[i].x)
            maxX = m_points[i].x;
    }
    return maxX;
}

double Polynom::GetMinX()
{
    double minX;
    minX = m_points[0].x;

    for (int i=1; i<m_counter; ++i)
    {
        if (minX>m_points[i].x)
            minX = m_points[i].x;
    }
    return minX;
}

// Checks points to define if a calculation can be performed
// Returns true if the points are OK, false - if not
bool Polynom::CheckPoints()
{
    for (int i=0; i<m_counter; ++i)
    {
        for (int j=i+1; j<m_counter; ++j)
        {
            if (m_points[i].x==m_points[j].x)
                return false;
        }
    }
    return true;
}

// Calculates polynomial coefficients
void Polynom::Calculate()
{
    size_t mySize[MAX_POINTS];
    double coeff;
    Monom parts[MAX_POINTS][MAX_POINTS];
    Dinom dinom;

    // Clear sorted array and result polynomial coefficients
    for (int i=0; i<MAX_POINTS; ++i)
    {
        m_polynomial[i] = 0;
    }

    // monom filling
    for (int i=0; i<m_counter; ++i)
    {
        if (i!=0)
        {
            parts[i][0].multiplier = 1;
            parts[i][0].power = 1;
            parts[i][1].multiplier = - m_points[i].x;
            parts[i][1].power = 0;
        }
    }

    for (int i=0; i<m_counter; ++i)
    {
        // void polynomial
        parts[i][0].multiplier = 1;
        parts[i][0].power = 0;
        mySize[i] = 1;
        for (int j=0; j<m_counter; ++j)
        {
            if (j!=i)
            {
                dinom.m1.multiplier = 1;
                dinom.m1.power = 1;
                dinom.m2.multiplier = - m_points[j].x;
                dinom.m2.power = 0;
                mySize[i] = CalculateSingleMultiply(dinom, parts[i], mySize[i]);
            }
        }
        coeff = m_points[i].y;
        for (int j = 0; j<m_counter; ++j)
        {
            if (j!=i)
                coeff /= (m_points[i].x - m_points[j].x);
        }
        CalculateNumberMultiply(coeff, parts[i], mySize[i]);    // constant coefficient multiplication
    }


    for (int i=0; i<m_counter; ++i)
    {
        for (int j=0; j<mySize[i]; ++j)
        {
            m_polynomial[parts[i][j].power] += parts[i][j].multiplier;
        }
    }
}

// Multiplies dinom by a polynomial
// Returns new count of the polynomial
int Polynom::CalculateSingleMultiply(Dinom a, Monom *result, size_t n)
{
    int maxElements;
    Monom firstExpr[MAX_POINTS];    // first semi-expression
    Monom secondExpr[MAX_POINTS];   // second semi-expression
    //int counter1;                   // number of items in the first expression
    //int counter2;                   // number of items in the second expression
    maxElements = n;

    if (n<1)
        return 0;     // calculation cannot be performed

    // Find the result as a two separate expressions
    for (size_t i=0; i<n; ++i)
    {
        firstExpr[i].multiplier = a.m1.multiplier*result[i].multiplier;
        if (firstExpr[i].multiplier!=0)
            firstExpr[i].power = a.m1.power + result[i].power;
        secondExpr[i].multiplier = a.m2.multiplier*result[i].multiplier;
        if (secondExpr[i].multiplier!=0)
            secondExpr[i].power = a.m2.power + result[i].power;
    }

    // Add first expression
    for (size_t i=0; i<n; ++i)
    {
        result[i].multiplier = firstExpr[i].multiplier;
        result[i].power = firstExpr[i].power;
    }

    // Add second expression
    for (size_t i=0; i<n; ++i)
    {
        for (size_t j=0; j<n; ++j)
        {
            if (secondExpr[j].power == result[i].power)
            {
                result[i].multiplier += secondExpr[j].multiplier;
                secondExpr[j].multiplier = 0;
                break;
            }
        }
    }

    // Additional elements from second expression
    for (size_t i=0; i<n; ++i)
    {
        if (secondExpr[i].multiplier!=0)
        {
            result[maxElements].multiplier = secondExpr[i].multiplier;
            result[maxElements].power = secondExpr[i].power;
            maxElements++;
        }
    }

    // Trim array
    for (int i=0; i<maxElements; ++i)
    {
        if (result[i].multiplier==0)
        {
            for (int j=i; j<maxElements-1; ++j)
            {
                result[j] = result[j+1];
                --maxElements;
            }
        }
    }
    return maxElements;
}

// Multiplies the polynomial by a number
void Polynom::CalculateNumberMultiply(double num, Monom *result, size_t n)
{
    for (size_t i=0; i<n; ++i)
    {
        result[i].multiplier *= num;
    }
}
