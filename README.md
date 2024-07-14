# DiyLidar

The project uses a point lidar, stepper motor in closed loop to achieve similar functioning as a 2D lidar, with enough accuracy to run SLAM. A ROS package will be created for the lidar. 

## Basic Component Info
<p>
Using simple 28BYJ-48 stepper motor, with ULN 2003 driver. At full steps the motor will achieve 2048 stpes per revelution, which takes ~4secs
If ran at a 2:1 ratio. The torque should slighly decrease, but still should be able to spin the light weight tf-luna(5g) but decrease steps per revolution to 1024 and take around 2 secs to complete 1 revolution.
That is 360 / 1024 = ~0.25 degrees per step. 
It takes ~2 secs per revolution. 
</p>

<p>
  Using tf-luna which has a range of 8m and fov of 2 degrees. Hence length of arc will be 0.27m(at 8m). Considering most reading should lower than 8m this should be fine. Range caps can also be set to counter this.
  
</p>
