lc = 1;
lc2 = 0.5; // for the pegs

Point(77)={17.7000,0,0,lc};
Point(78)={17.5325,0.8419,0,lc};
Point(79)={17.0556,1.5556,0,lc};
Point(80)={16.3419,2.0325,0,lc};
Point(81)={15.5000,2.2000,0,lc};
Point(82)={14.6581,2.0325,0,lc};
Point(83)={13.9444,1.5556,0,lc};
Point(84)={13.4675,0.8419,0,lc};
Point(85)={13.3000,0.0000,0,lc};
Point(86)={13.4675,-0.8419,0,lc};
Point(87)={13.9444,-1.5556,0,lc};
Point(88)={14.6581,-2.0325,0,lc};
Point(89)={15.5000,-2.2000,0,lc};
Point(90)={16.3419,-2.0325,0,lc};
Point(91)={17.0556,-1.5556,0,lc};
Point(92)={17.5325,-0.8419,0,lc};
CatmullRom(30) = {85,84,83,82,81,80,79,78,77};
CatmullRom(31) = {85,86,87,88,89,90,91,92,77};

Point(97)={46.9,1.5,-.7814,lc2};
Point(98)={46.7536,1.8536,-.756,lc2};
Point(99)={46.4,2,-.6946,lc2};
Point(100)={46.0464,1.8536,-.6332,lc2};
Point(101)={45.9,1.5,-.6078,lc2};
Point(102)={46.0464,1.1464,-.6332,lc2};
Point(103)={46.4,1,-.6946,lc2};
Point(104)={46.7536,1.1464,-.756,lc2};
Point(105)={46.9,-1.5,-.7814,lc2};
Point(106)={46.7536,-1.8536,-.756,lc2};
Point(107)={46.4,-2,-.6946,lc2};
Point(108)={46.0464,-1.8536,-.6332,lc2};
Point(109)={45.9,-1.5,-.6078,lc2};
Point(110)={46.0464,-1.1464,-.6332,lc2};
Point(111)={46.4,-1,-.6946,lc2};
Point(112)={46.7536,-1.1464,-.756,lc2};
Point(113)={51.1,-1.5,-1.5107,lc2};
Point(114)={50.9536,-1.8536,-1.4853,lc2};
Point(115)={50.6,-2,-1.4239,lc2};
Point(116)={50.2464,-1.8536,-1.3625,lc2};
Point(117)={50.1,-1.5,-1.3371,lc2};
Point(118)={50.2464,-1.1464,-1.3625,lc2};
Point(119)={50.6,-1,-1.4239,lc2};
Point(120)={50.9536,-1.1464,-1.4853,lc2};
Point(121)={51.1,1.5,-1.5107,lc2};
Point(122)={50.9536,1.8536,-1.4853,lc2};
Point(123)={50.6,2,-1.4239,lc2};
Point(124)={50.2464,1.8536,-1.3625,lc2};
Point(125)={50.1,1.5,-1.3371,lc2};
Point(126)={50.2464,1.1464,-1.3625,lc2};
Point(127)={50.6,1,-1.4239,lc2};
Point(128)={50.9536,1.1464,-1.4853,lc2};
CatmullRom(38) = {101,100,99,98,97};
CatmullRom(39) = {101,102,103,104,97};
CatmullRom(40) = {125,124,123,122,121};
CatmullRom(41) = {125,126,127,128,121};
CatmullRom(42) = {109,110,111,112,105};
CatmullRom(43) = {109,108,107,106,105};
CatmullRom(44) = {117,118,119,120,113};
CatmullRom(45) = {117,116,115,114,113};

Line Loop(46) = {-31,30};
Plane Surface(47) = {46};
Line Loop(48) = {-38,39};
Plane Surface(49) = {48};
Line Loop(50) = {-43,42};
Plane Surface(51) = {50};
Line Loop(52) = {-40,41};
Plane Surface(53) = {52};
Line Loop(54) = {-45,44};
Plane Surface(55) = {54};

// extruding this makes Gmsh go nuts
Extrude Surface {51, {0,0,3}};
