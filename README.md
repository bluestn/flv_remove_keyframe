# flv_remove_keyframe
only for test use, to remove key frames from flv video file, and only left the first keyframe & sps/pps frames in the new generated video file.

support linux centos/ubuntu environment.

HOW TO COMPILE:

   cd build
   cmake ..
   make
   
   
HOW TO USE:
   type the following command in shell window:
   
   flv_remove_keyframe {old_flv_video_file_name}.flv
   
   and then you will got the new video with the new name {old_flv_video_file_name}_no_keyframe.flv
    
 
