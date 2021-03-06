#include  <iostream>
#include "parser.h"
#include "printer.h"
#include "polynomial.h"
#include "buchberger.h"
#include "wallideal.h"
#include "termorder.h"
#include "gfanapplication.h"
#include "tropical2.h"
#include "log.h"

using namespace std;

class InitialFormsApplication : public GFanApplication
{
  SimpleOption optionIdeal;
  SimpleOption optionPair;
  SimpleOption optionMark;
  SimpleOption optionList;
public:
  const char *helpText()
  {
    return "This program converts a list of polynomials to a list of their initial forms with respect to the vector given after the list.\n";
  }
  InitialFormsApplication():
    optionIdeal("--ideal","Treat input as an ideal. This will make the program compute the initial ideal of the ideal generated by the input polynomials. The computation is done by computing a Groebner basis with respect to the given vector. The vector must be positive or the input polynomials must be homogeneous in a positive grading. None of these conditions are checked by the program.\n"),
    optionPair("--pair","Produce a pair of polynomial lists. Used together with --ideal this option will also write a compatible reduced Groebner basis for the input ideal to the output. This is useful for finding the Groebner cone of a non-monomial initial ideal.\n"),
    optionMark("--mark","If the --pair option is and the --ideal option is not used this option will still make sure that the second output basis is marked consistently with the vector."),
    optionList("--list","Read in a list of vectors instead of a single vector and produce a list of polynomial sets as output.")
  {
    registerOptions();
  }

  const char *name()
  {
    return "_initialforms";
  }

  int main()
  {
    FileParser P(Stdin);

    PolynomialSet g=P.parsePolynomialSetWithRing();

    IntegerVectorList wList;
    if(optionList.getValue())
    	wList=P.parseIntegerVectorList();
    else
    	wList.push_back(P.parseIntegerVector());

    for(IntegerVectorList::const_iterator i=wList.begin();i!=wList.end();i++)
    {
		log1 cerr<<"-\n";
    	assert(i->size()==g.getRing().getNumberOfVariables());

    	if(optionMark.getValue())
    	{
    		WeightReverseLexicographicTermOrder T(*i);
    		g.markAndScale(T);
    	}
    	if(optionIdeal.getValue())
    	{
    		WeightReverseLexicographicTermOrder T(*i);
    		buchberger(&g,T);
    	}

    	pout<<g.getRing()<<"\n"<<initialForms(g,*i);
    	if(optionPair.getValue())
    	{
    		pout<<"\n"<<g;
    	}
    }
    return 0;
  }
};

static InitialFormsApplication theApplication;
