/*
 * Publish json object to mqtt
 * uses libmosquitto anf libjson-c
 *
 */

#include <iostream>
#include <mosquitto.h>
#include <string.h>
#include <json-c/json.h>

using namespace std;

const char* json_string(double t, double p);

int main()
{
	int rc;
	struct mosquitto *mosq;
	const char* payload;

	cout << "Mosquitto Publisher" << endl;

	mosquitto_lib_init();

	mosq = mosquitto_new(NULL, true, NULL);

	rc = mosquitto_connect(mosq, "192.168.0.125", 1883, 60);

	if (rc != 0)
	{
		cout << "Failed to connect to broker" << endl;
		return -1;
	}

	payload = json_string(21.7, 1013.2);

	rc = mosquitto_publish(mosq, NULL, "/home/sensors", strlen(payload), payload, 0, false);

	if (rc != 0)
	{
		cout << "Failed to publish" << endl;
		return -1;
	}
	mosquitto_lib_cleanup();

	return 0;
}

// format temperature and pressure into json string
const char* json_string(double t, double p)
{
	// create json object
	json_object *jobj = json_object_new_object();

	// add temperature value
	json_object *jd = json_object_new_double(t);
	json_object_object_add(jobj, "t", jd);

	// add pressure value
	jd = json_object_new_double(p);
	json_object_object_add(jobj, "p", jd);

	// return json string
	return json_object_to_json_string(jobj);
}
