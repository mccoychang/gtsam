% automatically generated by wrap on 2011-Oct-31
echo on

toolboxpath = pwd
addpath(toolboxpath);

%% Point2
cd(toolboxpath)
mex -O5 new_Point2_.cpp
mex -O5 new_Point2_dd.cpp

cd @Point2
mex -O5 x.cpp
mex -O5 y.cpp
mex -O5 dim.cpp

%% Point3
cd(toolboxpath)
mex -O5 new_Point3_ddd.cpp

cd @Point3
mex -O5 norm.cpp

%% Test
cd(toolboxpath)
mex -O5 new_Test_.cpp

cd @Test
mex -O5 return_bool.cpp
mex -O5 return_size_t.cpp
mex -O5 return_int.cpp
mex -O5 return_double.cpp
mex -O5 return_string.cpp
mex -O5 return_vector1.cpp
mex -O5 return_matrix1.cpp
mex -O5 return_vector2.cpp
mex -O5 return_matrix2.cpp
mex -O5 return_pair.cpp
mex -O5 return_field.cpp
mex -O5 return_TestPtr.cpp
mex -O5 create_ptrs.cpp
mex -O5 return_ptrs.cpp
mex -O5 print.cpp

cd(toolboxpath)

echo off
