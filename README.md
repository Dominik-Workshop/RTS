# Linefollower


## Used tools:
<img align="center" height="64" src="images/logos/Eagle.png"> &nbsp;
<img align="center"  height="64" src="images/logos/Fusion-360.png"> &nbsp;
<img align="center" height="64" src="images/logos/Platformio_vscode.png"> &nbsp;
<img align="center" height="64" src="images/logos/MIT_app_inventor.png">


## Project overwiev

The Linefollower Robot is designed to autonomously navigate a track marked by a black line on a white surface. The goal is for the robot to complete the track as quickly as possible.
<img align="center" src="images/pictures/LF.jpg">

## Electronics

The robot incorporates 2 PCBs, which are connected via an FFC cable:
  - sensor board - contains 16 reflective sensors for line detection
  <img align="center" src="images/renders/LF_front_PCB_top.png">
  <img align="center" src="images/renders/LF_front_PCB_bottom.png">
  - main board 
  <img align="center" src="images/renders/LF_mainboard_PCB_top.png">
  <img align="center" src="images/renders/LF_mainboard_PCB_bottom.png">

## Mechanical construction

The PCBs are mechanically joined with a lightweight 3D-printed connection bar. The motor and battery mounts are also 3D-printed.

### Tires

Several tire types have been tested:
- MINI-Z Low Height Slick Tire 40° MZW39-40
- MINI-Z LM Wide High Grip Tire 20° MZT302-20

## Android app
<p align="center">
  <img align="center" width=40% src="images/screenshots/Android_app_initial.jpg"> &nbsp;&nbsp;
  <img align="center" width=40% src="images/screenshots/Android_app_set.jpg">
</p>

## Uploading the code to the robot

If the microcontroller doesn't programm:
<details>
<summary>Click to view solution</summary>
Make sure that the fusebits are set as bellow:
<img src="images/screenshots/atmega_fuses.png" alt="Fuse Bits Settings">
</details>
