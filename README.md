# MovingJpegs_Samsung
This is a tool to split a Samsung "moving" image into a jpeg image and a mp4 movie

Sun Feb  5 23:21:12 CST 2023
This is a cheap hack, it will take one option of a filename of the file to split
apart.  The original file should not be altered, it will create output.jpg and output.mp4.

Updated code to look if output.jpg and output.mp4 file exists before opening for output.

I found this repo useful.
  A repo for Windows application to strip the jpeg and the mp4 apart.
  https://github.com/joemck/ExtractMotionPhotos

   const unsigned char MotionPhoto_Data_Marker[] = {
    0x4D, 0x6F, 0x74, 0x69, 0x6F, 0x6E, 0x50, 0x68,
    0x6F, 0x74, 0x6F, 0x5F, 0x44, 0x61, 0x74, 0x61 };

// Copyright (C) 2023, Brian Dolan-Goecke 20230205 

