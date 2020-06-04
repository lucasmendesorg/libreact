/*
	Observables for C
		(c) 2020 Lucas Mendes <lucas AT lucasmendes.org>
*/

#ifndef LIBREACT_H
#define LIBREACT_H

#define MYSELF	__func__

typedef struct Observable {
	struct Observable *next;
	void *ptr;
	void (*callback)(struct Observable *, int event);
} Observable;

#ifdef DEBUG
int debugf(const char *who, const char *fmt, ...);
#else
#define debugf(...)
#endif

Observable *SendEventToObservable(Observable *observable, int event);

void FreeObservable(Observable *observable);
void DestroyObservable(Observable *observable);
Observable *CreateObservable(void (*callback)(Observable *, int), void *ptr);

// Returned Observable * should be set as current top observable everytime RemoveObserver()
// is called, since the removed observer can be the top of observable list, the next one
// must then become the top until it's null (no more observables)
//      I.e.: ob = RemoveObservable(ob, someCallback);
Observable *RemoveObserver(Observable *observable, void (*callback)(Observable *, int));
Observable *InsertObserver(Observable *observable, void (*callback)(Observable *, int));

#endif
