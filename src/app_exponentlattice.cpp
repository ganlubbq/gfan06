#include "parser.h"
#include "printer.h"
#include "polynomial.h"
#include "wallideal.h"
#include "termorder.h"
#include "gfanapplication.h"
#include "matrix.h"
#include "linalg.h"

class ExponentLatticeApplication : public GFanApplication
{
public:
  bool includeInDefaultInstallation()
  {
    return false;
  }
  const char *helpText()
  {
    return "This program computes a list of generators for the lattice generated by the exponent differences of monomials of the same polynomial in the input list of polynomials.\n";
  }
  ExponentLatticeApplication()
  {
    registerOptions();
  }

  const char *name()
  {
    return "_exponentlattice";
  }

  int main()
  {
    FileParser P(Stdin);

    PolynomialSet g=P.parsePolynomialSetWithRing();

    int n=g.getRing().getNumberOfVariables();
    IntegerVectorList l=exponentDifferences(g);

    FieldMatrix L=integerMatrixToFieldMatrix(rowsToIntegerMatrix(l,n),Q);
    L.reduce(false,true);
    L.removeZeroRows();
    pout<<fieldMatrixToIntegerMatrix(L).getRows();

    return 0;
  }
};

static ExponentLatticeApplication theApplication;
