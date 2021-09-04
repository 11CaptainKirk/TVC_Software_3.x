# TVC Software 3.x

> Avionics Software for Entropy Rocket

***ROBERT J. KIRK  ~  Sept. 4, 2021***
 

**File Structure:**
<pre>
main.cpp
    L state_machine.hpp
        L write_data.hpp
            L csv_format.hpp
        L update_gimbal.hpp
            L pid_compute.hpp
        L status_indicate.hpp
    L read_sensors.hpp
        L quaternion_conversion.hpp
    L csv_static.hpp
    L sensor_init.hpp
    L sensors.h
    L sensor_data_object.h    
</pre>

**About Files:**

File Name | Description
----------|-----------
main.cpp:                  | Operational File with Setup() and Loop() functions
state_machine.hpp:         | File with switch to change actions based on state
read_sensors.hpp:          | Read Sensor data and write to sensor data object 
csv_static.hpp:            | Data to be written on startup
sensor_init.hpp:           | Initialize Sensors
sensors.h                  | Create Sensor Objects
sensor_data_object.h:      | Create Sensor Data Class & Helper Functions
quaternion_conversion.hpp: | Convert raw Quaternions to Corrected Euler Angles
write_data.hpp:            | Write data from Sensor Data Object to SD Card
csv_format.hpp:            | Format Sensor Data as CSV & return to write_data
update_gimbal.hpp:         | Update Servo Gimbal Angle with PID output
pid_compute.hpp            | Compute Gimbal Angle
status_indicate.hpp:       | Indicate System Status (Piezo & LED)


**TODO**
- [ ] Plan Framework
- [ ] Integrate Existing Code
- [ ] Add Data Class
