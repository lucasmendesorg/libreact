/*
	Observables for C
		(c) 2020 Lucas Mendes <lucas AT lucasmendes.org>
*/

#include <stdlib.h>
#include <libreact.h>

void FreeObservable(Observable *observable) {
	free(observable);
}

void DestroyObservable(Observable *observable) {
	if(observable->next) {
		DestroyObservable(observable->next);
	}
	debugf(MYSELF, "Freeing %p", observable);
	FreeObservable(observable);
}

Observable *CreateObservable(void (*callback)(Observable *, int), void *ptr) {
	Observable *aux = (Observable *) malloc(sizeof(*aux));
	if(!aux) {
		debugf(MYSELF, "Cannot alloc *aux");
		return aux;
	}
	aux->callback = callback;
	aux->ptr = ptr;
	return aux;
}
