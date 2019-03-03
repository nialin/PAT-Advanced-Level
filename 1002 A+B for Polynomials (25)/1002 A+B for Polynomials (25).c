#include <stdio.h>
#include <stdlib.h>


struct term {
	int exponent;
	double coefficient;
	struct term *next;
};

struct polynomial {
	int len;
	struct term *terms;
};


void polynomial_create(struct polynomial *poly);
void polynomial_print(struct polynomial poly);

void polynomial_add(struct polynomial a, struct polynomial b, struct polynomial *sum);

void polynomial_create(struct polynomial *poly)
{
	int i;
	struct term **cur_ptr;

	scanf("%d", &poly->len);

	poly->terms = malloc(sizeof(struct term));
	cur_ptr = &poly->terms->next;

	for(i = 0; i < poly->len; ++i) {
		*cur_ptr = malloc(sizeof(struct term));

		scanf("%d%lf", &(*cur_ptr)->exponent, &(*cur_ptr)->coefficient);
		cur_ptr = &(*cur_ptr)->next;
	}

	*cur_ptr = NULL;
}

void polynomial_print(struct polynomial poly)
{
	printf("%d", poly.len);

	for(poly.terms = poly.terms->next; poly.terms; poly.terms = poly.terms->next)
		printf(" %d %.1f", poly.terms->exponent, poly.terms->coefficient);

	printf("\n");
}

void polynomial_add(struct polynomial a, struct polynomial b, struct polynomial *sum)
{
	struct term **cur_ptr;

	sum->len = 0;
	sum->terms = malloc(sizeof(struct term));
	cur_ptr = &sum->terms->next;

	for(a.terms = a.terms->next, b.terms = b.terms->next; a.terms && b.terms; ) {
		*cur_ptr = malloc(sizeof(struct term));

		if(a.terms->exponent == b.terms->exponent) {
			(*cur_ptr)->exponent = a.terms->exponent;
			(*cur_ptr)->coefficient = a.terms->coefficient + b.terms->coefficient;

			a.terms = a.terms->next;
			b.terms = b.terms->next;

			if(0.0l == (*cur_ptr)->coefficient) {
				free(*cur_ptr);
				continue;
			}
		}
		else if(a.terms->exponent > b.terms->exponent) {
			(*cur_ptr)->exponent = a.terms->exponent;
			(*cur_ptr)->coefficient = a.terms->coefficient;

			a.terms = a.terms->next;
		}
		else {
			(*cur_ptr)->exponent = b.terms->exponent;
			(*cur_ptr)->coefficient = b.terms->coefficient;

			b.terms = b.terms->next;
		}

		++sum->len;
		cur_ptr = &(*cur_ptr)->next;
	}

	while(a.terms) {
		*cur_ptr = malloc(sizeof(struct term));

		(*cur_ptr)->exponent = a.terms->exponent;
		(*cur_ptr)->coefficient = a.terms->coefficient;

		a.terms = a.terms->next;

		++sum->len;
		cur_ptr = &(*cur_ptr)->next;
	}

	while(b.terms) {
		*cur_ptr = malloc(sizeof(struct term));

		(*cur_ptr)->exponent = b.terms->exponent;
		(*cur_ptr)->coefficient = b.terms->coefficient;

		b.terms = b.terms->next;

		++sum->len;
		cur_ptr = &(*cur_ptr)->next;
	}

	*cur_ptr = NULL;
}

int main()
{
	struct polynomial a, b, sum;

	polynomial_create(&a);
	polynomial_create(&b);

	polynomial_add(a, b, &sum);

	polynomial_print(sum);

	return 0;
}
