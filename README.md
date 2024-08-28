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
  Since fov is 2 degrees. The number of steps required to cover the entire region would be 360 / 2 => 180 steps. The sensor can run max at 250hz. The motor has 2048 steps per revolution put also take 4 seconds to complete 1 revolution. So it definetelly needs to be stepped down. If the motor is stepped down to 1:8 ratio. Then it should complete 1 revolution in 1/2 a second. Unfortunately sensor can take a maximum of 125 readings in half a second, but there are 180 reading we need to do. 

  So basically there will be 180 steps. So the tf-lunas will be set to take 180 readings per second. And the motor will be geard down to 1:8 ration. So it will take 1 second to complete. That will result in 256 steps for the motor. which should be irrelevent for operation of tf-luna . But regardless around 1 reading will be takes around 1.5 step of motor.
  
</p>

<P>
  To be done:
  Make main model
  upload prototype to github
  Enable PID control for stepper motor.
  Create the ros2 subscriber node for the esp32 publisher.
  Make full version
</P>
