/*      
     WARNING !
     
	 DO NOT MODIFY CODES BELOW!
*/

#ifdef _WIN32
#include <windows.h>
#endif
#include <cmath>
#include "driver_cruise.h"

static void userDriverGetParam(float midline[200][2], float yaw, float yawrate, float speed, float acc, float width, int gearbox, float rpm);
static void userDriverSetParam(float* cmdAcc, float* cmdBrake, float* cmdSteer, int* cmdGear);
static int InitFuncPt(int index, void *pt);
void gear1( int* cmdGear,float* cmdAcc, float* cmdBrake);
void gear2(int* cmdGear,float* cmdAcc, float* cmdBrake);
void speedup(int* cmdGear,float* cmdAcc, float* cmdBrake);
// Module Entry Point
extern "C" int driver_cruise(tModInfo *modInfo)
{
	memset(modInfo, 0, 10*sizeof(tModInfo));
	modInfo[0].name    = "driver_cruise";	// name of the module (short).
	modInfo[0].desc    =  "user module for CyberCruise" ;	// Description of the module (can be long).
	modInfo[0].fctInit = InitFuncPt;			// Init function.
	modInfo[0].gfId    = 0;
	modInfo[0].index   = 0;
	return 0;
}

// Module interface initialization.
static int InitFuncPt(int, void *pt)
{
	tUserItf *itf = (tUserItf *)pt;
	itf->userDriverGetParam = userDriverGetParam;
	itf->userDriverSetParam = userDriverSetParam;
	return 0;
}

/*
     WARNING!

	 DO NOT MODIFY CODES ABOVE!
*/

/* 
    define your variables here.
    following are just examples
*/
static float _midline[200][2];
static float _yaw, _yawrate, _speed, _acc, _width, _rpm;
double tmp;
double D_err;//direction error					             
double D_errDiff = 0;//direction difference(Differentiation) 
double D_errSum=0;//sum of direction error(Integration)    

static int _gearbox;
static float K[7]; //曲率
static int acctime=0;//加速时间
float rcurv(float x1,float x2,float x3,float y1,float y2,float y3);
static void userDriverGetParam(float midline[200][2], float yaw, float yawrate, float speed, float acc, float width, int gearbox, float rpm){
	/* write your own code here */
	float dot[21][2];
	int i,j=0;
	for ( i = 0; i< 20; ++i) {dot[i][0] = midline[i*10][0]; dot[i][1]= midline[i*10][1];}//每隔10米取一点
	dot[20][0]=midline[199][0];dot[20][1]=midline[199][1];                   
	for ( i = 0; i< 200; ++i) _midline[i][0] = midline[i][0], _midline[i][1] = midline[i][1];
	_yaw = yaw;
	_yawrate = yawrate;
	_speed = speed;
	_acc = acc;
	_width = width;
	_rpm = rpm;
	_gearbox = gearbox;
	while(j<21) {K[j/3]=rcurv( dot[j][0],dot[j+1][0],dot[j+2][0],dot[j][1],dot[j+1][1],dot[j+2][1]);j=j+3;}//计算曲率半径
	printf("速度 %f 角速度%f 档位%d 10m far target(%f, %f)\n", _speed, _yawrate, _gearbox, _midline[10][0], _midline[10][1]);
}

static void userDriverSetParam(float* cmdAcc, float* cmdBrake, float* cmdSteer, int* cmdGear)
{
	/* write your own code here */
		int i,l;

		D_err = -atan2(_midline[30][0],_midline[30][1]);//only track the aiming point on the middle line 
		//D_errSum=D_errSum+D_err;
		D_errDiff = D_err - tmp;
		tmp = D_err;

		*cmdSteer = (_yaw +12*D_err+4*D_errDiff)/3.14;//设定舵机方向
	    if (_speed<20) {*cmdAcc=1;*cmdBrake=0;*cmdGear=1;acctime++;}
		l=int(_speed*0.025);
		if (acctime<93){//公路
			gear1( cmdGear,cmdAcc, cmdBrake);//确定档位
			for(i=0;i<l;i++)  
			{
				*cmdSteer =(_yaw +12*D_err+4*D_errDiff)/3.14;
				if( fabs(K[i])<0.005){
					if(_speed>305)
					{*cmdAcc=0.2; *cmdBrake=0.2;}
					else{*cmdAcc=1;*cmdBrake=0;}}
				if(fabs(K[i])>=0.005&&fabs(K[i])<0.0065){
					if(_speed>200) 
					{*cmdAcc=0.2; *cmdBrake=0.2+0.002*(_speed-sqrt(250/fabs(K[i])));}
					else {*cmdAcc=0.85, *cmdBrake=0.0;}}
				if(fabs(K[i])>=0.0065&&fabs(K[i])<0.008){
					if(_speed>160)
					{*cmdAcc=0.3,*cmdBrake=0.2+0.002*(_speed-sqrt(300/fabs(K[i])));}
					else {*cmdAcc=0.70; *cmdBrake=0.0;}}
				if(fabs(K[i])>=0.008&&(fabs(K[i])<0.012)){
					if(_speed>120) 
					{*cmdAcc=0.2; *cmdBrake=0.2+0.002*(_speed-sqrt(220/fabs(K[i])));}
					else { *cmdAcc=0.6; *cmdBrake=0.0;}}
				if((fabs(K[i])>=0.012)&&fabs(K[i])<0.018){
					if(_speed>115)
					{*cmdAcc=0.2; *cmdBrake=0.2+0.0035*(_speed-sqrt(280/fabs(K[i])));}
					else { *cmdAcc=0.60; *cmdBrake=0.0;}}
				if(fabs(K[i])>=0.018&&(fabs(K[i])<0.024)){
					if(_speed>110)
					{*cmdAcc=0.2; *cmdBrake=0.2+0.0035*(_speed-sqrt(280/fabs(K[i])));}
					else { *cmdAcc=0.60; *cmdBrake=0.0;}}
				if(fabs(K[i])>=0.024 && fabs(K[i])<0.029){
					if(_speed>90)
					{*cmdAcc=0.2; *cmdBrake=0.2+0.0035*(_speed-sqrt(200/fabs(K[i])));}
					else { *cmdAcc=0.60; *cmdBrake=0.0;}}
				if(fabs(K[i])>=0.029 && fabs(K[i])<0.037){
					if(_speed>80)
					{*cmdAcc=0.2; *cmdBrake=0.2+0.0035*(_speed-sqrt(200/fabs(K[i])));}
					else { *cmdAcc=0.60; *cmdBrake=0.0;}}
				if(fabs(K[i])>=0.037 && fabs(K[i])<0.060){
					if(_speed>70)
					{*cmdAcc=0.2; *cmdBrake=0.2+0.005*(_speed-sqrt(170/fabs(K[i])));}
					else { *cmdAcc=0.4; *cmdBrake=0.0;}}
				if(fabs(K[i])>0.060){
					if(_speed>70) 
					{*cmdAcc=0.1; *cmdBrake=0.2+0.006*(_speed-sqrt(50/fabs(K[i])));}
					else { *cmdAcc=0.4; *cmdBrake=0.0;}}
			}
		printf("舵机 %f 曲率 %f 中线偏角 %f 油门 %f 刹车 %f acctime%d\n",*cmdSteer,K[0],D_err,*cmdAcc,*cmdBrake,acctime);
        }
		else { //沙地
		l=int(_speed*0.02);//更改预瞄点
		gear2( cmdGear,cmdAcc, cmdBrake);//确定档位
		for(i=0;i<l;i++)  { 
			if(fabs(K[i])<=0.0065)
			{*cmdAcc=1.0;*cmdBrake=0.0;}
			if(fabs(K[i])>0.0065&&fabs(K[i])<=0.008){
				if(_speed>sqrt(320/fabs(K[i])))
				{*cmdAcc=0.2; *cmdBrake=0.2;}
				else {*cmdAcc=0.6; *cmdBrake=0.0;}}
			if(fabs(K[i])>0.008&&(fabs(K[i])<=0.012)){
				if(_speed>sqrt(200/fabs(K[i]))) 
				{*cmdAcc=0.2; *cmdBrake=0.2;}
				else { *cmdAcc=0.6; *cmdBrake=0.0;}}
		}
		l=int(_speed*0.030);
		for(i=0;i<l;i++)   {
			if(fabs(K[i])<=0.02&&fabs(K[i])>0.012)
			{*cmdSteer = (_yaw +8*D_err)/3.14;
				if(_speed>sqrt(274/fabs(K[i]))) {*cmdAcc=0.2; *cmdBrake=0.2;}
				else { *cmdAcc=0.6; *cmdBrake=0.0;}}
		}
		for(i=0;i<l;i++)   {
			if(fabs(K[i])<=0.037 && fabs(K[i])>0.02)
			{*cmdSteer = (_yaw +8*D_err)/3.14;
				if(_speed>sqrt(169/fabs(K[i]))) {*cmdAcc=0.2; *cmdBrake=0.2;}
				else { *cmdAcc=0.6; *cmdBrake=0.0;}}
		}
		for(i=0;i<6;i++)   {
			if(fabs(K[i])<=0.060 && fabs(K[i])>0.037)
			{*cmdSteer = (_yaw +8*D_err)/3.14;
				if(_speed>sqrt(288/fabs(K[i]))) {*cmdAcc=0.2; *cmdBrake=0.2;}
				else { *cmdAcc=0.4; *cmdBrake=0.0;}}
		}
		for(i=0;i<7;i++)   {
			if(fabs(K[i])>0.060)
			{*cmdSteer = (_yaw +12*D_err+4*D_errDiff)/3.14;
				if(_speed>sqrt(50/fabs(K[i]))) {*cmdAcc=0.2; *cmdBrake=0.2;}
				else { *cmdAcc=0.4; *cmdBrake=0.0;}}
		}
		printf("舵机 %f 曲率 %f 中线偏角 %f  油门 %f 刹车 %f acctime %d\n",*cmdSteer,K[0],D_err,*cmdAcc,*cmdBrake,acctime);
		}
}
        
void gear1(int* cmdGear,float* cmdAcc, float* cmdBrake){//公路档位
	      if (_speed<=45)*cmdGear=1;
		  if (_speed<=105 && _speed>45 && *cmdGear == 1 && _rpm>650) *cmdGear=*cmdGear+1;
		  if (_speed<=150 && _speed>105 && *cmdGear==2 && _rpm>650) *cmdGear=*cmdGear+1;
		  if (_speed<=195 && _speed>150 && *cmdGear == 3 && _rpm>650) *cmdGear=*cmdGear+1;
		  if (_speed<=250 && _speed>195&& *cmdGear==4 && _rpm>650)*cmdGear=*cmdGear+1;
		  if (_speed>250 && *cmdGear==5 && _rpm>600)*cmdGear=*cmdGear+1;
		  if (_speed<=60 && *cmdGear==2)*cmdGear=*cmdGear-1;
          if (_speed<=100 && _speed>50 && *cmdGear == 3 && _rpm<600) *cmdGear=*cmdGear-1;
		  if (_speed<=145 && _speed>100 && *cmdGear==4 && _rpm<600) *cmdGear=*cmdGear-1;
		  if (_speed<=185 && _speed>145 && *cmdGear == 5 && _rpm<600) *cmdGear=*cmdGear-1;
		  if (_speed<=240 && _speed>185 && *cmdGear==6 && _rpm<600)*cmdGear=*cmdGear-1;}

void gear2(int* cmdGear,float* cmdAcc, float* cmdBrake){//沙地档位
	      if (_speed<=40)*cmdGear=1;
		  if (_speed<=80 && _speed>40 && *cmdGear == 1 && _rpm>600) *cmdGear=*cmdGear+1;
		  if (_speed<=120 && _speed>80 && *cmdGear==2 && _rpm>600) *cmdGear=*cmdGear+1;
		  if (_speed<=160 && _speed>120 && *cmdGear == 3 && _rpm>600) *cmdGear=*cmdGear+1;
		  if (_speed<=200 && _speed>160&& *cmdGear==4 && _rpm>600)*cmdGear=*cmdGear+1;
		  if (_speed>200 && *cmdGear==5 && _rpm>600)*cmdGear=*cmdGear+1;
		  if (_speed<=35 && *cmdGear==2)*cmdGear=*cmdGear-1;
          if (_speed<=70&& _speed>35 && *cmdGear == 3 && _rpm<600) *cmdGear=*cmdGear-1;
		  if (_speed<=105 && _speed>70 && *cmdGear==4 && _rpm<600) *cmdGear=*cmdGear-1;
		  if (_speed<=140 && _speed>105 && *cmdGear == 5 && _rpm<600) *cmdGear=*cmdGear-1;
		  if (_speed<=175 && _speed>140 && *cmdGear==6 && _rpm<600)*cmdGear=*cmdGear-1;}
float len(float x1,float x2,float y1,float y2)
{return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
 }
float rcurv(float x1,float x2,float x3,float y1,float y2,float y3)
{float s,a,b,c;
 s=-((x2-x1)*(y3-y1)-(x3-x1)*(y2-y1))/2;
 a=len(x1,x2,y1,y2);
 b=len(x1,x3,y1,y3);
 c=len(x3,x2,y3,y2);
 return 4*s/(a*b*c);
 }

