//main
//TODO IFNDEF thing

typedef struct {
	unsigned int dht22_delay;
	unsigned int light_sensor_delay;
	unsigned int soil_sensor_delay;
	unsigned int light_on_time;
	unsigned int light_on_duration;
	unsigned int exhaust_delay;
	unsigned int exhaust_duration;
	unsigned int circulation_delay;
	unsigned int circulation_duration;
	unsigned int increment_size; //TODO possibly change this to be compile-time constant
	const char *influx_url; //TODO memory size for this
	const char *influx_db;
	const char *influx_auth;
} configuration;

typedef struct {
	unsigned int temperature:12; //maybe in kelvin, and x10 (eg 37 deg celsius == 3071)
	unsigned int humidity:8;
	unsigned int light_level:12;
	unsigned int soil_moisture:12;
	unsigned int light_on:1; //TODO maybe use stdbool.h or _Bool instead of bitfield
	unsigned int view_light_on:1;
	unsigned int exhaust_on:1;
	unsigned int fan_on:1;
	unsigned int measured:1;
} properties; //this bitfeild is 49 bits, ie not optimized


//timer functions
int open_timer(int);
int attach_handler(void);
void timer_handler(int);
int get_irl_time(void);

static int ini_handler_func(void *, const char *, const char *, const char *);

//reading sensor functions
int read_dht22(void);
int read_light(void);
int read_soil_moist(void);

//posting data and influxDB functions
int post_data(const properties *);


#define FULL_HOUR ((int)(60/settings.increment_size))
#define FULL_DAY (24*FULL_HOUR)
#define FULL_INC (settings.increment_size)


configuration settings;
properties conditions;
