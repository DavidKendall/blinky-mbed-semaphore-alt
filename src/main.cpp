#include <mbed.h>

enum{ON,OFF}; /* a hack to invert bit logic for common anode LED */

Semaphore flag(0);

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
	Thread p,q,r;

	r.start( callback(flash_red, &red) );
	p.start( callback(flash_red, &green) );
	q.start( callback(flash_red, &blue) );

	r.join();	
}

