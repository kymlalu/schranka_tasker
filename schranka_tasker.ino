// define max number of tasks to save precious Arduino RAM
#define TASKER_MAX_TASKS 4
#include "Tasker.h"

#define plnoSvit 1        //bylo 3
#define plnoBlik 3      //bylo 1
#define prazdnaSvit 4
#define cidloObsah 0    
#define sirenka 2

unsigned int blikaniCas = 650;		//cas je v ms
unsigned int houkaniCas = 60000;

int stavCidla = 0;
boolean blikBezi = false;
boolean houkaniBezi = false;
int predchoziStav = -1;           //ulozeni predchoziho stavu cidla

Tasker tasker (false);



void blikani (int pin) {
	if ( !blikBezi )return;
	digitalWrite (pin, !digitalRead (pin));
	}

void houkaniStavPinu (int pin) {
	digitalWrite (pin, !digitalRead (pin));
	}

void houkani (int pin) {
	if ( !houkaniBezi ) return;					//povoleni/zakazani fuknce
	tasker.setRepeated (houkaniStavPinu, 200, 6, pin);		// 6=3xpisk 200ms	
	}
	



void vyhodnoceniCidla (int) {             //zavolame v setup jako set.Interval
	stavCidla = digitalRead (cidloObsah);

	if ( stavCidla != predchoziStav ) {
		predchoziStav = stavCidla;    //ulozeni aktualniho stavu cidla do historie

		if ( stavCidla == 0 ) {

			blikBezi = true;                //povoleni blikani
			houkaniBezi = true;				//povolime houkani
			digitalWrite (prazdnaSvit, LOW);
			digitalWrite (plnoSvit, HIGH);
			}
		else {

			blikBezi = false;               //vypneme blikani
			houkaniBezi = false;			//vypneme houkani	
			digitalWrite (prazdnaSvit, HIGH);
			digitalWrite (plnoBlik, LOW);
			digitalWrite (plnoSvit, LOW);
			digitalWrite (sirenka, LOW);
			}
		}

	}


void setup ( ) {
	pinMode (prazdnaSvit, OUTPUT);  //prazdno
	pinMode (plnoSvit, OUTPUT); // sviti plno
	pinMode (plnoBlik, OUTPUT); // blikani plno
	pinMode (sirenka, OUTPUT); // sirenka 
	pinMode (cidloObsah, INPUT); // optozavora



	tasker.setInterval (vyhodnoceniCidla, 1000);
	tasker.setInterval (blikani, blikaniCas, plnoBlik);
	tasker.setInterval (houkani, houkaniCas, sirenka);
	

	tasker.run ( );
	}

void loop ( ) {
	}