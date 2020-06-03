# RPLIDAR_Python_Project
This code demonstrates how to interface with the RPLIDAR A1M8 from Slamtec using Python. The initial version of the code does the following:

1. Uses the serial, struct and serial libraries 
2. Uses hex encoded strings to send commands to the RPLIDAR unit (start_scan is the only one being used initially)
3. Performs a comport scan to list all the available com ports
4. Hard coded to connect to COM7 at 115200 BAUD. 
5. Clears the DTR bit - this is important for the RPLIDAR unit, cause with the DTR bit set, the motor won't turn
6. Sends the start scan command tot he RPLIDAR unit, and prints out the acknowledge response.
   (see the attached LR001_SLAMTEC_rplidar_protocol_v2.1_en.pdf for more explanation). 
7. Parses the data stream from the LIDAR unit.
8. Periodically outputs the LIDAR scan distance, in mm, for 8 discrete angles ( 0, 45, 90, 135, 180, 225, 270, 315) [deg]
9. If any of the scan angles were invalid, it will output zero for that case

I purchased the the LIDAR unit from here:  <a href = https://www.robotshop.com/en/rplidar-a1m8-360-degree-laser-scanner-development-kit.html>RPLidar A1M8 - 360 Degree Laser Scanner Development Kit</a>.
