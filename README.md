# Restoration of motion blur images
This project is inspired by Chapter 5 in "Digital Image Processing 3th edition", the first time I finish reading this chapter I feel like motion deblur is an amazing technich that I should definitely implement it, and is actually the case since I found this help a lot for the need to identify license plate of a fast moving car, since the restoration process is completely explainable this would also help in political usages.


<p align="center">
   <br>
   <img src="Images/1_Demonstration.jpg" width="70%" height="70%">
   <br>
</p>

# User interface
Here we have a user interface to perform motion deblur by the following steps:

**Step 1.** Load image <br>
To click on "File->Open" to load image (.jpg/.bmp/.png/.tif)

<p align="center">
   <br>
   <img src="Images/2_User_interface.jpg" width="70%" height="70%">
   <br>
</p>

**Step 2.** Specify motion direction and region of interest <br>
In this stage, we need to specify both the direction of motion and the region of interest to be proecssed <br>
(1) To click on "Edit->Parameter setting->from graph", and draw a line representing motion direction from graph <br>
(2) To click on "Edit->ROI", and select region of interest from graph (This action was to facilitate processing speed) <br>

<p align="center">
   <br>
   <img src="Images/2_User_interface_ROI_and_Motion_direction.jpg" width="70%" height="70%">
   <br>
</p>

**Step 3.** Parameter adjustment and Result <br>
In the previous we've finished specifying motion direction, and this step is for fine adjustment of motion direction and the parameters affecting the restoration process, for readers interested in details of algorithm please go through the next chapter.

<p align="center">
   <br>
   <img src="Images/3_Parameter_adjustment_and_Result_.jpg" width="70%" height="70%">
   <br>
</p>

# Implementation
To illustrate the concept of motion deblur, we will go through how the image is generated for static and motion objects. <br>
<br>
**Image acquisition of static object** <br>
Let's imagine we have a cell phone ready to take a photo shown in the right side of the graph, and both the scene and the phone are static which means for each pixels of the camera sensor would constantly look at the same spot of the scene during the entire exposure process, and the formulation for the imaging process is:

<p align="center">
   <br>
   <img src="Images/4_Formula_static_object.jpg" width="70%" height="70%">
   <br>
</p>

**Image acquisition of motion object** <br>
In this case, let's suppose either the scene or the phone are going planar motion during the imaging process, each pixels of the camera would integrate through the scene along the trajectory of motion during the exposure process illustrated in the following figure: 

<p align="center">
   <br>
   <img src="Images/4_Formula_motion_object.jpg" width="70%" height="70%">
   <br>
</p>

**Fourier transform** <br>
Now things going intriguing if we transform the formula of motion imaging into frequency domain, the shifting term in side the expression has become multiplication term outside the function:

<p align="center">
   <br>
   <img src="Images/5.jpg" width="70%" height="70%">
   <br>
</p>

<p align="center">
   <br>
   <img src="Images/6_.jpg" width="70%" height="70%">
   <br>
</p>

And here let's finish the integration and using euler's formula to simply the expression:

<p align="center">
   <br>
   <img src="Images/7.jpg" width="70%" height="70%">
   <br>
</p>

<p align="center">
   <br>
   <img src="Images/8.jpg" width="70%" height="70%">
   <br>
</p>

We find that in frequency domain, the motion blur image is actually composition of the mulitplication of static image and a filter representing motion blur:

<p align="center">
   <br>
   <img src="Images/9.jpg" width="70%" height="70%">
   <br>
</p>

Here let's specify a notation to the term of motion blur for notational simplicity, in a ideal situation the static image could be recovered by the division of motion blur image to the motion blur filter:

<p align="center">
   <br>
   <img src="Images/10.jpg" width="70%" height="70%">
   <br>
</p>

<p align="center">
   <br>
   <img src="Images/11.jpg" width="70%" height="70%">
   <br>
</p>

In practice we need to account for the additive noise during the imaging process, and wiener filter is designed for the situation that seeks to find minimum mean squared error between the restoration image and the actual image:

<p align="center">
   <br>
   <img src="Images/12.jpg" width="70%" height="70%">
   <br>
</p>

<p align="center">
   <br>
   <img src="Images/13.jpg" width="70%" height="70%">
   <br>
</p>
