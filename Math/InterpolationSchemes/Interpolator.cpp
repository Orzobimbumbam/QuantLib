//
// Created by Alberto Campi on 11/11/2018.
//

#include "Interpolator.h"

/*
math::CSCoeffs& math::CSCoeffs::operator=(const math::CSCoeffs &rhsCSCoeffs)
{
    a = rhsCSCoeffs.a;
    b = rhsCSCoeffs.b;
    c = rhsCSCoeffs.c;
    d = rhsCSCoeffs.d;

    return *this;
}*/

math::CSCoeffs::CSCoeffs(double aConst, double bLin, double cQuad, double dCub) : a(aConst), b(bLin), c(cQuad), d(dCub) {}

bool math::CSCoeffs::operator==(const math::CSCoeffs &rhsCSCoeffs)
{
    return a == rhsCSCoeffs.a && b == rhsCSCoeffs.b && c == rhsCSCoeffs.c && d == rhsCSCoeffs.d;
}

bool math::CSCoeffs::operator!=(const math::CSCoeffs &rhsCSCoeffs)
{
    return !(*this == rhsCSCoeffs);
}