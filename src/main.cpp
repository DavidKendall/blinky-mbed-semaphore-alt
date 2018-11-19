#include <mbed.h>

enum{ON,OFF}; /* a hack to invert bit logic for common anode LED */

Semaphore flag(1);

void flash_red(DigitalOut *led)
{
	wait_ms( rand()%1000 );
	while(true) {
		flag.wait();
		*led = ON;
		wait_ms( rand()%1000 );
		flag.release();
		*led = OFF;
		wait_ms( rand()%1000 );
	}
}

int main(void)
{
	DigitalOut   red(LED1,OFF);
	DigitalOut green(LED2,OFF);
	DigitalOut  blue(LED3,OFF);

	DigitalOut   red1(D5,OFF);
	DigitalOut green1(D8,OFF);
	DigitalOut  blue1(D9,OFF);

	Thread p,q,r;
	Thread p1,q1,r1;

	r.start( callback(flash_red, &red) );
	p.start( callback(flash_red, &green) );
	q.start( callback(flash_red, &blue) );

	r1.start( callback(flash_red, &red1) );
	p1.start( callback(flash_red, &green1) );
	q1.start( callback(flash_red, &blue1) );

	r.join();	
}

