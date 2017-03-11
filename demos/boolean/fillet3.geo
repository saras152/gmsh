SetFactory("OpenCASCADE");

w = DefineNumber[0.2, Min 0.01, Max 0.35, Step 0.01, Name "width"];
dx_out = 1.; dy_out = 0.3; dz_out = 1.;
dx_in = dx_out-2*w; dy_in = dy_out; dz_in = dz_out-2*w;
r_in = 0.1; r_out = r_in+w;

v_out = newv;
Block(v_out) = {
  -dx_out/2,-dy_out/2,-dz_out/2,
   dx_out/2, dy_out/2, dz_out/2
};
v_ = v_out;
f_[] = Abs(Boundary{ Volume{v_}; });
e_[] = Unique( Abs(Boundary{ Surface{f_[]}; }) );
v_out = Fillet{v_}{e_[2-1], e_[4-1], e_[6-1], e_[8-1]}{r_out};
Recursive Delete{ Volume{v_}; }

v_in = newv;
Block(v_in) = {
  -dx_in/2,-dy_in/2,-dz_in/2,
   dx_in/2, dy_in/2, dz_in/2
};
v_ = v_in;
f_[] = Abs(Boundary{ Volume{v_}; });
e_[] = Unique( Abs(Boundary{ Surface{f_[]}; }) );
v_in = Fillet{v_}{e_[2-1], e_[4-1], e_[6-1], e_[8-1]}{r_in};
Recursive Delete{ Volume{v_}; }

BooleanDifference { Volume{v_out}; Delete; }{ Volume{v_in}; Delete; }
