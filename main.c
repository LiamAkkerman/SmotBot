/*
main.c
SmotBot garden control unit
*/

#include <stdio.h>
#include <time.h> 
#include <unistd.h>
#include "main.h"


//TODO move these to sperate file of settings
//define delays between the sensor readings, in seconds
const int dht22_delay = 300;
const int light_sensor_delay = 300;
const int soil_sensor_delay = 1200;




int main(int argc, char *argv[]) {
	//TODO you know, the code

}

//TODO change to accept prevous itimerval struct as argument
int open_timer(int delay_number) {
	struct itimerval timer;
	
	/* Configure the timer to expire after some seconds... */
	timer.it_value.tv_sec = delay_number;
	timer.it_value.tv_usec = 0;
	timer.it_interval.tv_sec = delay_number;
	timer.it_interval.tv_usec = 0;
	
	/* Start a virtual timer. It counts down whenever this process is executing. */
	if(setitimer(ITIMER_VIRTUAL, &timer, NULL) != 0) {
		printf("ERROR: opening timer failed\n");
		return -1; //TODO I'd rather have only one final return
	}
	
	return 0;
}

//TODO change to accept prevous sigaction struct as argument
int attach_handler(void) {
	//assigns an action to occur when timer expires
	struct sigaction sa;
	memset(&sa, 0, sizeof(sa)); //I don't actaully know what this does, but it's supposed to be used
	
	//calls the referanced function
	sa.sa_handler = &timer_handler;
	if(sigaction(SIGVTALRM, &sa, NULL) != 0) { 
		printf("ERROR: handler failed\n");
		return -1; //TODO I'd rather have only one final return
	}
	
	return 0;
}

int timer_handler(int signum) {
	static int count = 0;
	count = count + 1;
	int result = 0;
	
	//if the current incriment count is a prechosen time, preform approriate action
	//TODO make more dynamic, scaling without needed to rewrite
	if(count == dht22_delay) {
		if(read_dht22() != 0) {
			printf("ERROR: DHT22 reading failed\n");
			result = -1;
		}
	}
	else if(count == light_sensor_delay) {
		if(read_light() != 0) {
			printf("ERROR: light reading failed\n");
			result = -1;
		}
	}
	else if(count == soil_sensor_delay) {
		if(read_soil_moist() != 0) {
			printf("ERROR: soil moisture reading failed\n");
			result = -1;
		}
	}
	
	
	return result;
}

//reading sensor functions
int read_dht22(void) {
	
	return 0;
}
int read_light(void) {
	
	return 0;
}
int read_soil_moist(void) {
	
	return 0;
}

//posting data and influxDB function
int post_data(void) {
	
	return 0;
}
