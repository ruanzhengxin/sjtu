/*      
     WARNING !
     
	 DO NOT MODIFY CODES BELOW!
*/

#ifdef _WIN32
#include <windows.h>
#include <cmath>
#endif

#include "driver_follow.h"


static void userDriverGetParam(float LeaderXY[2], float midline[200][2], float yaw, float yawrate, float speed, float acc, float width, int gearbox, float rpm);
static void userDriverSetParam(float* cmdAcc, float* cmdBrake, float* cmdSteer, int* cmdGear);
static int InitFuncPt(int index, void *pt);
void gear(int* cmdGear,float* cmdAcc, float* cmdBrake);
float length(float x,float y);
float longth(float x1,float x2,float y1,float y2);
float velo();
float accel();
void stovelo();
void stodist();
void stoacc();


// Module Entry Point
extern "C" int driver_follow(tModInfo *modInfo)
{
	memset(modInfo, 0, 10*sizeof(tModInfo));
	modInfo[0].name    = "driver_follow";	// name of the module (short).
	modInfo[0].desc    =  "user module for CyberFollower" ;	// Description of the module (can be long).
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
static int _gearbox;
static float _Leader_X, _Leader_Y;
static float distance[5],v[5],acc[5];//距离、相对速度、相对加速度


static void userDriverGetParam(float LeaderXY[2], float midline[200][2], float yaw, float yawrate, float speed, float acc, float width, int gearbox, float rpm){
	/* write your own code here */
	float dot[21][2];
	int i,j=0;
	for ( i = 0; i< 20; ++i) {dot[i][0] = midline[i*10][0]; dot[i][1]= midline[i*10][1];}//每隔10米取一点
	dot[20][0]=midline[199][0];dot[20][1]=midline[199][1];
	_Leader_X = LeaderXY[0];
	_Leader_Y = LeaderXY[1];
	for (int i = 0; i< 200; ++i) _midline[i][0] = midline[i][0], _midline[i][1] = midline[i][1];
	_yaw = yaw;
	_yawrate = yawrate;
	_speed = speed;
	_acc = acc;
	_width = width;
	_rpm = rpm;
	_gearbox = gearbox;
	/* you can modify the print code here to show what you want */
	//printf("speed %.3f Leader XY(%.3f, %.3f)\n", _speed, _Leader_X, _Leader_Y);+
}

static void userDriverSetParam(float* cmdAcc, float* cmdBrake, float* cmdSteer, int* cmdGear){
	/* write your own code here */
	float a,b,sum=0;
	float safedist=0;	//安全距离
	stovelo();
    stodist();
    stoacc();
	safedist=9.9+0.0379*_speed-4.777/pow(10.0,4)*_speed*_speed+3.466/pow(10.0,6)*pow(_speed,3)-6.365/pow(10.0,9)*pow(_speed,4);
	for (int i=0;i<5;i++){sum=sum+distance[i];}
	
		*cmdAcc =2*v[4]+0.1*acc[4]+0.6*(sum/5-safedist)+0.8*(distance[4]-safedist); //油门 刹车PID控制
		*cmdBrake =-2*v[4]-0.125*acc[4]-0.6*(sum/5-safedist)-0.8*(distance[4]-safedist);
		*cmdSteer =(_yaw-1/(distance[4])*240*atan2(_Leader_X, _Leader_Y)-2*atan2( _midline[20][0],_midline[20][1]))/3.14 ;
		if (fabs(*cmdSteer)*_speed>50){//防止打滑
			*cmdAcc =2*v[4]+0*acc[4]+0.6*(sum/5-safedist)+0.8*(distance[4]-safedist)-0.04*_speed*abs(*cmdSteer);}
		
		if (*cmdBrake>=0.84){*cmdSteer=0;}
		if (*cmdAcc>1){*cmdAcc=1;}
		if (*cmdAcc<0){*cmdAcc=0;}
		if (*cmdBrake>1){*cmdBrake=1;}
		if (*cmdBrake<0){*cmdBrake=0;}
		if (*cmdSteer>1){*cmdSteer=1;}
		if (*cmdSteer<-1){*cmdSteer=-1;}
		//更快捕捉前车急刹信号
		if((*cmdAcc<=1)&&(*cmdAcc>=0.99)&&(acc[4]<-8.5))
		{*cmdAcc=0;
		*cmdBrake=1.0;
		}
		//针对第7组急刹的patch
		if(distance[4]<14.98&&_speed>170)
		{
			*cmdAcc=0.1;
		    *cmdBrake=0.2;}
		gear(cmdGear,cmdAcc,cmdBrake);
	printf("油门 %f 刹车%f, 距离%.3f\n",*cmdAcc, *cmdBrake, distance[4]);
	printf("相对速度 %f 加速度%f 舵机%f\n",v[4],acc[4],*cmdSteer);
	printf("速度 %f\n",_speed);
	}
void gear(int* cmdGear,float* cmdAcc, float* cmdBrake){
	      if (_speed<=45)*cmdGear=1;
		  if (_speed>45 && _speed<=105 && *cmdGear == 1 && _rpm>650) *cmdGear=*cmdGear+1;
		  if (_speed>105 && _speed<=155 && *cmdGear==2 && _rpm>650) *cmdGear=*cmdGear+1;
		  if (_speed>155 && _speed<=195 && *cmdGear == 3 && _rpm>650) *cmdGear=*cmdGear+1;
		  if (_speed>195 && _speed<=240&& *cmdGear==4 && _rpm>650)*cmdGear=*cmdGear+1;
		  if (_speed>240 && *cmdGear==5 && _rpm>600)*cmdGear=*cmdGear+1;
		  if (_speed<=45 && *cmdGear==2)*cmdGear=*cmdGear-1;
          if (_speed>45 && _speed<=105 && *cmdGear == 3 && _rpm<600) *cmdGear=*cmdGear-1;
		  if (_speed>105 && _speed<=155 && *cmdGear==4 && _rpm<600) *cmdGear=*cmdGear-1;
		  if (_speed>155 && _speed<=195 && *cmdGear == 5 && _rpm<600) *cmdGear=*cmdGear-1;
		  if (_speed>195 && _speed<=240 && *cmdGear==6 && _rpm<600)*cmdGear=*cmdGear-1;}
float length(float x,float y)
{return sqrt(x*x+y*y);}
float longth(float x1,float x2,float y1,float y2)
{return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
 }
void stodist(){
	int i;
	for (i=0;i<4;i++){
		distance[i]=distance[i+1];}
	distance[4]=length(_Leader_X,_Leader_Y);}
float velo(){	//平均速度
	int i;
	float vsum;
	vsum=0;
	for(i=3;i>0;i=i-1){
		vsum=vsum+(distance[4]-distance[i])/(0.02*(4-i));}
	return vsum/4;}
void stovelo(){
	int i;
	for (i=0;i<4;i++){
		v[i]=v[i+1];}
	v[4]=velo();}
float accel(){	//平均加速度
	int i;
	float accsum;
	accsum=0;
	for(i=3;i>0;i=i-1){
		accsum=accsum+(v[4]-v[i])/(0.02*(4-i));}
	return accsum/4;}
void stoacc(){
	int i;
	for (i=0;i<4;i++){
		acc[i]=acc[i+1];}
	acc[4]=accel();}
