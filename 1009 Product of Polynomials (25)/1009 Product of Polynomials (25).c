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

void polynomial_multi(struct polynomial a, struct polynomial b, struct polynomial *sum);

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

void polynomial_multi(struct polynomial a, struct polynomial b, struct polynomial *rslt)
{
	int exponent;
	double coefficient;
	struct term **cur_ptr, *new, *a_ptr, *b_ptr;

	rslt->len = 0;
	rslt->terms = malloc(sizeof(struct term));

	for(a_ptr = a.terms->next; a_ptr; a_ptr = a_ptr->next) {
		for(b_ptr = b.terms->next; b_ptr; b_ptr = b_ptr->next) {
			exponent = a_ptr->exponent + b_ptr->exponent;
			coefficient = a_ptr->coefficient * b_ptr->coefficient;

			for(cur_ptr = &rslt->terms->next; *cur_ptr && (*cur_ptr)->exponent > exponent; cur_ptr = &(*cur_ptr)->next)
				;

			if(!*cur_ptr) {
				++rslt->len;

				*cur_ptr = malloc(sizeof(struct term));

				(*cur_ptr)->exponent = exponent;
				(*cur_ptr)->coefficient = coefficient;
				(*cur_ptr)->next = NULL;
			}
			else if((*cur_ptr)->exponent == exponent) {
				(*cur_ptr)->coefficient += coefficient;

				if(0.0 == (*cur_ptr)->coefficient) {
					--rslt->len;
					*cur_ptr = (*cur_ptr)->next;
				}
			}
			else {
				++rslt->len;

				new = malloc(sizeof(struct term));

				new->exponent = exponent;
				new->coefficient = coefficient;
				new->next = *cur_ptr;
				*cur_ptr = new;
			};
		}
	}
}

int main()
{
	struct polynomial a, b, sum;

	polynomial_create(&a);
	polynomial_create(&b);

	polynomial_multi(a, b, &sum);

	polynomial_print(sum);

	return 0;
}
