/*
	Observables for C
		(c) 2020 Lucas Mendes <lucas AT lucasmendes.org>
*/

/*
	Updates:
		Wed Jun  3 13:50:36 -03 2020	-- First version
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define MYSELF	__func__

typedef struct Observable {
	struct Observable *next;
	void *ptr;
	void (*callback)(struct Observable *, int event);
} Observable;

int debugf(const char *who, const char *fmt, ...) {
	va_list args;
	char buffer[4096];
	va_start(args, fmt);
	vsnprintf(buffer, sizeof(buffer), fmt, args);
	va_end(args);
	if(!who) who = "";
	return printf("%24s - %s\n", who, buffer);
}

Observable *SendEventToObservable(Observable *observable, int event) {
	for(; observable; observable = observable->next) {
		debugf(MYSELF, "Sending event %d to callback %p", event, observable->callback);
		observable->callback(observable, event);
	}
	return NULL;
}

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

// Returned Observable * should be set as current top observable everytime RemoveObserver()
// is called, since the removed observer can be the top of observable list, the next one
// must then become the top until it's null (no more observables)
//	I.e.: ob = RemoveObservable(ob, someCallback);
Observable *RemoveObserver(Observable *observable, void (*callback)(Observable *, int)) {
	// for o in observable: if o.callback == callback then observable.Remove(o)
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

void callback4(Observable *ob, int event) {
	debugf(MYSELF, "Hey %s, from %p", (char *) ob->ptr, ob);
}

void callback3(Observable *ob, int event) {
	debugf(MYSELF, "Hey %s, from %p", (char *) ob->ptr, ob);
}

void callback2(Observable *ob, int event) {
	debugf(MYSELF, "Hey %s, from %p", (char *) ob->ptr, ob);
}

void callback(Observable *ob, int event) {
	debugf(MYSELF, "Hey %s, from %p", (char *) ob->ptr, ob);
}

int main() {
	char name[] = "Mr. Sandman";
	Observable *ob = CreateObservable(&callback, (void *) &name);
	InsertObserver(ob, &callback2);
	InsertObserver(ob, &callback3);
	InsertObserver(ob, &callback4);
	{
		Observable *o;
		for(o = ob; o; o = o->next) {
			debugf(NULL, "Observer %p has callback = %p, ptr = '%s'",
				o, o->callback, (char *) o->ptr);
		}
	}
	SendEventToObservable(ob, 777);
	debugf(NULL, "Removing [the first] observer %p before DestroyObservable()", callback);
	ob = RemoveObserver(ob, callback);
	debugf(NULL, "Removing observer %p before DestroyObservable()", callback3);
	RemoveObserver(ob, callback3);
	SendEventToObservable(ob, 555);
	DestroyObservable(ob);
	return 0;
}
