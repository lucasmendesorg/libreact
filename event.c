/*
	Observables for C
		(c) 2020 Lucas Mendes <lucas AT lucasmendes.org>
*/

#include <libreact.h>

Observable *SendEventToObservable(Observable *observable, int event) {
	for(; observable; observable = observable->next) {
		debugf(MYSELF, "Sending event %d to callback %p", event, observable->callback);
		observable->callback(observable, event);
	}
	return observable;
}
