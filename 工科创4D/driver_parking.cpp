
/*      
     WARNING !
     
	 DO NOT MODIFY CODES BELOW!
*/

#ifdef _WIN32
#include <windows.h>
#endif

#include <math.h>
#include "driver_parking.h"
void storedotlinedist();
void storeangle();
float length(float x1,float x2,float y1,float y2);
float Rcurva(float x1,float x2,float x3,float y1,float y2,float y3);
static void userDriverGetParam(float lotX, float lotY, float lotAngle, bool bFrontIn, float carX, float carY, float caryaw, float midline[200][2], float yaw, float yawrate, float speed, float acc, float width, int gearbox, float rpm);
static void userDriverSetParam (bool* bFinished, float* cmdAcc, float* cmdBrake, float* cmdSteer, int* cmdGear);
static int InitFuncPt(int index, void *pt);

// Module Entry Point
extern "C" int driver_parking(tModInfo *modInfo)
{
	memset(modInfo, 0, 10*sizeof(tModInfo));
	modInfo[0].name    = "driver_parking";	// name of the module (short).
	modInfo[0].desc    =  "user module for CyberParking" ;	// Description of the module (can be long).
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
	printf("OK!\n");
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
static float k[7]; //曲率
static float _yaw, _yawrate, _speed, _acc, _width, _rpm, _lotX, _lotY, _lotAngle, _carX, _carY, _caryaw;
static int _gearbox,w,s=0;
static bool _bFrontIn;
static float destX,destY,destdist,angle,dotlinedist;
static void userDriverGetParam(float lotX, float lotY, float lotAngle, bool bFrontIn, float carX, float carY, float caryaw, float midline[200][2], float yaw, float yawrate, float speed, float acc, float width, int gearbox, float rpm){
	/* write your own code here */

	_lotX = lotX;
	_lotY = lotY;
	_lotAngle = lotAngle;
	_bFrontIn = bFrontIn;
	_carX = carX;
	_carY = carY;
	_caryaw = caryaw;
	float dot[21][2];
	int i,j=0;
	for ( i = 0; i< 20; ++i) {dot[i][0] = midline[i*10][0]; dot[i][1]= midline[i*10][1];}//每隔10米取一点
	dot[20][0]=midline[199][0];dot[20][1]=midline[199][1];     
	for (int i = 0; i< 200; ++i) _midline[i][0] = midline[i][0], _midline[i][1] = midline[i][1];
	while(j<21) {k[j/3]=Rcurva( dot[j][0],dot[j+1][0],dot[j+2][0],dot[j][1],dot[j+1][1],dot[j+2][1]);j=j+3;}//计算曲率半径
	_yaw = yaw;
	_yawrate = yawrate;
	_speed = speed;
	_acc = acc;
	_width = width;
	_rpm = rpm;
	_gearbox = gearbox;
	destX=lotX+7.9*cos(_lotAngle+0.25);
	destY=lotY+7.9*sin(_lotAngle+0.25);
	if(cos(_lotAngle)>=0){ w=-1;}  else{ w=1;} //判断车位朝向
	if(_lotAngle -_caryaw>=0) { s=-1;}  else{ s=1;}
	destdist=sqrt((_carX-destX) * (_carX - destX) + (_carY - destY) * (_carY - destY));//设置目标停车准备点
	dotlinedist=w*(tan(_lotAngle)*(_carX-2.5*cos(_lotAngle)-_lotX)+(_lotY-carY+2.5*sin(_lotAngle)))/(sqrt(tan(_lotAngle)*tan(_lotAngle)+1));
	//点到直线距离公式
	if(fabs(_lotAngle -_caryaw)<=3.14){angle=_lotAngle -_caryaw;}   else{angle=_lotAngle -_caryaw+s*2*3.14;}
}
static float ddotlinelist[5],avedotlinelist,dangle[5],aveangle;
static int back = 0;
static float speed;
static void userDriverSetParam (bool* bFinished, float* cmdAcc, float* cmdBrake, float* cmdSteer, int* cmdGear){   
	/* write your own code here */
	storedotlinedist();
    storeangle();
	avedotlinelist=(ddotlinelist[0]+ddotlinelist[1]+ddotlinelist[2]+ddotlinelist[3]+ddotlinelist[4])/5;
	aveangle=(dangle[0]+dangle[1]+dangle[2]+dangle[3]+dangle[4])/5;
	if (!*bFinished) {     
		if ((_carX-_lotX) * (_carX-_lotX) + (_carY-_lotY) * (_carY-_lotY) < 0.01){//停住   
			*cmdSteer = -33.6*angle/3.14-2.16*(dotlinedist);                                           
			*cmdBrake = 1.0;*cmdGear = -1;*cmdAcc = 0.0;
			if(fabs(_speed) < 0.2)  *bFinished = true; }		
		else if (back) { //开始倒车
			if (k[0]<-0.005) { *cmdSteer = -20.5*angle/3.14-26.88*aveangle/3.14-1.404*(dotlinedist)-2.472*avedotlinelist;}
			else {*cmdSteer = -21.09*angle/3.14-26.88*aveangle/3.14-1.404*(dotlinedist)-2.472*avedotlinelist;}
			if(fabs(_speed) >4.2*sqrt((_carX-_lotX) * (_carX-_lotX) + (_carY-_lotY) * (_carY-_lotY))+5.15){*cmdBrake = 0.2;*cmdGear =- 1;*cmdAcc = 0;}//倒车速度控制
			else{*cmdBrake = 0.0;*cmdGear = -1;*cmdAcc = 0.55;}  
		} 
		else if (destdist<15){//右转漂移停住
			if (!back && destdist>6){
			*cmdSteer =-0.5*fabs(atan2(destX-_carX,destY-_carY));
			if(_speed<destdist){*cmdAcc=0.3;*cmdBrake=0;}
		    else{*cmdAcc=0;*cmdBrake=0.2;}
			}
			if (!back && destdist<6){
			*cmdSteer=(_caryaw-(_lotAngle+0.6))/3.14;
			*cmdAcc=0;
			*cmdBrake=0.1*_speed+0.05*destdist;
		
			if(_speed<2.05){back=1;}}} 
		else if ((_carX-_lotX) * (_carX - _lotX) + (_carY - _lotY) * (_carY - _lotY) < 3500) {//到一定范围时，将车子调整至道路左侧
			*cmdSteer = (_yaw -3.98*atan2(_midline[20][0]-_width/3,_midline[20][1]))/3.14;
			*cmdGear=1;*cmdAcc=0.2;*cmdBrake=0;}
		else {//其它路段按巡线方式行驶
			*cmdAcc = 1;//油门给100%
		    *cmdBrake = 0;//无刹车
		    *cmdSteer = (_yaw -8*atan2( _midline[30][0],_midline[30][1]))/3.14 ;//设定舵机方向
		    *cmdGear = 1;//档位始终挂1
			}
		printf("曲率 %f \n",k[0]);
	}
	if (*bFinished){
		if ((_carX-_lotX) * (_carX - _lotX) + (_carY - _lotY) * (_carY - _lotY) < 0.05){
			*cmdSteer=0;*cmdAcc=1;*cmdBrake=0;*cmdGear=1;}
		else { *cmdSteer =(_yaw -8*atan2( _midline[30][0],_midline[30][1]))/3.14 ;
		     *cmdAcc=1-0.006*fabs(*cmdSteer*_speed);*cmdBrake=0;}
		//-0.006*fabs(*cmdSteer*_speed)
		*cmdGear=1;}
	if (*cmdAcc>1){*cmdAcc=1;}
	if (*cmdAcc<0){*cmdAcc=0;}
	if (*cmdBrake>1){*cmdBrake=1;}
	if (*cmdBrake<0){*cmdBrake=0;}
	if (*cmdSteer>1){*cmdSteer=1;}

	if (*cmdSteer<-1){*cmdSteer=-1;}
	printf("Steer:%.2f\tspeed:%.2f\tlotAngle:%.2f\tcaryaw:%.2f\tback:%d\n",*cmdSteer,_speed,_lotAngle,_caryaw,back);
	printf("油门%.2f刹车%.2f\n车位坐标X%.2fY%.2f车辆坐标X%.2fY%.2f\n",*cmdAcc,*cmdBrake,_lotX,_lotY,_carX,_carY);
	printf("停车坐标X%.2fY%.2f停车距离%.2fdotlinedist%.2fw%d\n",_carX-3*cos(_lotAngle),_carY-3*sin(_lotAngle),destdist,dotlinedist,w);
	
}
void storedotlinedist(){
	int i;
	for (i=0;i<4;i++){
		ddotlinelist[i]=ddotlinelist[i+1];}
	ddotlinelist[4]=dotlinedist;}
void storeangle(){
	int i;
	for (i=0;i<4;i++){
		dangle[i]=dangle[i+1];}
	dangle[4]=angle;}

float length(float x1,float x2,float y1,float y2)
{return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
 }
float Rcurva(float x1,float x2,float x3,float y1,float y2,float y3)
{float s,a,b,c;
 s=-((x2-x1)*(y3-y1)-(x3-x1)*(y2-y1))/2;
 a=length(x1,x2,y1,y2);
 b=length(x1,x3,y1,y3);
 c=length(x3,x2,y3,y2);
 return 4*s/(a*b*c);
 }