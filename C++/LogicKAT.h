#pragma once
class LogicKAT
{
public:
	LogicKAT();
	~LogicKAT();

	int Filter3Frame( double array_data[50] = {0});

	int judgeAngle(double array_data[50]);
	int walk(double array_data_last[50], double array_data[50]);
	int pingYi(int foot_distance,double array_data_last[50], double array_data[50]);
	int foot_angle(double array_data[50]);
	//处理镜头畸变
	void deal_distortion(double array_data[50]);

public:
	double array_data_1[50];
	double array_data_2[50];
	double array_data_3[50];
	double array_init[50];
	double array_ave[50];

	double array_last[50];

	double distance_waist_std;
	double distance_shoulder_std;
	double distance_std_1;

	 int bool_start;
	 bool lost_bool;

	 int walk_index;

	 int  right_distance;
	 int right_index;
	 int right_index_time;
	 bool bool_right;

	 int  left_distance;
	 int left_index;
	 int left_index_time;
	 bool bool_left;

	 int  distance_two_foot;
	 int foot_distance_std;

	 bool bool_wanqu;

	 int walk_stop_index;

	 int state;
	 int movtio_index;


};

