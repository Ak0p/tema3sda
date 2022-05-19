/**-- test-ab.c --  prelucreaza arbori binari cu chei intregi --*/
#include "tarb.h"

/*-- se completeaza cu definitiile functiilor implementate --*/

void RSD(TArb a)
{
	if(!a) {printf("-"); return;}
	if(!a->st && !a->dr) {printf(" %d ", a->info); return;}
	printf(" %d ", a->info);
	printf("(");
	RSD(a->st);
	printf(",");
	RSD(a->dr);
	printf(")");
}

int main ()
{
	TArb arb = NULL;
	int elem[4] = {10, 8, 15, 23}, i;

	for(i = 0; i < 4; i++)
		Inserare_ABC (&arb, elem[i]); 
	AfiArb (arb);
	printf ("noduri: %i   niveluri: %i\n", 
	NrNoduri(arb), NrNiv(arb));
	RSD(arb);

	/*-- se completeaza cu apelurile functiilor implementate --*/

	DistrArb (&arb);
	return 0;
}
