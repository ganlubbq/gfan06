#include "parser.h"
#include "printer.h"
#include "saturation.h"
#include "gfanapplication.h"
#include "lp.h"

class IdealIntersectionApplication : public GFanApplication
{
  FieldOption theFieldOption;
public:
  bool includeInDefaultInstallation()
  {
    return false;
  }
  const char *helpText()
  {
    return "This program computes the intersection of two ideals generated by sets of polynomials given in the input.\n";
  }
  IdealIntersectionApplication()
  {
    registerOptions();
  }

  const char *name()
  {
    return "_idealintersection";
  }

  int main()
  {
    FileParser P(Stdin);

    PolynomialRing theRing=P.parsePolynomialRing();
    PolynomialSet a=P.parsePolynomialSet(theRing);
    PolynomialSet b=P.parsePolynomialSet(theRing);

    pout<<theRing<<idealIntersection(a,b);

    return 0;
  }
};

static IdealIntersectionApplication theApplication;
