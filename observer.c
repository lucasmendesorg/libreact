/*
	Observables for C
		(c) 2020 Lucas Mendes <lucas AT lucasmendes.org>
*/

/*
	Updates:
		Wed Jun  3 13:50:36 -03 2020	-- First version
*/

#include <stdlib.h>
#include <libreact.h>

Observable *RemoveObserver(Observable *observable, void (*callback)(Observable *, int)) {
	Observable *last = observable, *current;
	if(last->callback == callback) {
		if(observable->next) {
			observable = observable->next;
		} else {
			observable = NULL;
		}
		debugf(MYSELF, "Removing first observer %p w/ callback = %p. %p is now the top observer",
			last, last->callback, observable);
		FreeObservable(last);
		return observable;
	}
	for(current = last->next; current; last = current, current = current->next) {
		if(current->callback == callback) {
			debugf(MYSELF, "Removing observer %p w/ callback = %p",
				current, current->callback);
			last->next = current->next;
			FreeObservable(current);
			break;
		}
	}
	return observable;
}

Observable *InsertObserver(Observable *observable, void (*callback)(Observable *, int)) {
	if(!observable || !callback) {
		debugf(MYSELF, "*observable and *callback must be not null");
		return NULL;
	}
	Observable *aux = CreateObservable(callback, observable->ptr);
	if(!aux) {
		debugf(MYSELF, "Cannot alloc *aux");
		return aux;
	}
	aux->callback = callback;
	aux->ptr = observable->ptr;
	{
		Observable *last;
		for(last = observable; last->next; last = last->next);
		last->next = aux;
	}
	return aux;
}
