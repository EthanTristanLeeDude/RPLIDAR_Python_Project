# RPLIDAR_Python_Project
This code demonstrates how to interface with the RPLIDAR A1M8 from Slamtec using Python. 

RPLIDAR_stream.py does the following:

1. Uses the serial, struct and serial libraries.
2. Uses hex encoded strings to send commands to the RPLIDAR unit (start_scan is the only one being used initially).
3. Performs a comport scan to list all the available com ports.
4. Currently hard coded to connect to COM7 at 115200 BAUD. 
5. Clears the DTR bit. The motor won't turn if the DTR bit is set.
6. Sends the start scan command to the RPLIDAR unit, and prints out the acknowledge response. <a href = https://github.com/EthanTristanLeeDude/RPLIDAR_Python_Project/blob/master/LR001_SLAMTEC_rplidar_protocol_v2.1_en.pdf> more info</a>
7. Parses the data stream from the LIDAR unit.
8. Periodically outputs the LIDAR scan distance, in mm, for 8 discrete angles in degrees (0, 45, 90, 135, 180, 225, 270, 315).
9. If any of the scan angles were invalid, it will output zero for that case.

RPLIDAR_static_map.py builds more functionality on top of RPLIDAR_stream.py: 

1. Generates a static map of its surroundings. 
2. The image is 2400 pixels x 2400 pixels with a resolution of 1 cm^2 per pixel, and an angular resolution of 5 degrees.  
3. The top of the image is the 0 degree direction.
4. See "Sample Static Map Image.jpg" for one example of what the output looks like.


I purchased the LIDAR unit from here: <a href = https://www.robotshop.com/en/rplidar-a1m8-360-degree-laser-scanner-development-kit.html>RPLidar A1M8 - 360 Degree Laser Scanner Development Kit</a>.
