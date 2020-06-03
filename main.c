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
