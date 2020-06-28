# I want to re-order the normal[x], orientation[y] and approach[z] to be:
# orientation[x] , approach[y] and normal[-z]

fprintf('\n\nF =');
fprintf('\n OX  AX  NX  PX');
fprintf('\n OY  AY  NY  PY');
fprintf('\n OZ  AZ  NZ  PZ');
fprintf('\n 0   0   0   1\n\n');

F_origin = [ 1 0 0 1200;
      0 1 0 1200;
      0 0 -1 0;
      0 0 0 1]
         
#when at location zero:

zero_degree_from_origin = [0;32;0;1]
absolute_point1a = F_origin  * zero_degree_from_origin

ninety_degree_from_origin = [15;0;0;1]
absolute_point2a = F_origin  * ninety_degree_from_origin

one_eighty_degree_from_origin = [0;-85;0;1]
absolute_point3a = F_origin  * one_eighty_degree_from_origin

two_seventy_degree_from_origin = [-29;0;0;1]
absolute_point4a = F_origin  * two_seventy_degree_from_origin

F_Translation = [ 1 0 0 0;
                  0 1 0 20;
                  0 0 -1 0;
                  0 0 0 1]
F_twenty_cm_forward = F_origin * F_Translation

#0 degrees: 	0	13
zero_degree_from_twenty_cm_forward = [0;13;0;1]
absolute_point1b = F_twenty_cm_forward  * zero_degree_from_twenty_cm_forward

#90 degrees: 	17	0
ninety_degree_from_twenty_cm_forward = [17;0;0;1]
absolute_point2b = F_twenty_cm_forward * ninety_degree_from_twenty_cm_forward

#180 degrees: 	0	-105
one_eighty_degree_from_twenty_cm_forward = [0;-105;0;1]
absolute_point3b = F_twenty_cm_forward  * one_eighty_degree_from_twenty_cm_forward

#270 degrees: 	-27	0
two_seventy_degree_from_twenty_cm_forward = [-27;0;0;1]
absolute_point4b = F_twenty_cm_forward * two_seventy_degree_from_twenty_cm_forward

angle = -90;
F_rotation = [ cos(angle*pi/180) -sin(angle*pi/180)   0   0;
               sin(angle*pi/180)  cos(angle*pi/180)   0   0;
               0                  0                   -1  0;
               0                  0                   0   1] ;  # this is 90 degrees clockwise from the top
               
F_rotate_and_Translate = F_origin * F_Translation * F_rotation 

#0 degrees: 	0	19
zero_rotated_and_translated = [0;19;0;1]
absolute_point2c = F_rotate_and_Translate * zero_rotated_and_translated

#90 degrees: 	104	0
ninety_rotated_and_translated = [104;0;0;1]
absolute_point3c = F_rotate_and_Translate * ninety_rotated_and_translated

#180 degrees: 	0	-26
one_eighty_rotated_and_translated = [0;-26;0;1]
absolute_point4c = F_rotate_and_Translate * one_eighty_rotated_and_translated

#270 degrees: 	-12	0
two_seventy_rotated_and_translated = [-12;0;0;1]
absolute_point1c = F_rotate_and_Translate * two_seventy_rotated_and_translated

