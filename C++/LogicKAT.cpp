#include "LogicKAT.h"
#include<cstring>
#include<iostream>
#include <math.h>
#define MINDISTANCE 40


LogicKAT::LogicKAT()
{
	array_data_1[50] = { 0 };
	array_data_2[50] = { 0 };
	array_data_3[50] = { 0 };
	  array_init[50] = { 0 };
	  array_last[50] = { 0 };
	   array_ave[50] = { 0 };

	  distance_waist_std = 0;
	  distance_shoulder_std = 0;
	  distance_std_1 = 0;

	  bool_start = 0;

	  walk_index = 0;

	  right_distance=0;
	  right_index=0;  
	  right_index_time = 0;
	  bool_right = false;

	  left_distance = 0;
	  left_index = 0;
	  left_index_time = 0;
	  bool_left = 0;

	  distance_two_foot = 0;

	  foot_distance_std = 0;

	  bool_wanqu = 1;

	  walk_stop_index = 0;

	  state =0;
	  movtio_index = 0;
}


LogicKAT::~LogicKAT()
{
}
int LogicKAT::Filter3Frame( double array_data[50]) {
	

	
	
	//init
	if (abs(array_data[5] - array_data[3]) < MINDISTANCE && \
		abs(array_data[7] - array_data[3]) < MINDISTANCE && \
		abs(array_data[9] - array_data[3]) < MINDISTANCE && \
		abs(array_data[11] - array_data[3]) < MINDISTANCE && \
		abs(array_data[13] - array_data[3]) < MINDISTANCE && \
		abs(array_data[15] - array_data[3]) < MINDISTANCE && \
		array_data[6] > array_data[8] && \
		array_data[4] > array_data[6] && \
		array_data[2] > array_data[4] && \
		array_data[10] > array_data[2] && \
		array_data[12] > array_data[10] && \
		array_data[14] > array_data[12]) 
	    {
		
		memcpy(array_init, array_data, 400);
		distance_waist_std = sqrt(pow(abs(array_data[18] - array_data[24]), 2) + pow(abs(array_data[19] - array_data[25]), 2));
		foot_distance_std = sqrt(pow(abs(array_data[22] - array_data[28]), 2) + pow(abs(array_data[23] - array_data[29]), 2));
		distance_std_1 = array_data[3] - 368;
		distance_shoulder_std = sqrt(pow(abs(array_data[4] - array_data[10]), 2) + pow(abs(array_data[5] - array_data[11]), 2));
		std::cout << "AAAAAAAAAAAAAAAAAAA";
		memcpy(array_last, array_data, 400);
		bool_start = 1;





	    }

	walk(array_last, array_data);
	//std::cout <<std::fixed<<std::abs(array_data[23]- array_last[23])<<"              "<< std::abs(array_data[29] - array_last[29]);
	//std::cout << std::fixed << sqrt(pow(abs(array_last[22] - array_data[22]), 2) + pow(abs(array_last[23] - array_data[23]), 2))<<std::endl;
	pingYi(foot_distance_std, array_last, array_data);



    lost_bool = 0;
	if(bool_start == 1)
	{

		for (int i = 0; i < 50; i++) 
		{
			if (0 == array_data[i]) 
			{
				array_data[i] = array_last[i];
				lost_bool = 1;
			}

			memcpy(array_last, array_data, 400);
		}


		if (0 == lost_bool)
		{
			
			memcpy(array_last, array_data, 400);

		}

	}

	

	
	memcpy(array_data_1, array_data_2, 400);
	memcpy(array_data_2, array_data_3, 400);
	memcpy(array_data_3, array_data, 400);

	for (int i = 0; i < 50; i++)
	{
		array_ave[i] = (array_data_1[i] + array_data_2[i] + array_data_3[i]) / 3;

	}


	if (sqrt(pow(abs(array_data[22] - array_data[28]), 2) + pow(abs(array_data[23] - array_data[29]), 2)) >= distance_waist_std) {
		movtio_index = 1;
	}
	else {
		movtio_index = 0;
	}
	
	//std::cout << disance2 << "******" << array_data[3] - 368 << std::endl;
	
	//change distance
	//distance_shoulder_std = distance_shoulder_std - (distance_std_1 - (array_data[3] - 368));
	
	//std::cout << sqrt(pow(abs(array_data[2] - 656), 2) + pow(abs(array_data[3] - 368), 2)) / distance_std_1 << std::endl;

	return judgeAngle(array_ave);


};


int LogicKAT::judgeAngle(double array_data[50])
{
	//auto disance = sqrt(pow(abs(array_data[18] - array_data[24]), 2) + pow(abs(array_data[19] - array_data[25]), 2));

	//auto angle = acos((2* disance*disance)/(distance_waist_std*distance_waist_std)-1);

	
	auto disance2 = sqrt(pow(abs(array_data[4] - array_data[10]), 2) + pow(abs(array_data[5] - array_data[11]), 2))+27;
	disance2 = disance2 + (distance_std_1 - (array_data[3] - 368));
	/*
	if(disance2 > distance_shoulder_std)
	{
		disance2 = distance_shoulder_std;
	}
	*/
	
	auto angle2 = acos((2 * disance2*disance2) / (distance_shoulder_std*distance_shoulder_std) - 1);


	auto a = foot_angle(array_ave);
	auto b = angle2 * 90 / 3.1415;
	if (abs(a - b) > 45) {
		bool_wanqu = 1;
	}
	
	auto angle3 = 0;

	//使用脚步的数据来辅助判断方向
	/*
	if (array_data[22] < array_data[28] && array_data[23] < array_data[29])
		{
			 angle3 = angle2 * 180 / 3.14 / 2;
		}
	else if (array_data[22] > array_data[28] && array_data[23] < array_data[29])
		{
			 angle3 = 180- angle2 * 180 / 3.14 / 2;
		}
	else if(array_data[22] > array_data[28] && array_data[23] > array_data[29])
		{
			angle3 = 180 + angle2 * 180 / 3.14 / 2;
		}
	else if (array_data[22] < array_data[28] && array_data[23] > array_data[29])
		{
			angle3 = 360 - angle2 * 180 / 3.14 / 2;
		}
	*/
	if (array_data[2] < array_data[0] && array_data[4] < array_data[10])
	{
		angle3 = angle2 * 180 / 3.14 / 2;
	}
	else if (array_data[2] < array_data[0] && array_data[4] > array_data[10])
	{
		angle3 = 180 - angle2 * 180 / 3.14 / 2;
	}
	else if (array_data[2] > array_data[0] && array_data[4] > array_data[10])
	{
		angle3 = 180 + angle2 * 180 / 3.14 / 2;
	}
	else if (array_data[2] > array_data[0] && array_data[4] < array_data[10])
	{
		angle3 = 360 - angle2 * 180 / 3.14 / 2;
	}

	
	//std::cout << disance2 << std::endl;
	//std::cout << angle2 * 180 / 3.14 / 2 << std::endl;
	if (angle3 < 0 && array_data[10]>array_data[2]) {
		angle3 = 0;//强制去除异常
	}
	else if (angle3 < 0 && array_data[10] < array_data[2]) {
		angle3 = 180;
	
	}
	std::cout << angle3 << std::endl;
	
	return angle3;
}

int LogicKAT::walk(double array_data_last[50], double array_data[50]) {
	//std::cout << std::fixed << std::abs(array_data[23] - array_data_last[23]) << "              " << std::abs(array_data[29] - array_data_last[29]);
	/*
	if (std::abs(array_data[23] - array_data_last[23]) > 15 || std::abs(array_data[29] - array_data_last[29]) > 15) {
		walk_index += 1;
	}
	else {
		walk_index -= 1;
	}

	if (walk_index >= 2) 
	{

		std::cout << "BBBBBBBBBBBBBBBBBBBBBBBBBBBB";

	}
	if (walk_index < 0) {
		walk_index = 0;
	}
	else if (walk_index > 3) {
		walk_index = 3;
	}
	*/
	if ((std::abs(array_data[19] - array_data_last[19]) > 1 && std::abs(array_data[21] - array_data_last[21]) > 5 && std::abs(array_data[23] - array_data_last[23]) > 10) || \
		(std::abs(array_data[25] - array_data_last[25]) > 1 && std::abs(array_data[27] - array_data_last[27]) > 5 && std::abs(array_data[29] - array_data_last[29]) > 10) || \
		(std::abs(array_data[20] - array_data_last[20]) > 30 && std::abs(array_data[22] - array_data_last[22]) < 30 ) || \
		(std::abs(array_data[26] - array_data_last[26]) > 30 && std::abs(array_data[28] - array_data_last[28]) < 30)
		)
	{
		walk_index++;
		walk_stop_index = 0;
	}
	else 
	{
		walk_stop_index ++;
	}

	if (walk_index >= 2) 
	{

		
		if (walk_stop_index >= 3) 
		{
			//std::cout << "*******************" << std::endl;
			state = 0;
			walk_index = 0;
		}
		else 
		{
			//std::cout << "BBBBBBBBBBBBBBBBBBBBBBBBBBBB" << std::endl;
			state = 1;
		}

	}
	else if(walk_stop_index >= 3)
	{
		walk_index = 0;
		state = 0;
		//std::cout << "*******************" << std::endl;
	}
	else
	{
		//std::cout << "*******************" << std::endl;
		state = 0;
	}


	//std::cout <<std::fixed<<std::abs(array_data[23] - array_data_last[23]) << "         " << std::abs(array_data[29] - array_data_last[29])<<std::endl;
	return 0;
}

int LogicKAT::pingYi(int foot_distance, double array_data_last[50], double array_data[50]) {

	  right_distance = sqrt(pow(abs(array_data_last[22] - array_data[22]), 2) + pow(abs(array_data_last[23] - array_data[23]), 2));
	  left_distance = sqrt(pow(abs(array_data_last[28] - array_data[28]), 2) + pow(abs(array_data_last[29] - array_data[29]), 2));
	  distance_two_foot = sqrt(pow(abs(array_data[22] - array_data[28]), 2) + pow(abs(array_data[23] - array_data[29]), 2));

	  if (right_distance > 10) {
		  right_index += 1;
		  if (right_index >= 2) {
			  bool_right = 1;
			  left_index = 0;
			  bool_left = 0;
		  }
	  }
	  else if (left_distance > 10) {
		  left_index += 1;
		  if (left_index >= 2) {
			  bool_left = 1;
			  right_index = 0;
			  bool_right = 0;
		  }
	  }
	  if (bool_right == 1 && (distance_two_foot>foot_distance) && right_distance<5 && left_distance<5) {
		 
		  if (bool_wanqu == 1) {
			 // std::cout << "BACK``````````````" << std::endl;
			  //state = 4;
		  }
		  else {
			 // std::cout << "向右平移！！！！！！" << std::endl;
			  //state = 3;
		  }

	  }
	  else if(bool_left == 1 && (distance_two_foot>foot_distance) && left_distance<5 && right_distance<5) {
		  if (bool_wanqu == 1) {
			//  std::cout << "BACK``````````````" << std::endl;
			  //state = 4;
		  }
		  else {
			//  std::cout << "向2222平移！！！！！！" << std::endl;
			  //state = 2;
		  }
	}
	  //std::cout << std::fixed << right_index_time << "   " << distance_two_foot<<"     " << foot_distance <<"   "<<right_distance<< std::endl;

	return 0;
}


int LogicKAT::foot_angle(double array_data[50]) {
	auto a = abs(array_data[23] - array_data[29]);
	auto b = abs(array_data[22] - array_data[28]);
	auto c =sqrt(pow(a, 2) + pow(b, 2));

	auto angle_foot = acos((pow(b, 2)+ pow(c, 2)- pow(a, 2))/(2*b*c));

	angle_foot =angle_foot *180/3.1415;

	//计算膝盖弯曲度
	auto knee_left_1 = sqrt(pow(abs(array_data[24] - array_data[26]), 2) + pow(abs(array_data[25] - array_data[27]), 2));
	auto knee_left_2 = sqrt(pow(abs(array_data[26] - array_data[28]), 2) + pow(abs(array_data[27] - array_data[29]), 2));
	auto knee_left_3 = sqrt(pow(abs(array_data[24] - array_data[28]), 2) + pow(abs(array_data[25] - array_data[29]), 2));

	auto knee_right_1 = sqrt(pow(abs(array_data[18] - array_data[20]), 2) + pow(abs(array_data[19] - array_data[21]), 2));
	auto knee_right_2 = sqrt(pow(abs(array_data[20] - array_data[22]), 2) + pow(abs(array_data[21] - array_data[23]), 2));
	auto knee_right_3 = sqrt(pow(abs(array_data[18] - array_data[22]), 2) + pow(abs(array_data[19] - array_data[23]), 2));


	//std::cout << knee_left_3 / (knee_left_1 + knee_left_2)<<std::endl;
	if (knee_left_3 / (knee_left_1 + knee_left_2)<0.98 || knee_right_3 / (knee_right_1 + knee_right_2)<0.98) {
		bool_wanqu = 1;
	}
	else {
		bool_wanqu=0;
	}

	return angle_foot;


}

void LogicKAT::deal_distortion(double array_data[50]) 
{
	//1.1号点为中心，来缩放全身骨骼位置
	//2.需要考虑远近、左右等



}